/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 10/13/2024
 * Description Program that reads from image data, extracts least significant bits from each pixel and converts into ASCII values that form together the secret encoded message
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: decode <file.ppm>\n");
    return 0;
  }

  int width, height;
  struct ppm_pixel* pixel_data = read_ppm(argv[1], &width, &height);
  
  // Check if the file could not be opened
  if (pixel_data == NULL) {
    return 0;
  }

  int max_message_chars = (width * height * 3) / 8; 
  char* bit_array = malloc(sizeof(char) * width * height * 3);
  int bit_index = 0;

  // Extract the bits from pixel data
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      // Store the least significant bits of the RGB values
      bit_array[bit_index] = pixel_data[row * width + col].red % 2;
      bit_array[bit_index + 1] = pixel_data[row * width + col].green % 2;
      bit_array[bit_index + 2] = pixel_data[row * width + col].blue % 2;
      bit_index += 3;
    }
  }

  printf("Reading %s:with width %d and height %d\n", argv[1], width, height);
  printf("Max number of characters in the image: %d\n", max_message_chars);

  // Reconstruct the hidden message from the bits
  for (int char_index = 0; char_index < max_message_chars; char_index++) {
    unsigned char current_char = 0x0; // Initialize a character byte
    for (int bit = 0; bit < 8; bit++) {
      current_char |= bit_array[char_index * 8 + bit] << (7 - bit); // Rebuild the character from the bits
    }
    // Stop decoding if the null character is found
    if (current_char == '\0') {
      break;
    }
    printf("%c", current_char); // Print each decoded character
  }
  printf("\n");

  // Free allocated memory
  free(bit_array);
  free(pixel_data);

  return 0;
}



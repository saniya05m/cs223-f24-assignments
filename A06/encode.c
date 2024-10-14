/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 10/13/2024
 * Description Program that encodes user provided message into least significant bits of provided's images pixel data from ppm file and saved that into a new file
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: Please provide a .ppm file as an argument.\n");
    return 0;
  }

  int width, height;
  struct ppm_pixel* image_data = read_ppm(argv[1], &width, &height);
  
  // Handle file reading error
  if (image_data == NULL) {
    exit(0);
  }

  int maxLen = ((width * height * 3) / 8) - 1; 
  printf("Reading %s: w = %d, h = %d\n", argv[1], width, height);
  printf("Max number of characters in the image: %d\n", maxLen);

  // Allocate memory for the user's message
  char* message = malloc(sizeof(char) * (maxLen + 1));
  printf("Enter a phrase: ");
  scanf("%s", message);

  // Check if the message is too long
  if (strlen(message) >= maxLen) {
    printf("Error: Message is too long to be encoded.\n");
    free(message);
    return 0;
  }

  // Allocate memory for encoded bit sequence
  char* bitstream = malloc(sizeof(char) * (maxLen + 1) * 8);

  // Convert the message into a stream of bits
  for (int i = 0; i < strlen(message) + 1; i++) {
    unsigned char bit_mask = 0x80; // Start with the most significant bit
    for (int j = 0; j < 8; j++) {
      bitstream[i * 8 + j] = (bit_mask & message[i]) >> (7 - j); 
      bit_mask = bit_mask >> 1; // Shift the bit mask
    }
  }

  int bit_index = 0;

  // Embed the bits into the pixel RGB values
  for (int row = 0; row < height; row++) {
    unsigned char lsb_mask = 0x1; // Mask for the least significant bit
    for (int col = 0; col < width; col++) {
      // Embed in the red channel
      if (bit_index < (strlen(message) + 1) * 8 && 
            image_data[row * width + col].red % 2 != bitstream[bit_index]) {
        image_data[row * width + col].red ^= lsb_mask;
      }
      bit_index++;
      // Embed in the green channel
      if (bit_index < (strlen(message) + 1) * 8 && 
            image_data[row * width + col].green % 2 != bitstream[bit_index]) {
        image_data[row * width + col].green ^= lsb_mask;
      }
      bit_index++;
      // Embed in the blue channel
      if (bit_index < (strlen(message) + 1) * 8 && 
            image_data[row * width + col].blue % 2 != bitstream[bit_index]) {
        image_data[row * width + col].blue ^= lsb_mask;
      }
      bit_index++;
    }
  }

  // Create a new file name for the encoded image
  char output_filename[1024];
  strcpy(output_filename, argv[1]);
  output_filename[strlen(output_filename) - 4] = '\0';
  strcat(output_filename, "-encoded.ppm");

  // Write the modified pixel data to the new file
  write_ppm(output_filename, image_data, width, height);
  printf("Writing file %s\n", output_filename);

  // Clean up dynamically allocated memory
  free(message);
  free(image_data);
  free(bitstream);

  return 0;
}



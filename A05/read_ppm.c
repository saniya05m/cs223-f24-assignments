/*---------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 10/04/2024
 * Description Function to read a ppm file and store it in 2d array
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!) 

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fp = fopen(filename, "r");
  int maxVal;

  if (!fp) {
    printf("Cannot open file");
     return NULL;
  }

  char magic[4];
  fgets(magic, sizeof(magic), fp); // read the magic number 
    
  //skip everything from # to \n
  char buffer;
  buffer = fgetc(fp);
  if(buffer=='#'){
    do{
      buffer = getc(fp);
    }while(buffer!='\n');
  }
  ungetc(buffer,fp);
  
  // skip comments and read witdth, height, and max color value
  fscanf(fp, "%d %d\n%d", w, h, &maxVal);
  struct ppm_pixel *pixels = malloc((*w * *h) * sizeof(struct ppm_pixel));

  //allocate memory for pixel data
  if (!pixels) {
    printf("Error: Unable to allocate memory!\n");
    fclose(fp);
    return NULL;
  }

  //Read pixel data into the array
  fread(pixels, sizeof(struct ppm_pixel),(*w * *h), fp);
  fclose(fp);
  return pixels;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}

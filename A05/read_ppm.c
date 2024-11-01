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
  FILE *fp;
  fp = fopen(filename, "rb");
  if (fp == NULL) {
    printf("Cannot open file: %s\n", filename);
    return NULL;
  }

  char buffer[1024];
  int width = 0;
  int height = 0;
  //skip title lines
  fgets(buffer, 1024, fp);
  fgets(buffer, 1024, fp);
  while (buffer[0] == '#') {
    fgets(buffer, 1024, fp);
  }
  
  //read and store the width & height
  sscanf(buffer, "%d%*c %d%*c", &width, &height);
  //skip line with "255"
  fgets(buffer, 1024, fp);

  struct ppm_pixel* pxl = malloc(sizeof(struct ppm_pixel) * width * height);
  fread(pxl, sizeof(struct ppm_pixel), (width * height), fp);

  fclose(fp);
  *w = width;
  *h = height;
  return pxl;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}

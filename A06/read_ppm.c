/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 10/13/2024
 * Description function that reads from ppm file and stores the data into an array of pixel structs
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  infile = fopen(filename, "rb");
  if (infile == NULL) {
    printf("Error! Can't open file: %s\n", filename);
    return NULL;
  }
  char buffer[1024];
  int width = 0;
  int height = 0;
  //skip title lines
  fgets(buffer, 1024, infile);
  fgets(buffer, 1024, infile);
  while (buffer[0] == '#') {
    fgets(buffer, 1024, infile);
  }
  
  //read and store the width & height
  sscanf(buffer, "%d%*c %d%*c", &width, &height);
  //skip line with "255"
  fgets(buffer, 1024, infile);

  struct ppm_pixel* pxl = malloc(sizeof(struct ppm_pixel) * width * height);
  fread(pxl, sizeof(struct ppm_pixel), (width * height), infile);

  fclose(infile);
  //return
  *w = width;
  *h = height;
  return pxl;
}


struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}

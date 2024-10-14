/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 10/13/2024
 * Description function that given a struct pixel data writes it into a ppm file format
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
    printf("File not opened. \n");
    exit(0);
  }

  //write title lines
  fprintf(fp, "%s\n", "P6");
  fprintf(fp, "%s\n", "# Created by Saniya");

  //write width and height
  fprintf(fp, "%d %d\n", w, h);

  //write max color value
  fprintf(fp, "%d\n", 255);

  //write binary data
  fwrite(pixels, sizeof(struct ppm_pixel), (w*h), fp);

  fclose(fp);
}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}

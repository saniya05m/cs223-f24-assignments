/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 10/04/2024
 * Description Write a 2d array of pixels into a standard ppm file
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return;
    }

    // Write the header
    fprintf(fp, "P6\n%d %d\n255\n", w, h);

    // Write the pixel data
    fwrite(pixels, sizeof(struct ppm_pixel), w * h, fp);
    
    fclose(fp);
}
void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}

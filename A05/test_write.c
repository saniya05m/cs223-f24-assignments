/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main() {
    int w, h;
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);

    if (!pixels) {
        return 1;
    }

    // Test writing to a new file
    write_ppm("test.ppm", pixels, w, h);

    // Read the file back and print it
    struct ppm_pixel* new_pixels = read_ppm("test.ppm", &w, &h);
    if (!new_pixels) {
        free(pixels);
        return 1;
    }

    printf("Testing file test.ppm: %d %d\n", w, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = new_pixels[i * w + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(pixels);
    free(new_pixels);
    return 0;
}

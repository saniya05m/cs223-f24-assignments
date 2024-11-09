/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 11/08/2024
 * Description: Generates a ppm of a mendelbrot image 
 ---------------------------------------------*/ 
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <time.h>
  #include <sys/time.h>
  #include "read_ppm.h"
  #include "write_ppm.h"

  int main(int argc, char* argv[]) {
    int size = 480;
    float xmin = -2.0;
    float xmax = 0.47;
    float ymin = -1.12;
    float ymax = 1.12;
    int maxIterations = 1000;

    int opt;
    while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
      switch (opt) {
        case 's': size = atoi(optarg); break;
        case 'l': xmin = atof(optarg); break;
        case 'r': xmax = atof(optarg); break;
        case 't': ymax = atof(optarg); break;
        case 'b': ymin = atof(optarg); break;
        case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
      }
    }
    printf("Generating mandelbrot with size %dx%d\n", size, size);
    printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
    printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

    // todo: your work here
    // generate pallet

    //reading the ppm file
    struct timeval tStart, tEnd; 
    double timer;


    struct ppm_pixel* pixels = malloc(size * size * sizeof(struct ppm_pixel));
    if (!pixels) {
      printf("Error: Could not read PPM file.\n");
      return 1;
    }
    
    struct ppm_pixel* palette = malloc(sizeof(struct ppm_pixel) * maxIterations);
    if (!palette) {
      printf("Error: Could not allocate memory for palette.\n");
      return 1;
    }

    gettimeofday(&tStart, NULL);
    srand(time(0));

    // generate random colors for the palette
    for (int i = 0; i < maxIterations; i++) {
      palette[i].red = rand() % 255;
      palette[i].green = rand() % 255;
      palette[i].blue = rand() % 255;
    }


    for (int i = 0; i < size;i ++) {
      for (int j = 0; j < size; j++) {
          float xfrac = (float)i / size;
          float yfrac = (float)j / size;
          float x0 = xmin + xfrac * (xmax - xmin);
          float y0 = ymin + yfrac * (ymax - ymin);

          float x = 0;
          float y = 0;
          int iter = 0;
          while (iter < maxIterations && x*x + y*y < 2*2) {
            float xtmp = x*x - y*y + x0;
            y = 2*x*y + y0;
            x = xtmp;
            iter++;
          }

          if (iter < maxIterations) {
            pixels[i * size + j] = palette[iter];
          } else {
            pixels[i * size + j].red = 0;
            pixels[i * size + j].blue = 0;
            pixels[i * size + j].green = 0;

          }
      }
    }

    gettimeofday(&tEnd, NULL);

     // compute time
    timer = tEnd.tv_sec - tStart.tv_sec + (tEnd.tv_usec - tStart.tv_usec)/1.e6;
    printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size, timer);

    // write output file
    char filename[1024];
    sprintf(filename, "mandelbrot-%d-%ld.ppm", size, time(0));
    write_ppm(filename, pixels, size, size);
    printf("Writing file: %s", filename);

    free(pixels);
    free(palette);
    return 0;
  }

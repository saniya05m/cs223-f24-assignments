/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 10/13/2024
 * Description Code that outputs a bitmap from a unsigned 64 bit int
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  
  for (int row = 0; row < 8; row++){ 
    for (int column = 0; column < 8; column++){ 
      unsigned long bit = img >> (63 - (column + row * 8));
      unsigned long leftmask = 0x1;
      if (bit & leftmask) {
        printf("@ ");
      }
      else {
        printf("  ");
      }
    }
    printf("\n");
  }
  return 0;
}

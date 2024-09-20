/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 09/20/2024
 * Description 
Program that inputs amount of pause and a word to elongate using dots in between each letter.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int main() {
 int pause;
 char buff[32];
 char* res;
 res = malloc(sizeof(char)*100);

 printf("Pause length: ");
 scanf("%d",&pause);

 printf("Text: ");
 scanf("%s", buff);

 int indexr = 0;
 for(int i = 0; buff[i]!='\0'; i++){
    res[indexr] = buff[i];
    indexr++;
    for(int j = 0; j<pause; j++){
       res[indexr+j] = '.';
    }
    indexr+=pause;
 }
 printf("%s", res);
 printf("\n");  
 free(res);
 return 0;
}

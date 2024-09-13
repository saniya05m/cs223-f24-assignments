/**
* Program for Assignment 2 part 2, exclaim, for CS223 course.
*
* This program reads an input from a user and outputs it again, 
*except that lowercase letters are converted to a random 
*character from the set of @!*#.
* @author: Saniya Mukhambetkaliyeva
* @version: September 13, 2024
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  char buff[32];
  printf("Enter a word: ");
  scanf("%s", buff);
  printf("OMG! ");
 
  for(int i=0; buff[i]!='\0'; i++){
     if((int)buff[i]<=122 && (int)buff[i]>=97){
         char randch[4]={'@', '!', '#', '*'};
         printf("%c", randch[rand()%4]);      
         }
  
     else{
         printf("%c", buff[i]);
     }
  }  
 
  printf("\n");

  return 0;

}

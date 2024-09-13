/**
* Program for Assignment 2 part 3, acronym, for CS223 course.
*
* This program reads an input from a user, a phrase and 
* outputs acronym formed from the phrase.
* @author: Saniya Mukhambetkaliyeva
* @version: September 13, 2024
*/

#include <stdio.h>

int main() {
 char phrase [1024];
 printf("Enter a phrase: ");
 scanf("%[^\n]%*c", phrase);
 char acronym [1024];
 printf("Acronym: ");

 //iterator to keep track of the length of the acronym.
 int iacr = 0;
 
 //check if a character is uppercase letter.
 if((int)phrase[0] >=65 && (int)phrase[0] <=90){
     acronym[iacr] = phrase[0];
     iacr++;
 }
 
 
 for(int i = 1; phrase[i] != '\0'; i++){
     if (phrase[i] == ' ' && (int)phrase[i+1] >= 65 && (int)phrase[i+1] <= 90){
          acronym[iacr] = phrase[i+1];
          iacr++;
     }
 }
 
 //print the acronym
 for(int i = 0; i < iacr; i++){
     printf("%c", acronym[i]);
 }

 printf("\n");
 
 return 0;
}

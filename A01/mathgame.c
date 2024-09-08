/***************************************************
 * mathgame.c
 * Author: 
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
int rounds;
printf("Welcome to Math Game! \n");
printf("How many rounds do you want to play? ");
scanf("%d", &rounds);
int correct = 0;
for (int i = 0; i < rounds; i++){
int n1 = rand() % 10 + 1;
int n2 = rand() % 10 + 1;
int result = n1 + n2;
printf("%d %c %d %s ", n1, '+', n2, "= ?");
int response;
scanf("%d", &response);
if(response == result){
printf("Correct! \n");
correct = correct + 1;
} else {
printf("Incorrect :( \n");
correct = correct + 0;
}
}
printf("%s %d %c %d %s", "You anwered", correct, '/', rounds, "correctly. \n");
return 0;
}

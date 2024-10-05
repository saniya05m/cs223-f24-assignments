/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_crossword(char **crossword, int rows) {
    for (int i = 0; i < rows; i++) {
        free(crossword[i]);
    }
    free(crossword);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word1> <word2>\n", argv[0]);
        return 1;
    }

    char *word1 = argv[1];
    char *word2 = argv[2];

    // Find common letter and its index
    int common_letter_index_word1 = -1;
    int common_letter_index_word2 = -1;

    for (int i = 0; i < strlen(word1); i++) {
        for (int j = 0; j < strlen(word2); j++) {
            if (word1[i] == word2[j]) {
                common_letter_index_word1 = i;
                common_letter_index_word2 = j;
                break;
            }
        }
        if (common_letter_index_word1 != -1) break;
    }

    if (common_letter_index_word1 == -1) {
        printf("No common letter!\n");
        return 1;
    }

    // Dimensions of the crossword
    int rows = strlen(word1);
    int cols = strlen(word2);

    // Allocate memory for crossword
    char **crossword = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        crossword[i] = malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) {
            crossword[i][j] = '.';  // Fill with dots initially
        }
    }

    // Fill in the crossword with the words
    for (int i = 0; i < strlen(word1); i++) {
        crossword[i][common_letter_index_word2] = word1[i]; // Place word1 vertically
    }

    for (int i = 0; i < strlen(word2); i++) {
        crossword[common_letter_index_word1][i] = word2[i]; // Place word2 horizontally
    }

    // Print the crossword
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", crossword[i][j]);
        }
        printf("\n");
    }

    // Free memory
    free_crossword(crossword, rows);

    return 0;
}


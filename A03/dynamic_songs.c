/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 09/20/2024 
 * Description 
 Program that reads information about songs from a csv file and stores the information into an array of Song structures
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char title[128];
    char artist[128];
    int duration;
    float danceability;
    float energy;
    float tempo;
    float valence;
};

void printSongs(struct Song songs[], int n) {
    for(int i =0; i < n; i++) {
         printf("%d) %-20s artist: %-20s duration: %-20d danceability: %-20f E: %-20f T: %-20f V: %-20f\n",
         i, songs[i].title, songs[i].artist, songs[i].duration, songs[i].danceability, songs[i].energy, songs[i].tempo, songs[i].valence);
    }
    printf("\n===========================\n");

}

int main() {
 FILE *file = fopen("songlist.csv", "r");

 char buffer[1000];
 
 if(!fgets(buffer, sizeof(buffer), file)) {
    fclose(file);
    return -1;
 }
 
 int num_songs = atoi(strtok(buffer, ","));
 struct Song *songs = (struct Song *) malloc(num_songs * sizeof(struct Song));

 fgets(buffer, sizeof(buffer), file);
 
 for (int i = 0; i < num_songs; i++) {
     if (!fgets(buffer, sizeof(buffer), file)) {
         break;
     }
     
     char *token = strtok(buffer, ",");
     strncpy((songs)[i].title, token, 127);
     
     token = strtok(NULL, ",");
     strncpy((songs)[i].artist, token, 127);
     
     token = strtok(NULL, ",");
     (songs)[i].duration = atoi(token);
     
     token = strtok(NULL, ",");
     (songs)[i].danceability = atof(token);

     token = strtok(NULL, ",");
     (songs)[i].energy = atof(token);

     token = strtok(NULL, ",");
     (songs)[i].tempo = atof(token);

     token = strtok(NULL, ",");
     (songs)[i].valence = atof(token);
 }
  
 fclose(file);
 //free memory
 free(songs);
 printSongs(songs, num_songs); 
 
 return 0;
}


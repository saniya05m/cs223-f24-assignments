/**
* Program for Assignment 2 part 4, songs, for CS223 course.
*
* This program creates a structure to describe a song
* creates a list of songs and asks user to edit an
* attribute of a particular song from the list.
* @author: Saniya Mukhambetkaliyeva
* @version: September 13, 2024
*/

#include <stdio.h>
#include <string.h>

// create a structure to describe a song.
struct Song {
    char title[32];
    char artist[32];
    int minutes;
    int seconds;
    float danceability;
};

// function to print songs
void printSongs(struct Song songs[], int n) {
    for(int i =0; i < n; i++) {
         printf("%d) %-20s artist: %-20s duration: %d:%-20d danceability: %.2f\n",
         i, songs[i].title, songs[i].artist, songs[i].minutes, songs[i].seconds, songs[i].danceability);
    }
    printf("\n===========================\n");

}

// function to edit a song
void editSong(struct Song *song) {
    char attribute[20];
    printf("Which attribute do you wish to edit? [artist, title, duration, danceability]: ");
    scanf("%s", attribute);
    
    // determining which attribute was chosen to be edited and making edits to the struct.
    if (strcmp(attribute, "artist") == 0) {
        printf("Enter a new artist name: ");
        scanf(" %[^\n]s", song->artist);  // Read input with spaces
    } else if (strcmp(attribute, "title") == 0) {
        printf("Enter a new title: ");
        scanf(" %[^\n]s", song->title);
    } else if (strcmp(attribute, "duration") == 0) {
        printf("Enter a duration (minutes): ");
        scanf("%d", &song->minutes);
        printf("Enter a duration (seconds): ");
        scanf("%d", &song->seconds);
    } else if (strcmp(attribute, "danceability") == 0) {
        printf("Enter a new danceability (0.00 to 1.00): ");
        scanf("%f", &song->danceability);
    } else {
        printf("Invalid attribute.\n");
    }
}
int main() {
    struct Song songs[3] = {
         {"Shout", "Tears for Fears", 4, 11, 0.50},
         {"As it was", "Harry Styles", 2, 47, 0.70},
         {"Wish you were here", "Pink Floyd", 5, 34, 0.30}
    };
    int song_id;
    printf("Welcome to Saniya's Song list.\n");
    printSongs(songs, 3);
    printf("Enter a song id to edit [0,1,2]: ");
    scanf("%d", &song_id);

    if (song_id >= 0 && song_id < 3) {
        editSong(&songs[song_id]);
    } else {
        printf("Invalid song id.\n");
    }

    // Print updated list of songs
    printSongs(songs, 3);
  return 0;
}

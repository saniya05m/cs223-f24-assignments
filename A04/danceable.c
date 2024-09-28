/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 09/27/2024
 * Description
Program that reads from csv file containing songs, finds most danceable song and deletes it every time user pressed d.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining struct for Songs
typedef struct Song {
    char title[100];
    char artist[100];
    int duration_ms;
    float danceability;
    float energy;
    float tempo;
    float valence;
} Song;

//defining Node struct for linked list
typedef struct Node {
    Song song;
    struct Node *next;
} Node;

//insert new Song structs into a linked list
void insert(Node **head, Song song) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->song = song;
    new_node->next = *head;
    *head = new_node;
}

Node* find_and_remove_most_danceable(Node **head) {
    if (*head == NULL) return NULL;

    Node *prev = NULL, *most_danceable_prev = NULL, *current = *head, *most_danceable = *head;

    while (current != NULL) {
        if (current->song.danceability > most_danceable->song.danceability) {
            most_danceable_prev = prev;
            most_danceable = current;
        }
        prev = current;
        current = current->next;
    }

    if (most_danceable_prev == NULL) {
        *head = most_danceable->next;  // The head node is the most danceable
    } else {
        most_danceable_prev->next = most_danceable->next;
    }

    return most_danceable;
}

//print songs in a pretty format
void print_songs(Node *head) {
    int index = 0;
    while (head != NULL) {
        printf("%d) %-30s %-15s (%d:%02ds) D: %.3f E: %.3f T: %.3f V: %.3f\n",
               index++, head->song.title, head->song.artist,
               head->song.duration_ms / 60000, (head->song.duration_ms / 1000) % 60,
               head->song.danceability, head->song.energy, head->song.tempo, head->song.valence);
        head = head->next;
    }
}

// free heap memory of linked list
void free_list(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

//loading songs from csv file into Song structs connected together in a linked list
void load_songs_from_csv(const char *filename, Node **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        Song song;
        char *token = strtok(line, ",");
        strcpy(song.title, token);

        token = strtok(NULL, ",");
        strcpy(song.artist, token);

        token = strtok(NULL, ",");
        song.duration_ms = atoi(token);

        token = strtok(NULL, ",");
        song.danceability = atof(token);

        token = strtok(NULL, ",");
        song.energy = atof(token);

        token = strtok(NULL, ",");
        song.tempo = atof(token);

        token = strtok(NULL, ",");
        song.valence = atof(token);

        insert(head, song);
    }

    fclose(file);
}

int main() {
    Node *song_list = NULL;
    load_songs_from_csv("songlist.csv", &song_list);

    char command;
    while (1) {
        print_songs(song_list);
        printf("\nPress 'd' to show the most danceable song (any other key to quit): ");
        scanf(" %c", &command);

        if (command == 'd') {
            Node *most_danceable = find_and_remove_most_danceable(&song_list);
            if (most_danceable) {
                printf("\n---------------------------------------- Most danceable ------------------------------------\n");
                printf("%-30s %-15s (%d:%02ds) D: %.3f E: %.3f T: %.3f V: %.3f\n",
                       most_danceable->song.title, most_danceable->song.artist,
                       most_danceable->song.duration_ms / 60000,
                       (most_danceable->song.duration_ms / 1000) % 60,
                       most_danceable->song.danceability, most_danceable->song.energy,
                       most_danceable->song.tempo, most_danceable->song.valence);
                printf("--------------------------------------------------------------------------------------------\n");
                free(most_danceable);
            } else {
                printf("\nDataset contains 0 songs\n");
            }
        } else {
            break;
        }
    }

    free_list(song_list);
    return 0;
}

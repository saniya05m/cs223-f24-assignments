/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 12/01/2024
 * Description: Program that implements a dependencies search tree
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <dirent.h> 
#include "tree.h"

pthread_mutex_t mutex;
struct tree_node* treeRoot = NULL;

struct thread_args {
    int range_start, range_end;
    char **file_list;
};

void* process_files(void* args) {
    struct thread_args *threadData = (struct thread_args *) args;

    for (int i = threadData->range_start; i < threadData->range_end; ++i) {
        pthread_mutex_lock(&mutex);
        treeRoot = insert(threadData->file_list[i], treeRoot);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void analyze_dependencies(char* file) {
    FILE *filePointer;
    char buffer[100];
    char *dependency = NULL;

    filePointer = fopen(file, "r");
    if (filePointer) printf("%s has the following dependencies\n", file);

    while (fgets(buffer, 100, filePointer)) {
        if (strstr(buffer, "#include ")) {
            dependency = strtok(buffer, " ");
            dependency = strtok(NULL, " ");
            int index = 0;

            if (dependency[index] == '<') {
                char dep[100];
                while (dependency[index + 1] != '>') {
                    dep[index] = dependency[index + 1];
                    ++index;
                }
                dep[index] = '\0';
                printf(" %s\n", dep);
            } else {
                char *depFile = strtok(dependency, "\"");
                printf(" %s\n", depFile);
            }
        }
    }
    fclose(filePointer);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("usage: ./grep numThreadscommand directory -name <fileExt>\n");
        return 0;
    }

    int numThreads = atoi(argv[1]);
    char command[5];
    char directory[100];
    char **files = malloc(sizeof(char*) * 100);

    if (numThreads < 1) {
        printf("usage: numThreads > 0\n");
        return 1;
    }

    strcpy(command, argv[2]);
    strncpy(directory, argv[3], 98);
    directory[strlen(directory)] = '/';
    directory[strlen(directory) + 1] = '\0';

    int index = 0;
    for (int i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "-name") == 0) {
            if (i + 1 < argc) {
                if (strstr(argv[i + 1], "*")) {
                    DIR *directoryPointer;
                    struct dirent *entry;
                    directoryPointer = opendir(directory);
                    char extension[10];
                    strncpy(extension, argv[i + 1] + 1, strlen(argv[i + 1]));
                    if (directoryPointer) {
                        while ((entry = readdir(directoryPointer)) != NULL) {
                            if (strstr(entry->d_name, extension)) {
                                files[index] = malloc(sizeof(char) * 100);
                                sprintf(files[index], "%s%s", directory, entry->d_name);
                                ++index;
                            }
                        }
                        closedir(directoryPointer);
                    }
                } else {
                    files[index] = malloc(sizeof(char) * 100);
                    sprintf(files[index], "%s/%s", directory, argv[i]);
                    ++index;
                }
            }
        }
    }

    if (index < 1) {
        printf("usage: ./grep numThreads command directory -name <fileExt>\n");
        return 0;
    }

    printf("Processing %d files\n", index);

    float elapsedTime;
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);

    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    struct thread_args *threadDataArray = malloc(numThreads * sizeof(struct thread_args));
    pthread_mutex_init(&mutex, NULL);

    if (index >= numThreads) {
        for (int i = 0; i < numThreads; i++) {
            threadDataArray[i].range_start = i * (index / numThreads);
            threadDataArray[i].range_end = (i == numThreads - 1) ? index : (i + 1) * (index / numThreads);
            threadDataArray[i].file_list = files;
            printf("Thread %d processing %d files (%d to %d)\n", i, 
                   threadDataArray[i].range_end - threadDataArray[i].range_start, 
                   threadDataArray[i].range_start + 1, threadDataArray[i].range_end);
        }

        for (int i = 0; i < numThreads; i++) pthread_create(&threads[i], NULL, process_files, &threadDataArray[i]);
        for (int i = 0; i < numThreads; i++) pthread_join(threads[i], NULL);

        gettimeofday(&endTime, NULL);
        elapsedTime = endTime.tv_sec - startTime.tv_sec + (endTime.tv_usec - startTime.tv_usec) / 1.e6;
        printf("Elapsed time is %f\n", elapsedTime);
        pthread_mutex_destroy(&mutex);
    } else {
        printf("Number of threads (%d) < number of files (%d) to search\n", numThreads, index);
    }

    char userCommand[1024];
    while (1) {
        printf("$ ");
        scanf("%[^\n]%*c", userCommand);
        if (strcmp(userCommand, "quit") == 0) break;
        else if (strcmp(userCommand, "list") == 0) printSorted(treeRoot);
        else {
            struct tree_node* result = find(userCommand, treeRoot);
            if (result) analyze_dependencies(result->data.name);
            else printf("%s not found\n", userCommand);
        }
    }

    for (int i = 0; i < index; ++i) free(files[i]);
    free(files); free(threads); free(threadDataArray);
    clear(treeRoot);

    return 0;
}


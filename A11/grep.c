/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 12/01/2024
 * Description: Program that implements grep functionality and returns all files that contain a given keyword
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct {
    char **files;           // List of files for the thread
    int num_files;          // Number of files to process
    char *keyword;          // Keyword to search for
    int thread_id;          // Thread ID
    int matches;            // Matches found by this thread
    pthread_mutex_t *mutex; // Mutex for synchronized access
} ThreadArgs;

// Thread function to search keyword in the assigned files
void *search_files(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    args->matches = 0;

    printf("Thread %d searching %d files (%d to %d)\n",
           args->thread_id, args->num_files,
           args->thread_id + 1, args->thread_id + args->num_files);

    for (int i = 0; i < args->num_files; i++) {
        FILE *file = fopen(args->files[i], "r");
        if (!file) {
            pthread_mutex_lock(args->mutex);
            fprintf(stderr, "Thread %d: Could not open file %s\n", args->thread_id, args->files[i]);
            pthread_mutex_unlock(args->mutex);
            continue;
        }

        char line[1024];
        int line_number = 0;
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (strstr(line, args->keyword)) {
                args->matches++;
                pthread_mutex_lock(args->mutex);
                printf("%d) %s:%d: %s", args->thread_id, args->files[i], line_number, line);
                pthread_mutex_unlock(args->mutex);
            }
        }
        fclose(file);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "usage: ./grep <NumThreads> <Keyword> <Files>\n");
        return EXIT_FAILURE;
    }

    int num_threads = atoi(argv[1]);
    char *keyword = argv[2];
    int num_files = argc - 3;

    if (num_threads <= 0) {
        fprintf(stderr, "Number of threads must be greater than 0.\n");
        return EXIT_FAILURE;
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadArgs *thread_args = malloc(num_threads * sizeof(ThreadArgs));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    // Divide files among threads
    int files_per_thread = num_files / num_threads;
    int remaining_files = num_files % num_threads;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int file_index = 0;
    for (int i = 0; i < num_threads; i++) {
        int num_files_for_thread = files_per_thread + (i < remaining_files ? 1 : 0);

        thread_args[i].files = &argv[3 + file_index];
        thread_args[i].num_files = num_files_for_thread;
        thread_args[i].keyword = keyword;
        thread_args[i].thread_id = i;
        thread_args[i].matches = 0;
        thread_args[i].mutex = &mutex;

        file_index += num_files_for_thread;

        if (pthread_create(&threads[i], NULL, search_files, &thread_args[i]) != 0) {
            perror("pthread_create");
            free(threads);
            free(thread_args);
            return EXIT_FAILURE;
        }
    }

    int total_matches = 0;
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            free(threads);
            free(thread_args);
            return EXIT_FAILURE;
        }
        total_matches += thread_args[i].matches;
        printf("Thread %d found %d lines containing keyword: %s\n",
               i, thread_args[i].matches, keyword);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1e6;

    printf("Elapsed time is %.6f seconds\n", elapsed_time);
    printf("Total matches: %d\n", total_matches);

    pthread_mutex_destroy(&mutex);
    free(threads);
    free(thread_args);
    return EXIT_SUCCESS;
}


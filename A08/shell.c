/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva 
 * Date: 11/1/2024
 * Description Shell simulation program that takes in users input and runs a process to execute the commands
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET " >>> ", cwd);
}

int main() {
    char *input;
    char *args[100];
    pid_t pid;
    int status;

    while (1) {
        print_prompt();
        input = readline("");

        if (input == NULL) { // Check for EOF
            break;
        }

        if (strcmp(input, "exit") == 0) { // Check for exit
            free(input);
            break;
        }

        if (strlen(input) > 0) {
            add_history(input); // Add to history
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            args[++i] = strtok(NULL, " ");
        }

        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
        } else if (pid == 0) { // Child process
            if (execvp(args[0], args) < 0) { // Execute command
                perror("Command execution failed, sorry :( ");
                exit(1); // Failed exec
            }
        } else {
            waitpid(pid, &status, 0); // Wait for child

            // Checking child for error
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf(ANSI_COLOR_RED "Error: Command exited with status %d\n" ANSI_COLOR_RESET, WEXITSTATUS(status));
            }
        }

        free(input);
    }
    printf("Exiting shell... bye bye :) \n");
    return 0;
}


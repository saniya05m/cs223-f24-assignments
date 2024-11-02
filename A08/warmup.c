/*----------------------------------------------
 * Author: Saniya Mukhambetkaliyeva
 * Date: 10/1/2024
 * Description: Code that creates multiple children processes and outputs its 
 * number along with the process number. And then in the end both branches say
 * bye
 ---------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("%d] A0\n", getpid());

    pid_t pid_B0 = fork();
    if (pid_B0 == 0) {
        // In B0
        printf("%d] B0\n", getpid());

        pid_t pid_C0 = fork();
        if (pid_C0 == 0) {
            // In C0
            printf("%d] C0\n", getpid());
            return 0;  // C0 ended
        }

        // Again in B0
        wait(NULL);  // Wait for C0 to finish

        pid_t pid_C1 = fork();
        if (pid_C1 == 0) {
            // In C1
            printf("%d] C1\n", getpid());
            printf("%d] Bye\n", getpid());
            return 0;  // C1 ends
        }

        // Again in B0, waiting for C1 to finish
        wait(NULL);
        printf("%d] Bye\n", getpid());
        return 0;  // B0 ends
    } else {
        // In the original A0 process
        pid_t pid_B1 = fork();
        if (pid_B1 == 0) {
            // In B1
            printf("%d] B1\n", getpid());
            printf("%d] Bye\n", getpid());
            return 0;  // B1 ends
        }

        // In A0, waiting for both B0 and B1 to finish
        wait(NULL);  // Wait for B0
        wait(NULL);  // Wait for B1
    }

    return 0;
}


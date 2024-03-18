#include "main.h"

int main(int argc, char* argv[]) {
    for (; ; ) {
        pid_t pids[2];
        do {
            pids[0] = fork();
            if (pids[0] < 0) {
                perror("Error occurred while executing fork()");
                exit(EXIT_FAILURE);
            }
            if (pids[0] == 0) {
                char* args[2] = {"/bin/ls", NULL};
                int status = execve("/bin/ls", args, NULL);
                if (status) {
                    perror("Error occurred while executing ls");
                    return EXIT_FAILURE;
                }
                return EXIT_SUCCESS;
            }
            int status;
            waitpid(pids[0], &status, 0);
            pids[1] = fork();
            if (pids[1] == 0) {
                char* args[2] = {"/bin/ps", NULL};
                int status = execve("/bin/ps", args, NULL);
                if (status) {
                    perror("Error occurred while executing ps");
                    return EXIT_FAILURE;
                }
                return EXIT_SUCCESS;
            }
            wait(NULL);
            sleep(SLEEP_INTERVAL);
        } while (0);
    }
}
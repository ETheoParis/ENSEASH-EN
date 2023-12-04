#define SIZE 1024
#define MESSAGE "enseash % "
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

char** complexCom(char*input, char**buffer);

void executeCommand(char* input, int pidoriginal) {
    struct timespec start, end;
    int status;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    int pid = fork();

    if (pid < 0) {
        perror("fork impossible");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (execl(input, input, NULL) == -1) {
            if (execlp(input, input, NULL) == -1) {
                perror("wrong command");
                exit(EXIT_FAILURE);
            }
        }
        exit(EXIT_SUCCESS);
    }

    wait(&status);
    clock_gettime(CLOCK_MONOTONIC, &end);
    char prompt[100];
    long timeelapsed = (end.tv_nsec - start.tv_nsec) / 1000;

    if (WIFEXITED(status)) {
        snprintf(prompt, 100, "enseash [exit:%d]|[%ldms] %%", WEXITSTATUS(status), timeelapsed);
    } else if (WIFSIGNALED(status)) {
        snprintf(prompt, 100, "enseash [sign:%d]|[%ldms] %%", WTERMSIG(status), timeelapsed);
    }
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main(int argc, char* argv[]) {
    char input[SIZE];
    int pidoriginal = getpid();

    while (1) {
        if (write(STDOUT_FILENO, MESSAGE, strlen(MESSAGE)) == -1) {
            perror("write enseash");
        }

        if (read(STDIN_FILENO, input, SIZE) == -1) {
            perror("read");
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            if (write(STDOUT_FILENO, "bye bye \n", 10) == -1) {
                perror("bye bye error");
            }
            exit(EXIT_SUCCESS);
        }

        executeCommand(input, pidoriginal);
    }
    return 0;
}

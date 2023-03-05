#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define PIPE_FAILED_ERROR       513
#define FORK_FAILED_ERROR       514
#define SUCCESS                 0

static int x;

int main(int argc, char *argv[]) {

    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1) {              // creating first pipe unsuccessful
        fprintf(stderr, "pipe failed\n");
        return PIPE_FAILED_ERROR;
    } 

    if (pipe(fd2) == -1) {              // creating second pipe unsuccessful
        fprintf(stderr, "pipe failed\n");
        return PIPE_FAILED_ERROR;
    }

    char input_str[100];
    fgets(input_str, sizeof(input_str)/sizeof(char), stdin);
    
    int *ptr = (int*)mmap(NULL, 64, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, -1, 0);
    x = *ptr;

    pid_t p = fork();
    
    if (p < 0) {                        // fork was unsuccessful
        fprintf(stderr, "fork failed\n");
        return FORK_FAILED_ERROR;
    }
    else if (p > 0) {                   // parent process

        close(fd1[0]);                  // close reading end of first pipe

        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);

        // wait for child to send a string
        wait(NULL);

        close(fd2[1]);

        char piped_input[100];

        // Read piped input
        read(fd2[0], piped_input, 100);

        printf("%s\n", piped_input);

        int y = atoi(piped_input);
        printf("%d == %d? %d\n", x, y, x == y);

        printf("x = %d\n", x);
        printf("x^2 = (%d)^2 = %d\n", x, x*x);

        munmap(ptr, 64);

        close(fd2[0]);
    }

    // child process
    else {
        close(fd1[1]);                  // close writing end of first pipe
        
        char str[100];

        // Read a string using first pipe
        read(fd1[0], str, 100);

        printf(">>> %s\n", str);

        // Take String length
        int s_length = strlen(str);

        x = s_length;

        str[s_length] = '\0';

        char piped_output[100];

        sprintf(piped_output, "%d", s_length);

        printf("%s\n", piped_output);

        write(fd2[1], piped_output, strlen(piped_output)+1);

        close(fd1[0]);
        close(fd2[0]);

        return 0;

    } 

    return SUCCESS;
}

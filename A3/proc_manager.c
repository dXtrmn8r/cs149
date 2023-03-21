#include <stdio.h>                      // needed for standard io operations
#include <stdlib.h>                     // needed for malloc/free
#include <string.h>                     // needed for string operations
#include <unistd.h>                     //
#include <fcntl.h>

#define MAX_CHARS 30

int main() {

    char input[MAX_CHARS];
    char *command_list[MAX_CHARS];

    int ch_pid;

    int num_commands = 0;

    while (fgets(input, 30, stdin) != NULL) {                       // input is read here
        // replaces '\n' with a null character '\0'
        input[strlen(input) - 1] = '\0';
        num_commands++;

        ch_pid = fork();

        if (ch_pid == 0) {
            int child_pid = getpid();
            char pid_name_out[MAX_CHARS];                          // filename of the output file descriptor
            char pid_name_err[MAX_CHARS];                          // filename of the error file descriptor

            sprintf(pid_name_out, "%d", child_pid);                 // converts int arguments to string args
            strcpy(pid_name_err, pid_name_out);
            printf("PID %s\n", pid_name_out);

            // opens the necessary files PID.out and PID.err
            int out_desc = open(strcat(pid_name_out,".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_desc = open(strcat(pid_name_err,".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

            // courtesy of Lilou Sicard-Nöel
            dup2(out_desc, 1);
            dup2(err_desc, 2);

            // TODO: tokenize input
            // from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
            // from https://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
            char *argvals[MAX_CHARS];
            int argcount = 0;

            char *p = strtok(input, " ");

            while (p != NULL) {
                argvals[argcount] = p;
                argcount++;
                p = strtok(NULL, " ");
            }
            argvals[argcount] = NULL;

            int exit_code = execvp(argvals[0], argvals);

            if (exit_code != 0)
                exit(exit_code);

            // fprintf(stdout, "Hello world from PID %d.\n", child_pid);
            // fprintf(stderr, "ERROR from PID %d\n", child_pid);

            // close used resources
            close(out_desc);
            close(err_desc);
            exit(0);
        }
    }
    /*
        ch_pid = fork();

        fprintf(stderr, "%s\n", input);


        if (ch_pid == 0) {
            int child_pid = getpid();
            char *pid_name_out = "";
            pid_name_out = malloc(4*sizeof(char));
            char *pid_name_err = "";
            pid_name_err = malloc(4*sizeof(char));

            sprintf(pid_name_out, "%d", child_pid);
            strcpy(pid_name_err, pid_name_out);
            printf("PID %s\n", pid_name_out);

            FILE *outstr = fopen(strcat(pid_name_out,".out"), "w");
            FILE *errstr = fopen(strcat(pid_name_err,".err"), "w");

            execvp;

            fprintf(outstr, "Hello world from PID %d.\n", child_pid);
            fprintf(errstr, "ERROR from PID %d\n", child_pid);

            fclose(outstr);
            fclose(errstr);

            free(pid_name_out);
            free(pid_name_err);


        } else {
            // printf("Parent process.");
            int status;

            FILE *errstr = fopen(strcat(atoi))

            while ((ch_pid = wait(&status)) > 0) {
                if (WIFEXITED(status)) {
                    fprintf(fderr, "Child %d terminated normally with exit code: %d\n",
                            ch_pid, WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    fprintf(fderr, "Child %d terminated abnormally with signal number: %d\n",
                            ch_pid, WTERMSIG(status));
                }
            }

        }

    }
     */

    for (int i = 0; i < num_commands; i++) {
        printf("%s\n", command_list[i]);
    }

    // while waiting for a process to finish
    while (wait(NULL) != -1) {

    }

    return 0;
}


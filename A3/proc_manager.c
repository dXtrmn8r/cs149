/**
 * Program where user inputs any command line function supported in local machine, and executes them as separate child processes.
 *
 * Author names:                        Darren Peralta, Henry Choy
 * Author emails:                       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:                  03/21/2023
 * Date created:                        03/17/2023
 */

#include <stdio.h>                      // needed for standard io operations
#include <stdlib.h>                     // needed for malloc/free
#include <string.h>                     // needed for string operations
#include <unistd.h>                     // needed for execvp, fd constants (i.e. STDOUT_FILENO, STDERR_FILENO)
#include <fcntl.h>                      // needed for open() and its corresponding FLAGS (i.e. O_RDWR, O_CREAT, O_APPEND_

#define MAX_CHARS 30

/**
 * Main method that executes each function inputted by the user.
 * Assumptions:                         Users will type a single command with its corresponding cmd args. Pipe not supported
 * Input params:                        None
 * @return non-zero integer if any error occurred, 0 otherwise.
 */
int main() {

    char input[MAX_CHARS];
    // char *command_list[MAX_CHARS];

    int ch_pid;
    char pid_name_out[MAX_CHARS];                                     // filename of the output file descriptor
    char pid_name_err[MAX_CHARS];                                     // filename of the error file descriptor

    // int num_commands = 0;

    while (fgets(input, 30, stdin) != NULL) {                        // input is read here
        // replaces '\n' with a null character '\0'
        input[strlen(input) - 1] = '\0';
        //  num_commands++;

        ch_pid = fork();                                            // forks each command inputted

        if (ch_pid == 0) {                                          // child process
            int actual_child_pid = getpid();

            sprintf(pid_name_out, "%d", actual_child_pid);          // converts int arguments to string args
            strcpy(pid_name_err, pid_name_out);                     // copies PID string in out filename to err filename

            // opens the necessary files PID.out and PID.err
            int out_desc = open(strcat(pid_name_out,".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            int err_desc = open(strcat(pid_name_err,".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

            // courtesy of L. Sicard-Nöel
            // duplicate file descriptors
            dup2(out_desc, STDOUT_FILENO);
            dup2(err_desc, STDERR_FILENO);

            // tokenize each command line argument
            // from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
            // from https://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
            char *argvals[MAX_CHARS];
            int argcount = 0;

            char *p = strtok(input, " ");

            // store tokenized command line arguments into argvals[]
            while (p != NULL) {
                argvals[argcount] = p;
                argcount++;
                p = strtok(NULL, " ");
            }
            argvals[argcount] = NULL;    // stop storing command line arguments by pointing to NULL at the end

            // executes each command, and returns exit code
            int exit_code = execvp(argvals[0], argvals);

            // exit appropriately from the exit code
            if (exit_code != 0) exit(exit_code);

            // debugging
            // fprintf(stdout, "Hello world from PID %d.\n", actual_child_pid);
            // fprintf(stderr, "ERROR from PID %d\n", actual_child_pid);

            // close used resources
            free(p);
            close(out_desc);
            close(err_desc);
            return exit_code;
        }
    }

    // parent process
    int status;

    // Process API slides, courtesy of Dr. William Andreopoulos
    // waits for each child process to finish
    while ((ch_pid = wait(&status)) > 0) {

        // filenames for file descriptors
        sprintf(pid_name_out, "%d.out", ch_pid);
        sprintf(pid_name_err, "%d.err", ch_pid);

        // open respective file descriptors for each process
        int out_desc = open(pid_name_out, O_RDWR | O_APPEND, 0777);
        int err_desc = open(pid_name_err, O_RDWR | O_APPEND, 0777);

        // duplicate file descriptors
        dup2(out_desc, STDOUT_FILENO);
        dup2(err_desc, STDERR_FILENO);

        // receive signal from child process
        if (WIFEXITED(status)) {                                        // exited normally
            fprintf(stderr, "Exited with exit code = %d\n",
                    ch_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {                               // exited abnormally with signal
            fprintf(stderr, "Child %d terminated with signal %d\n",
                    ch_pid, WTERMSIG(status));
        }

        // close used resources
        close(out_desc);
        close(err_desc);
    }

    return 0;
}


/**
 * Program where user inputs any command line function supported in local machine, and executes them as separate child processes.
 *
 * Author names:                        Darren Peralta, Henry Choy
 * Author emails:                       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:                  04/23/2023
 * Date created:                        03/17/2023
 */

#include <stdio.h>                      // needed for standard io operations
#include <stdlib.h>                     // needed for malloc/free
#include <string.h>                     // needed for string operations
#include <unistd.h>                     // needed for execvp, fd constants (i.e. STDOUT_FILENO, STDERR_FILENO)
#include <sys/wait.h>                   // needed for wait()
#include <fcntl.h>                      // needed for open() and its corresponding FLAGS
                                        // (i.e. O_RDWR, O_CREAT, O_APPEND)
#include <time.h>                       // time functions
#include <math.h>                       // mathematical functions

#include "dictionary_hashtable.c"       // needed for hash table functions

#define MAX_COMMAND_CHARS 100
#define MAX_PID_CHARS 10
#define MAX_ARGS 10

double elapsed(struct timespec start_time, struct timespec end_time);

/**
 * Main method that executes each function inputted by the user.
 * Assumptions:                         Users will type a single command with its corresponding cmd args. Pipe not supported
 * Input params:                        None
 * @return non-zero integer if any error occurred, 0 otherwise.
 */
int main() {

    char *command = (char *)malloc(sizeof(char) * MAX_COMMAND_CHARS);               // user command variable

    int ch_pid;                                                                     // pid of forked process

    int num_commands = 0;                                                           // number of commands

    char pid_name_out[MAX_PID_CHARS];                                               // filename of the output file descriptor
    char pid_name_err[MAX_PID_CHARS];                                               // filename of the error file descriptor
    while (fgets(command, MAX_COMMAND_CHARS, stdin) != NULL) {                      // command is read here
        // replaces '\n' with a null character '\0'
        command[strlen(command) - 1] = '\0';
        num_commands++;

        ch_pid = fork();                                                            // forks each command inputted

        if (ch_pid < 0) {                                                           // forking error
            fprintf(stderr, "fork() error");                                        // display message
            exit(2);                                                                // exit process
        } else if (ch_pid == 0) {                                                   // child process
            int actual_child_pid = getpid();                                        // pid of child process

            strcpy(pid_name_out, "");                                               // initializes pid_name_out properly
            strcpy(pid_name_err, "");

            sprintf(pid_name_out, "%d", actual_child_pid);                          // converts int arguments to string args
            strcpy(pid_name_err, pid_name_out);                                     // copies PID string in out filename to err filename

            // opens the necessary files PID.out and PID.err
            int fd_out = open(strcat(pid_name_out, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_err = open(strcat(pid_name_err, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

            // courtesy of L. Sicard-Nöel
            // duplicate file descriptors
            dup2(fd_out, STDOUT_FILENO);
            dup2(fd_err, STDERR_FILENO);

            // tokenize each command line argument
            // from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
            // from https://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
            char *argvals[MAX_ARGS];
            int argcount = 0;

            char *p = strtok(command, " ");

            // store tokenized command line arguments into argvals[]
            while (p != NULL) {
                argvals[argcount] = p;
                argcount++;
                p = strtok(NULL, " ");
            }
            argvals[argcount] = NULL;                                               // stop storing command line arguments by pointing to NULL at the end

            // execute code
            int exit_code = execvp(argvals[0], argvals);

            // exit appropriately
            if (exit_code != 0)
                exit(exit_code);;
        } else {                                                                    // parent process
            // adds process to the hashtable
            struct nlist *newproc = insert(command, ch_pid, num_commands);          // new process node
            clock_gettime(CLOCK_MONOTONIC, &newproc->start);                        // gets start time

            strcpy(pid_name_out, "");                                               // initializes pid_name_out properly
            strcpy(pid_name_err, "");
            
            // filenames for file descriptors
            sprintf(pid_name_out, "%d", ch_pid);                                    // converts int arguments to string args
            strcpy(pid_name_err, pid_name_out);                                     // copies PID string in out filename to err filename

            // open respective file descriptors for each process
            int fd_out = open(strcat(pid_name_out, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_err = open(strcat(pid_name_err, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

            // duplicate file descriptors
            dup2(fd_out, STDOUT_FILENO);
            dup2(fd_err, STDERR_FILENO);

            // executes each command, and returns exit code
            // printf("command = %s\n", newproc->command);
            printf("Starting command %d: child %d pid of parent %d\n", num_commands, ch_pid, getpid());
            // following line courtesy of L. Sicard-Nöel
            fflush(stdout);                                                         // cleans stdout buffer by writing its contents immediately to stdout
        }
    }

    // parent process
    int status;

    // Process API slides, courtesy of Dr. William Andreopoulos
    // waits for each child process to finish
    while ((ch_pid = wait(&status)) >= 0) {
    	char *res_command = (char *)malloc(sizeof(char) * MAX_COMMAND_CHARS);
        if (ch_pid > 0) {
            struct nlist *node = lookup(ch_pid);                                    // node in the hashtable with command
            strcpy(pid_name_out, "");                                               // initializes pid_name_out properly
            strcpy(pid_name_err, "");

            // filenames for file descriptors
            sprintf(pid_name_out, "%d", ch_pid);                                    // converts int arguments to string args
            strcpy(pid_name_err, pid_name_out);                                     // copies PID string in out filename to err filename

            // open respective file descriptors for each process
            int fd_out = open(strcat(pid_name_out, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
            int fd_err = open(strcat(pid_name_err, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

            // duplicate file descriptors
            dup2(fd_out, STDOUT_FILENO);
            dup2(fd_err, STDERR_FILENO);


            clock_gettime(CLOCK_MONOTONIC, &node->finish);
            // in seconds
            double elapsed_time = elapsed(node->start, node->finish);

            if (elapsed_time > 2.0)
                strcpy(res_command, node->command);

            // exits program
            printf("Finished child %d pid of parent %d\n", node->pid, getpid());
            printf("Finished at %ld, runtime duration %f\n", node->finish.tv_sec, elapsed_time);
            fflush(stdout);

            // receive signal from child process
            if (WIFEXITED(status)) {                                                // exited normally
                fprintf(stderr, "Exited with exit code = %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {                                       // exited abnormally with signal
                fprintf(stderr, "Terminated with signal %d\n", WTERMSIG(status));
            }

            free(node->command);
            free(node);

            if (elapsed_time > 2.0) {                                               // command restarts
                int index = 1;
                ch_pid = fork();                                                    // ch_pid is now the PID of the restarted process

                if (ch_pid < 0) {                                                   // forking error
                    fprintf(stderr, "fork() error");                                // display message
                    exit(2);                                                        // exit process
                } else if (ch_pid == 0) {                                           // child process
                    int actual_child_pid = getpid();                                // pid of child process

                    strcpy(pid_name_out, "");                                       // initializes pid_name_out properly
                    strcpy(pid_name_err, "");

                    sprintf(pid_name_out, "%d", actual_child_pid);                  // converts int arguments to string args
                    strcpy(pid_name_err, pid_name_out);                             // copies PID string in out filename to err filename

                    // opens the necessary files PID.out and PID.err
                    int fd_out = open(strcat(pid_name_out, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
                    int fd_err = open(strcat(pid_name_err, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

                    // courtesy of L. Sicard-Nöel
                    // duplicate file descriptors
                    dup2(fd_out, STDOUT_FILENO);
                    dup2(fd_err, STDERR_FILENO);
                    fflush(stdout);
                    fflush(stderr);

                    // tokenize each command line argument
                    // from https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
                    // from https://stackoverflow.com/questions/15472299/split-string-into-tokens-and-save-them-in-an-array
                    char *argvals[MAX_ARGS];
                    int argcount = 0;

                    char *p = strtok(res_command, " ");

                    // store tokenized command line arguments into argvals[]
                    while (p != NULL) {
                        argvals[argcount] = p;
                        argcount++;
                        p = strtok(NULL, " ");
                    }
                    argvals[argcount] = NULL;                                       // stop storing command line arguments by pointing to NULL at the end

                    // execute code
                    int exit_code = execvp(argvals[0], argvals);

                    // exit appropriately from the exit code
                    if (exit_code != 0)
                        exit(exit_code);
                } else {                                                            // parent process
                    // adds process to the hashtable
                    struct nlist *resproc = insert(res_command, ch_pid, index);     // new process node
                    clock_gettime(CLOCK_MONOTONIC, &resproc->start);                // gets start time

                    strcpy(pid_name_out, "");                                       // initializes pid_name_out properly
                    strcpy(pid_name_err, "");

                    // filenames for file descriptors
                    sprintf(pid_name_out, "%d", ch_pid);                            // converts int arguments to string args
                    strcpy(pid_name_err, pid_name_out);                             // copies PID string in out filename to err filename

                    // open respective file descriptors for each process
                    fd_out = open(strcat(pid_name_out, ".out"), O_RDWR | O_CREAT | O_APPEND, 0777);
                    fd_err = open(strcat(pid_name_err, ".err"), O_RDWR | O_CREAT | O_APPEND, 0777);

                    // duplicate file descriptors
                    dup2(fd_out, STDOUT_FILENO);
                    dup2(fd_err, STDERR_FILENO);

                    // executes each command, and returns exit code
                    printf("RESTARTING\n");
                    fprintf(stderr, "RESTARTING\n");
                    // printf("rcommand = %s\n", res_command);
                    printf("Starting command %d: child %d pid of parent %d\n", index, ch_pid, getpid());
                    // following line courtesy of L. Sicard-Nöel
                    fflush(stdout);                                                 // cleans all buffers
                    fflush(stderr);
                }
            } else {
                fprintf(stderr, "spawning too fast\n");
                fflush(stderr);
            }

            // close used resources
            close(fd_out);
            close(fd_err);
        }
        free(res_command);
    }

    free(command);

    return 0;
}

/**
 * Calculates the time elapsed
 * Assumptions          None
 * @param start_time    The start time
 * @param end_time      The end time
 * @return              The elapsed time in seconds
 */
double elapsed(struct timespec start_time, struct timespec end_time) {
    // number of seconds
    long seconds = end_time.tv_sec - start_time.tv_sec;
    // number of nanoseconds converted to seconds
    double nanoseconds = ((double)(end_time.tv_nsec - start_time.tv_nsec)) * pow(10,-9);

    return (double) seconds + nanoseconds;
}



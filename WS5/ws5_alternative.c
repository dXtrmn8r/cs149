/**
 * Code that prints "hello world from PID xxx" where xxx is the process ID of the current process running.
 *
 * Author:              Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:  02/21/2023
 * Creation date:       02/21/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TIMES 4

/**
 * Main method that forks this parent process into a new child process twice in order to print "hello world..." four times.
 * Assumptions:         None
 * Input Params:        None
 * Returns 0 for success.
 */
int main(void) {
    
    for (int i = 0; i < MAX_TIMES; i++) {
        int pid = fork();
        if (pid == 0)
            return 0;
        else
            printf("hello world from PID %d, PPID %d\n", getpid(), getppid());
    }

    return 0;
}

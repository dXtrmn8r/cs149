/**
 *  Description:                    A program that lists all the names from a given text file as well as how many of each name in a line there are.
 *
 *  Author names:                   Darren Peralta, Henry Choy
 *  Author emails:                  {darrencarl.peralta,henry.choy}@sjsu.edu
 *  Last modified date:             03/05/2023
 *  Creation date:                  02/15/2023
 *
 *  Updated after assignment 1 has been graded.
 */

#include <stdio.h>
#include <string.h>                 // necessary for string functions
#include <ctype.h>                  // necessary for character functions
#include <stdbool.h>                // to use booleans in C
#include <stdlib.h>                 // to be able to use malloc and free operations
#include <unistd.h>                 // to be able to use pipe and fork functions
#include <sys/wait.h>               // to be able to use wait functions

#define MAX_NAMES           100     // maximum number of names to read
#define MAX_CHARS           30      // maximum number of characters to read

// error messages
#define USAGE_ERROR         129
#define PIPE_ERROR          130
#define FORK_ERROR          131
#define FILE_NOT_FOUND_ERR  404

/**
 * Suggested by Dr. William Andreopoulos <william.andreopoulos@sjsu.edu>
 *
 * Stores a record of the name, as well as how many characters it has encountered in a variable.
 */
struct name_record {
    char name[MAX_CHARS];
    int count;
};

/**
 * Method that returns true if all the characters in a string are whitespace.
 * Assumptions:                     None
 * Input Parameters:                s - a pointer to a constant character array/string to check for whitespace.
 * Returns:                         true - if all the characters in s are whitespace
 *                                  false - if there is at least one whitespace character
 */
bool is_blank(const char* s) {
    // while there are characters to be read.
    // this will terminate if s points to a null character
    while (*s) {
        // if s does not point to a whitespace character
        if (!isspace(*s))
            return false;
        s++;
    }
    return true;
}



/**
 * Main method that lists ll the names from a given text file as well as how many of each name in a line there are.
 * No assumptions.
 * Input Parameters:                argc - number of command line arguments
 *                                  argv - array of command line arguments (strings)
 * Returns:                         0 on success
 *                                  1 if the file does not exist
 */
int main(int argc, const char *argv[]) {
    
    if (argc < 2) {                                 // if there is no file specified
        fprintf(stderr, "Usage: %s file1, file2, ...\n", argv[0]);
        return USAGE_ERROR;
    }
    
    unsigned long lines_read = 0;                   // indicates the number of lines read
    long bytes_read;                                // indicates the number of bytes read
    struct name_record names[MAX_NAMES];            // record of names
    int names_stored = 0;                           // number of names stored

    int fd[2];                                      // file descriptors for pipe

    
    // initializes each element in name array to their default values
    for (int i = 0; i < MAX_NAMES; i++) {
        strcpy(names[i].name,"");
        names[i].count = 0;
    }

    // if pipe fails to open    
    if (pipe(fd) == -1) {
        fprintf(stderr, "ERROR: Pipe failed.");
        return PIPE_ERROR;
    }
    
    size_t size = MAX_CHARS;                        // maximum number of characters to be read
    
    pid_t cpid;                                     // process id for any children spawned in parent process
    
    // each file in command line arguments runs its own thread
    for (int argn = 1; argn < argc; argn++) {
        
        const char *filename = argv[argn];              // filename
        cpid = fork();                                  // forks child process
        
        if (cpid < 0) {                                 // fork failed
            fprintf(stderr, "ERROR: Fork from pid %d failed.", getpid());
            return FORK_ERROR;
        } else if (cpid == 0) {                         // this is the child process
            FILE *file_pointer = fopen(filename, "r");  // opens file with given filename

            int local_names_stored = 0;                 // local record: number of local names stored
            struct name_record local_record[MAX_NAMES]; // local name record
            
            // initialize local name record
            strcpy(local_record[0].name,"");
            local_record[0].count = 0;
            
            if (file_pointer == NULL) {             // if the file is not in the same directory as the exec
                fprintf(stderr, "ERROR: The file \"%s\" does not exist.\n", filename);
                return FILE_NOT_FOUND_ERR;
            }
            
            char *input = NULL;                     // the line to be inputted
            
            // this loop will execute when it hasn't read to the end of the file.
            while ((bytes_read = getdelim(&input, &size, '\n', file_pointer)) != -1) {
                lines_read++;
                bool name_found = false;            // flag indicating the name is already on nameList

                // replaces the newline character with a NULL character
                if (input[bytes_read - 1] == '\n') {
                    input[bytes_read - 1] = '\0';
                    --bytes_read;
                }
                
                // linear searches the entire line is already stored on nameList one by one
                for (int i = 0; i < local_names_stored; i++) {
                    // compares the input with an individual name already stored on nameList
                    if (strcmp(input, local_record[i].name) == 0) {
                        local_record[i].count++;
                        name_found = true;
                        break;
                    }
                }
                
                // if the line contains whitespaces
                if (is_blank(input)) {
                    fprintf(stderr, "Warning - Line %lu is empty.\n", lines_read);
                }
                // if the name is already on the list
                else if (name_found == false) {
                    strcpy(local_record[local_names_stored].name, input);
                    local_record[local_names_stored].count = 1;
                    local_names_stored++;
                }
            }
            
            close(fd[0]);                           // closes reading end of pipe

            // write failures because of unavailable resources
            if (write(fd[1], &local_names_stored, sizeof(int)) < 0) {       // writes number of local names in record to pipe
                fprintf(stderr, "Warning - write failed\n.");
            }
            
            if (write(fd[1], local_record, sizeof(local_record)) < 0) {     // writes local record to pipe
                fprintf(stderr, "Warning - write failed\n.");
            }
            
            // closes the file resource and the input pointer
            free(input);                            // input pointer
            fclose(file_pointer);                   // any open files
            close(fd[1]);                           // writing end of pipe
            return 0;
        }
        
    }
    
    close(fd[1]);                                   // closes writing end of pipe


    for (int argn = 1; argn < argc; argn++) {
        
        int pid_status;                             // exit code status
        
        wait(&pid_status);                          // waits for child processes to finish
       
        // if process exited normally and successfully
        if (WIFEXITED(pid_status) && WEXITSTATUS(pid_status) == 0) {
            int num_local_names;
            struct name_record local_names[100];
            
            // read contents from read end of pipe
            read(fd[0], &num_local_names, sizeof(int));
            read(fd[0], local_names, sizeof(local_names));
                
            bool name_already_stored = false;       // name already stored on global record (names[])
            
            // go through each name from local_names (piped data)
            for (int i = 0; i < num_local_names; i++) {

                // go through each stored names on global record (parent process)
                for (int j = 0; j < names_stored; j++) {
                    if (strcmp(local_names[i].name, names[j].name) == 0) {  // name found
                        name_already_stored = true;
                        names[j].count += local_names[i].count;
                        break;
                    }
                }
                
                // creates a new record if it didn't already exist
                if (name_already_stored == false) {
                    strcpy(names[names_stored].name, local_names[i].name);
                    names[names_stored].count += local_names[i].count;
                    names_stored++;
                }
            }
        }
    }
    
    close(fd[0]);                                   // closes reading end of pipe
    
    
    // prints each name on nameList with the number of names in nameCount
    for (int i = 0; i < names_stored; i++) {
        struct name_record current_name = names[i];
        printf("%s: %d\n", current_name.name, current_name.count);
    }
    
    return 0;
}


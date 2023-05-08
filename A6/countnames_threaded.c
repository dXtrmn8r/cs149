/**
 *  Assignment 6
 *
 *  Description:                    A program that lists all the names from a given text file as well as how many of each name in a line there are.
 *
 *  Author names:                   Darren Peralta, Henry Choy
 *  Author emails:                  {darrencarl.peralta,henry.choy}@sjsu.edu
 *  Last modified date:             05/06/2023
 *  Creation date:                  02/15/2023
 */

#include <stdio.h>
#include <string.h>                 // necessary for string functions
#include <ctype.h>                  // necessary for character functions
#include <stdbool.h>                // to use booleans in C
#include <stdlib.h>                 // to use malloc and free operations
#include <unistd.h>                 // to use getpid()
#include <pthread.h>                // to use locks


#define MAX_CHARS           30      // maximum number of characters to read

#define HASHSIZE            26      // number of buckets in hashtable

// error messages
#define USAGE_ERROR         2

//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;


//thread mutex lock for critical sections of allocating THREADDATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;


//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;


void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
    pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;


//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;


//The name counts.
// You can use any data structure you like, here are 2 proposals: a linked list OR an array (up to 100 names).
//The linked list will be faster since you only need to lock one node, while for the array you need to lock the whole array.
//You can use a linked list template from A5. You should also consider using a hash table, like in A5 (even faster).
struct NAME_STRUCT
{
    char name[30];
    int count;
};
typedef struct NAME_STRUCT THREAD_NAME;

//array of 100 names
THREAD_NAME names_counts[100];

//node with name_info for a linked list
struct NAME_NODE
{
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};

/**
 * hash table functions
 */
int hash(char *c) {

    int hashval = 0;
    for (int i = 0; i < strlen(c); ++i) {
        hashval += c[i];
    }

    return hashval % 26;
}

// hashtable
static struct NAME_NODE *hashtable[HASHSIZE];


struct NAME_NODE *lookup(char* name) {
    struct NAME_NODE *np;
    for (np = hashtable[hash(name)]; np != NULL; np = np->next) {
        if (strcmp(name, np->name_count.name) == 0)
            return np;
    }
    return NULL;
}

struct NAME_NODE *insert(char* name) {
    struct NAME_NODE *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct NAME_NODE*) malloc(sizeof(*np));
        if (np == NULL) return NULL;
        strcpy(np->name_count.name, name);
        np->name_count.count = 1;

        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
    } else {
        np->name_count.count++;
    }
    return np;
}

void FREE_HASHNODE(){
    struct NAME_NODE *np;
    for(int i = 0; i < HASHSIZE; i++){
        while(hashtable[i]!=NULL){
            np = hashtable[i];
            hashtable[i]=np->next;
            free(np);
        }
    }
}

void getTime(char* times) {
    time_t now;
    time(&now);

    unsigned int hr, min, sec, day, mo, yr;
    struct tm *local = localtime(&now);

    hr = local->tm_hour;
    min = local->tm_min;
    sec = local->tm_sec;

    day = local->tm_mday;
    mo = local->tm_mon + 1;             // 0 = January
    yr = local->tm_year + 1900;         // 0 = 1900

    if (hr < 12) // before midday
        sprintf(times,"%02d/%02d/%d %02d:%02d:%02d am", day, mo, yr, hr, min, sec);
    else  // after midday
        sprintf(times,"%02d/%02d/%d %02d:%02d:%02d pm", day, mo, yr, hr - 12, min, sec);
}

static char* timeStr = NULL;

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
 * Assumptions:                     File names are relative to working directory of program
 * Input Parameters:                argc - number of command line arguments
 *                                  argv - array of command line arguments (strings)
 * Returns:                         0 on success
 *                                  1 if the file does not exist
 */
int main(int argc, char *argv[]) {

    if (argc != 3) {                                // if there is no file specified
        fprintf(stderr, "Usage: %s file1, file2\n", argv[0]);
        return USAGE_ERROR;
    }
    printf("================================================== LOG MESSAGES ==================================================\n");
    timeStr = (char*)malloc(40);

    printf("create first thread\n");
    pthread_create(&tid1,NULL,thread_runner,argv[1]);

    printf("create second thread\n");
    pthread_create(&tid2,NULL,thread_runner,argv[2]);

    // printf("wait for first thread to exit\n");
    pthread_join(tid1,NULL);
    printf("first thread exited\n");

    // printf("wait for second thread to exit\n");
    pthread_join(tid2,NULL);
    printf("second thread exited\n");

    printf("================================================== NAME  COUNTS ==================================================\n");
    struct NAME_NODE *np;
    for(int i = 0; i < HASHSIZE; i++){
        np = hashtable[i];
        while(np!=NULL){
            printf("%s: %d\n",np->name_count.name,np->name_count.count);
            np = np->next;
        }
    }

    FREE_HASHNODE();
    free(timeStr);
    exit(0);
}

/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* x)
{
    pthread_t me;

    me = pthread_self();

    FILE *fp;
    char* fileName = (char*) x;

    getTime(timeStr);
    pthread_mutex_lock(&tlock1);
    logindex++;
    printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld (p=%p)\n",
           logindex, me, getpid(), timeStr, me, p);
    pthread_mutex_unlock(&tlock1);

    pthread_mutex_lock(&tlock2); // critical section starts
    if (p==NULL) {
        p = (THREADDATA*) malloc(sizeof(THREADDATA));
        p->creator=me;
    }
    pthread_mutex_unlock(&tlock2);  // critical section ends

    getTime(timeStr);
    pthread_mutex_lock(&tlock1);

    if (p!=NULL && p->creator==me) {
        logindex++;
        printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld and I created THREADDATA %p\n",
               logindex, me, getpid(), timeStr, me, p);
    } else {
        logindex++;
        printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld and I can access the THREADDATA %p\n",
               logindex, me, getpid(), timeStr, me, p);
    }

    pthread_mutex_unlock(&tlock1);

    /**
     * //TODO implement any thread name counting functionality you need.
     * Assign one file per thread. Hint: you can either pass each argv filename as a thread_runner argument from main.
     * Or use the logindex to index argv, since every thread will increment the logindex anyway
     * when it opens a file to print a log message (e.g. logindex could also index argv)....
     * //Make sure to use any mutex locks appropriately
     */
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: The file \"%s\" does not exist.\n", fileName);
    } else {
        getTime(timeStr);
        pthread_mutex_lock(&tlock1);
        logindex++;
        printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld (p=%p)\n",
               logindex, me, getpid(), timeStr, me, p);
        pthread_mutex_unlock(&tlock1);

        char *input = NULL;                     // the line to be inputted
        unsigned long lines_read = 0;           // number of lines read
        long bytes_read;                        // number of bytes read
        size_t size = MAX_CHARS;                // maximum number of characters to read

        // this loop will execute when it hasn't read to the end of the file.
        while ((bytes_read = getdelim(&input, &size, '\n', fp)) != -1) {
            lines_read++;
            // bool name_found = false;            // flag indicating the name is already on nameList

            // if the line contains whitespaces
            if (is_blank(input)) {
                fprintf(stderr, "Warning - file %s line %lu is empty.\n", fileName, lines_read);
                continue;                       // goes back to the start of the loop
            }

            // replaces the newline character with a NULL character
            if (input[bytes_read - 1] == '\n') {
                input[bytes_read - 1] = '\0';
                --bytes_read;
            }

            struct NAME_NODE *np = lookup(input);
            pthread_mutex_lock(&tlock3);
            if (np == NULL) {
                insert(input);
            } else {
                (np->name_count.count)++;
            }
            pthread_mutex_unlock(&tlock3);
        }
    }

    pthread_mutex_lock(&tlock1);
    logindex++;
    pthread_mutex_unlock(&tlock1);

    // TODO use mutex to make this a start of a critical section
    pthread_mutex_lock(&tlock2);
    // critical section starts
    if (p!=NULL && p->creator==me) {
        printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld and I delete THREADDATA\n",logindex, me, getpid(), timeStr, me);
        /**
         * TODO Free the THREADATA object.
         * Freeing should be done by the same thread that created it.
         * See how the THREADDATA was created for an example of how this is done.
         */
        free(p);
        p = NULL;
    } else {
        printf("Logindex %d, thread %ld, PID %d, %s: This is thread %ld and I can access the THREADDATA\n",logindex, me, getpid(), timeStr, me);
    }
    // TODO critical section ends
    pthread_mutex_unlock(&tlock2);

    pthread_exit(NULL);
    return NULL;

} //end thread_runner



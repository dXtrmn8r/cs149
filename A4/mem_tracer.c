#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/file.h>
#include <unistd.h>

/**
 * Program that implements a dynamic array and a linked list of strings.
 *
 * @authors:        Darren Carl Peralta, Henry Choy
 * @emails:         {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified:   04/08/2023
 * Created:         04/06/2023
 */

/**
 * CS149 assignment#4 helper code.
 * See the TODO's in the comments below! You need to implement those.
 */

/**
 * TRACE_NODE_STRUCT is a linked list of
 * pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
 */
struct TRACE_NODE_STRUCT {
    char* functionid;                // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT* next;  // ptr to next frame
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/**--------------------------------
 * function PUSH_TRACE
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do.
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
 */
void PUSH_TRACE(char* p)          // push p on the stack
{
    TRACE_NODE* tnode;
    static char glob[]="global";

    if (TRACE_TOP==NULL) {

        // initialize the stack with "global" identifier
        TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));

        // no recovery needed if allocation failed, this is only
        // used in debugging, not in production
        if (TRACE_TOP==NULL) {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }

        TRACE_TOP->functionid = glob;
        TRACE_TOP->next=NULL;
    }//if

    // create the node for p
    tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (tnode==NULL) {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }//if

    tnode->functionid=p;
    tnode->next = TRACE_TOP;  // insert fnode as the first in the list
    TRACE_TOP=tnode;          // point TRACE_TOP to the first node

} // end PUSH_TRACE

/**
 * function POP_TRACE
 * Pop a function call from the stack
 */
void POP_TRACE()    // remove the op of the stack
{
    TRACE_NODE* tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);

} // end POP_TRACE



/** 
 * function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance
 * For example, it returns a string that looks like: global:funcA:funcB:funcC.
 * Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global
 */
char* PRINT_TRACE()
{
    int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE* tnode;
    static char buf[100];

    if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
        strcpy(buf,"global");   // still in the `global' area
        return buf;
    }

    /* peek at the depth(50) top entries on the stack, but do not
       go over 100 chars and do not go over the bottom of the
       stack */

    sprintf(buf,"%s",TRACE_TOP->functionid);
    length = strlen(buf);                  // length of the string so far
    for(i=1, tnode=TRACE_TOP->next;
        tnode!=NULL && i < depth;
        i++,tnode=tnode->next) {
        j = strlen(tnode->functionid);             // length of what we want to add
        if (length+j+1 < 100) {              // total length is ok
            sprintf(buf+length,":%s",tnode->functionid);
            length += j+1;
        }else                                // it would be too long
            break;
    }
    return buf;
} // end PRINT_TRACE

/**-----------------------------------------
 * function REALLOC calls realloc
 * TODO REALLOC should also print info about memory usage.
 * TODO For this purpose, you need to add a few lines to this function.
 * For instance, example of print out:
 * "File mem_tracer.c, line X, function F reallocated the memory segment at address A to a new size S"
 * Information about the function F should be printed by printing the stack (use PRINT_TRACE)
 */
void* REALLOC(void* p,int t,char* file,int line)
{
    p = realloc(p,t);
    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n",
           file,
           line,
           PRINT_TRACE(),
           p,
           t);
    return p;
}

/**-------------------------------------------
 * function MALLOC calls malloc
 * TODO MALLOC should also print info about memory usage.
 * TODO For this purpose, you need to add a few lines to this function.
 * For instance, example of print out:
 * "File mem_tracer.c, line X, function F allocated new memory segment at address A to size S"
 * Information about the function F should be printed by printing the stack (use PRINT_TRACE)
 */
void* MALLOC(int t,char* file,int line)
{
    void* p;
    p = malloc(t);
    printf("File %s, line %d, function %s allocated new memory segment at address %p to a new size %d\n",
           file,
           line,
           PRINT_TRACE(),
           p,
           t);
    return p;
}

/**----------------------------------------------
 * function FREE calls free
 * TODO FREE should also print info about memory usage.
 * TODO For this purpose, you need to add a few lines to this function.
 * For instance, example of print out:
 * "File mem_tracer.c, line X, function F deallocated the memory segment at address A"
 * Information about the function F should be printed by printing the stack (use PRINT_TRACE)
 */
void FREE(void* p,char* file,int line)
{
    free(p);
    printf("File %s, line %d, function %s deallocated memory segment at address %p\n",
           file,
           line,
           PRINT_TRACE(),
           p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)


/**-----------------------------------------
 * STRING_NODE is a linked list of a node of char*s, that acts like a stack.
 * *s		pointer to the first character of the string
 * index	index of the string
 * *next	pointer to the next node in the linked list
 */
typedef struct STRING_NODE {
    char                    *s;             // string stored
    int                     index;          // index in linked list
    struct STRING_NODE      *next;          // next node in the linked list
} STRING_NODE;

static STRING_NODE *HEAD = NULL;            // head of the linked list

/**
 * PUSH_STRING pushes a string (text) to the top of the stack.
 * Assumptions:     None
 * Input @params:   *s      pointer to the start of the string (char*)
 *                  index   index of string
 * Returns nothing
 */
void PUSH_STRING(char* s, int index) {
    PUSH_TRACE("PUSH_STRING");
    struct STRING_NODE *temp;

    temp = (struct STRING_NODE *) malloc(sizeof(struct STRING_NODE));
    temp->s = s;
    temp-> index = index;

    if (HEAD == NULL) {
        HEAD = temp;
        HEAD->next = NULL;
    } else {
        temp->next = HEAD;
        HEAD = temp;
    }

    POP_TRACE();
}// end PUSH_STRING

/**
 * POP_STRING pops the string (text) at the top of the stack.
 * Assumptions:     None
 * Input @params:   None
 * Returns nothing
 */
void POP_STRING() {
    PUSH_TRACE("POP_STRING");

    struct STRING_NODE *temp;
    temp = HEAD;
    HEAD = temp->next;
    // free(temp->s);
    free(temp);

    POP_TRACE();
}// end POP_STRING

/**
 * FREE_LINKEDLIST  frees all of the nodes used in the linked list.
 * Assumptions:     None
 * Input @params:   None
 * Returns nothing
 */
void FREE_LINKEDLIST() {
    PUSH_TRACE("FREE_LINKEDLIST");
    while (HEAD != NULL)
        POP_STRING();
    POP_TRACE();
}

/**
 * print_LL prints the stack in order to stdout
 * Assumptions:     None
 * Input @params:   *node   the node of the string whose data needs to be printed
 * Returns nothing
 */
void print_LL(STRING_NODE *node) {
    PUSH_TRACE("print_LL");
    if (node->next != NULL)
        print_LL(node->next);

    printf("array[%d] = %s\n", node->index, node->s);
    POP_TRACE();
}


// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done
/**
 * Program that takes a list of strings, stores them in a dynamically-allocated array.
 * Assumptions:         array can initially store up to 10 char*, increases by 10 if limit is reached.
 */
void make_extend_array()
{
    PUSH_TRACE("make_extend_array");
    size_t bufflen = 200;

    char    **array = NULL;
    int     ROWS = 10;
    int     NUM_COMMANDS = 0;

    char    *input = (char *) malloc(bufflen * sizeof(char));       // variable where input is stored.

    // make array
    array = (char**) malloc(sizeof(char*) * ROWS);                  // creates first 10 rows

    // as long as there is input to accept
    while(getline(&input, &bufflen, stdin) != -1) {
        input[strlen(input) - 1] = '\0';                            // clear newline character
        array[NUM_COMMANDS] = strdup(input);                        // make reference to string on array

        // mem tracing
        printf("File %s, line %d, function %s allocated new memory segment at address %p to of size %lu\n",
                __FILE__,
                __LINE__ - 1,
                PRINT_TRACE(),
                array[NUM_COMMANDS],
                sizeof(char) * bufflen);

        // push command to array
        PUSH_STRING(array[NUM_COMMANDS], NUM_COMMANDS);
        NUM_COMMANDS++;

        // check if realloc is needed (if more ROWS are needed)
        if (NUM_COMMANDS >= ROWS) {
            ROWS += 10;
            array = realloc(array, sizeof(char *) * ROWS);
        }
    }

    // output linked list
    print_LL(HEAD);

    // free linked list
    FREE_LINKEDLIST();

    //now deallocate array and other pointers used.
    for(int i = 0; i < NUM_COMMANDS; i++)
        free(array[i]);
        
    free(array);
    free(input);

    POP_TRACE();
    return;
} //end make_extend_array


// ----------------------------------------------
// function main
int main()
{
    int fd = open("memtrace.out", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
    dup2(fd, STDOUT_FILENO);
    PUSH_TRACE("main");

    make_extend_array();

    POP_TRACE();        // pop main    
    POP_TRACE();        // nothing left, so just calls free
    return 0;
} // end main

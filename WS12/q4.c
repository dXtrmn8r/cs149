/**
 *  Author names:           Darren Peralta, Henry Choy
 *  Author emails:          {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 *  Last modified:          04/23/2023
 *  Creation date:          04/20/2023
 *
 *  Memory leaks will occur since pointer p was not freed.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int*) malloc(sizeof(int));
    *p = 5;

    return 0;
}

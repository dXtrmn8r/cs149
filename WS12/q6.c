/**
 *  Author names:           Darren Peralta, Henry Choy
 *  Author emails:          {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 *  Last modified:          04/23/2023
 *  Creation date:          04/20/2023
 *
 *  q6.c:24 will cause an invalid read since *data was read after calling free on it, so it will have unpredictable behavior since it will possibly read garbage data. valgrind reports a read error.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
//    int *data = (int*) malloc(100 * sizeof(int));
    int *data = (int*) calloc(100, sizeof(int));
//    data[100] = 0;

    for (int i = 0; i < 100; i++) {
//        printf("data[%u] = %d\n", i, data[i]);
    }

    free(data);

    printf("data[%u] = %d\n", 20, data[20]);

    return 0;
}

/**
 *  Author names:           Darren Peralta, Henry Choy
 *  Author emails:          {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 *  Last modified:          04/23/2023
 *  Creation date:          04/20/2023
 *
 *  q5:16 will cause an invalid write since it is originally not part of the allocated memory. valgrind reports an invalid write.
 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int));           // HC: NOTE THE DIFFERENCE BETWEEN THE TWO LINES. USE THIS AS DEFAULT.
//    int *data = (int*) calloc(100, sizeof(int));
    data[100] = 222333;

//    for (int i = 0; i < 100; i++) {
//        printf("data[%u] = %d\n", i, data[i]);
//    }

    free(data);
    return 0;
}

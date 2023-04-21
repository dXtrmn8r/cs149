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

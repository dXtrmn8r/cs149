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
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int*) malloc(100 * sizeof(int));
    data[100] = 0;

    for (int i = 0; i < sizeof(data)/sizeof(int); i++) {
        printf("data[%u] = %d\n", i, data[i]);
    }

    free(data);
    return 0;
}

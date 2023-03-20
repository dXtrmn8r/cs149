#include <stdio.h>

#define NUM_VARS 4

/* Define your function here */
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {
    int temp;
    
    temp = *userVal1;

    *userVal1 = *userVal2;
    *userVal2 = temp;

    temp = *userVal3;

    *userVal3 = *userVal4;
    *userVal4 = temp;
}

int main(void) {

    /* Type your code here. Your code must call the function.  */
    int data[NUM_VARS];

    for (int i = 0; i < NUM_VARS; i++) {
        scanf("%d", &data[i]);
    }

    int *a, *b, *c, *d;

    a = &data[0];
    b = &data[1];
    c = &data[2];
    d = &data[3];

    SwapValues(a, b, c, d);

    printf("%d %d %d %d\n", *a, *b, *c, *d);

    return 0;
}

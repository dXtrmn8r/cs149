#include <stdio.h>

/* Define your function here */ 
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
   int tempVal;
   
   tempVal = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = tempVal;
   
   tempVal = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = tempVal;
   
}

int main(void) {
   
   /* Type your code here. Your code must call the function.  */
   int numArr [4];
   int *num1, *num2, *num3, *num4;
   
   for (int i = 0; i < 4; i++){
      scanf("%d", &numArr[i]);
   }
   
   num1 = &numArr[0];
   num2 = &numArr[1];
   num3 = &numArr[2];
   num4 = &numArr[3];
   
   SwapValues(num1, num2, num3, num4);
   
   printf ("%d %d %d %d\n", *num1, *num2, *num3, *num4);

   return 0;
}

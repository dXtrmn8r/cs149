#include <stdio.h>

/**
 * Description:         A program that divides an integer userNum by x three times.
 *
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:  02/12/2023
 * Creation date:       02/10/2023
 */

/**
 * Main method that divides an integer userNum by x three times.
 * Assumptions:         All inputs can be parsed as integers.
 * Input Params:        userNum - dividend. This is the number to be divided.
 *                      x - divisor. This is the number to be divided by.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int userNum;
   int x;
   scanf("%d %d", &userNum, &x);
   
   for (int i = 0; i < 3; i++) {
      printf("%d", userNum /= x);
      if (i != 2) printf(" ");
   }
   
   printf("\n");

   return 0;
}


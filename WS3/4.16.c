/**
 * Description:         Program that inputs any number of positive integers, and prints their sum and the largest of these positive integers.
 *
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:  
 * Creation date:       
 */
#include <stdio.h>

/**
 * Main method that fulfills the described program.
 * Assumptions:         All inputs can be parsed as integers.
 * Input params:        Any number of positive integers followed by a negative integer to terminate the program.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int x;
   int sum = 0;
   int n = 0;
   int max;
   
   do {
      scanf("%d", &x);
      if (x < 0) break;
      else if (n == 0 || x > max)
         max = x;
      
      sum += x;
      n++;
   } while (x >= 0);
   
   printf("%d %0.2lf\n", max, (double) sum / (double) n);

   return 0;
}


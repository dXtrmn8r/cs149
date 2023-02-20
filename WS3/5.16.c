/**
 * Program that prints a maximum of twenty integers in reverse order.
 *
 * Author names:            Darren Peralta, Henry Choy
 * Author emails:           {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:      02/20/2023
 * Creation date:           02/14/2023
 */
#include <stdio.h>

/**
 * Main method that accepts a positive integer, num_integers, followed by that many integers.
 * It then prints the last num_integers in reverse order.
 *
 * Assumptions:             All user input can be parsed as integers. A maximum number of twenty integers can be printed out here.
 * Input params:            An integer num_integers, followed by num_integers integers.
 * Returns 0 for success.
 */
int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

   /* Type your code here. */
   int num_integers = 0;
   scanf("%d", &num_integers);
   
   for (int i = 0; i < num_integers; i++) {
      scanf("%d", &userVals[i]);
   }
   
   for (int j = num_integers - 1; j >= 0; j--) {
      printf("%d,", userVals[j]);
   }
   printf("\n");
   

   return 0;
}


/**
 * Program that given a user-inputted list of integers (maximum 20), a lower bound and an upper bound,
 * Prints all the integers in that list that is within that range (inclusive of the bounds).
 *
 * Author names:                    Darren Peralta, Henry Choy
 * Author emails:                   {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:              02/20/2023
 * Creation date:                   02/15/2023
 */
#include <stdio.h>

#define MAX_INTEGERS    20
/**
 * Program that accepts an integer, followed by a list of that many integers, an integer acting as a lower bound, and an integer acting as an upper bound.
 * Prints all integers in the list that is greater than or equal to the lower bound and less than or equal to the upper bound.
 *
 * Assumptions:                     List is a maximum of twenty integers.
 * Input params:                    None.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int numIntegers;
   scanf("%d", &numIntegers);
   
   int list[MAX_INTEGERS];
   
   for (int i = 0; i < numIntegers; i++) {
      scanf("%d", &list[i]);
   }
   
   int lower;
   scanf("%d", &lower);
   int upper;
   scanf("%d", &upper);
   
   for (int i = 0; i < numIntegers; i++) {
      int x = list[i];
      
      if (x >= lower && x <= upper)
         printf("%d,", x);
   }
   printf("\n");

   return 0;
}


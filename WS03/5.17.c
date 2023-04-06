/**
 * Given an odd number of positive integers (for a maximum of nine) sorted in increasing order, it prints out the middle number on the list (median).
 *
 * Author names:                    Darren Peralta, Henry Choy
 * Author emails:                   {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:              02/20/2023
 * Creation date:                   02/15/2023
 */
#include <stdio.h>

/**
 * Main method that does as described above.
 *
 * Assumptions:                     The list will contain an odd number of positive integers.
 * Input params:                    All input can be parsed into integers.
 * Returns 0 for success.
 */
int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   /* Type your code here. */
   int i = 0;                       // number of integers stored
   int input = 0;                   // integers inputted by the user

   // accepts up to nine integers to be inputted
   do {   
      scanf("%d", &input);
      // if input is positive
      if (input > 0) {
         // if there are already nine integers on the list
         if (i == 9) {
            printf("Too many numbers\n");
            return 1;
         } else {                   // if there is still room for more integers to be stored.
            userValues[i] = input;
            i++;
         }
      }
   } while (input > 0);             // wasteful, but at least it ensures that this code runs at least once in case the user inputs a negative integer.
   
   printf("Middle item: %d\n", userValues[(i-1)/2]);

   return 0;
}

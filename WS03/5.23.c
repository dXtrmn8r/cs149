/**
 * Program that prints the two smallest integers from a list of user-inputted integers.
 * Author names:                Darren Peralta, Henry Choy
 * Author emails:               {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:          02/20/2023
 * Creation date:               02/15/2023
 */
#include <stdio.h>

/**
 * Main method that does the above-described program.
 * It accepts a single integer, followed by that many integers.
 * Assumptions:                 List will be a maximum of twenty integers. All inputs are integers.
 * Input params:                None.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int numElements;
   scanf("%d", &numElements);
   
   int list[20];
   int smallest[2];
   
   // user inputs integers here
   for (int i = 0; i < numElements; i++) {
      scanf("%d", &list[i]);
   }
   
   // takes care of sorting the smallest two integers
   if (list[0] < list[1]) {
      smallest[0] = list[0];
      smallest[1] = list[1];
   } else {
      smallest[0] = list[1];
      smallest[1] = list[0];
   }
   
   // traverses the rest of the numbers on the list
   for (int i = 2; i < numElements; i++) {
       // if the number is smaller than the smallest integer
       if (list[i] < smallest[0]) {
           smallest[1] = smallest[0];
           smallest[0] = list[i];
       } else if (list[i] < smallest[1])            // if the number is smaller than the second-smallest integer
           smallest[1] = list[i];
   }
   
   printf("%d and %d\n", smallest[0], smallest[1]);

   return 0;
}


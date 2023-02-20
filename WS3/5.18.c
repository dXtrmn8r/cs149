/**
 * Program that prints all user-inputted integers up to a given threshold.
 * It accepts a single integer inputLength, followed by that many integers.
 * The user will then input one more integer indicating the threshold.
 *
 * Author names:                    Darren Peralta, Henry Choy
 * Author emails:                   {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:              02/20/2023
 * Creation date:                   02/15/2023
 */
#include <stdio.h>

/**
 * Main method that does the above-described code.
 *
 * Assumptions:                     All input can be parsed as integers.
 *                                  List will always contain less than twenty integers.
 * Input params:                    None
 * Returns 0 for success.
 */
int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user

   /* Type your code here. */
   int inputLength;
   scanf("%d", &inputLength);
   
   // scans that many integers
   for (int i = 0; i < inputLength; i++)
      scanf("%d", &userValues[i]);
   
   int threshold;
   scanf("%d", &threshold);
   
   // checks if each number in the list is equal to or less than some kind of threshold
   for (int i = 0; i < inputLength; i++) {
      if (userValues[i] <= threshold)
         printf("%d,", userValues[i]);
   }
   
   printf("\n");

   return 0;
}


/**
 * Description:         Program that determines whether the array of integers all have multiples of 10, all have no multiples of 10, or a mixture of the two.
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:  03/13/2023
 * Date created:        03/13/2023
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_ITEMS_LIST 20

/* Define your function here */

/**
 * Returns true if all the numbers in an array of integers are multiples of 10.
 * Assumptions:         None
 * Input Parameters:    inputVals[] - array of integers
 *                      numVals     - number of integers in array.
 * Returns:             true if all the numbers in array are multiples of 10.
 */
bool IsArrayMult10(int inputVals[], int numVals) {
   for (int i = 0; i < numVals; i++) {              // traverse through array
      // if there is a number that isn't a multiple of 10
      if (inputVals[i] % 10 != 0)
          return false;
   }
   return true;
}

/**
 * Returns true if none of the numbers in an array of integers are multiples of 10.
 * Assumptions:         None
 * Input Parameters:    inputVals[] - array of integers
 *                      numVals     - number of integers in array.
 * Returns:             true if there are no multiples of 10 in array.
 */
bool IsArrayNoMult10(int inputVals[], int numVals) {
   for (int i = 0; i < numVals; i++) {              // traverse through array
      // if there is a number that is a multiple of 10
      if (inputVals[i] % 10 == 0)
          return false;
   }
   return true;
}

/**
 * Main method that implements the program described above.
 * Assumptions:         None
 * Input Parameters:    None
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. Remember to include the bool library*/
   unsigned int array_size;                         // size of the array
   scanf("%d", &array_size);
   
   if (array_size > MAX_ITEMS_LIST)                 // truncates array to its default maximum size
      array_size = MAX_ITEMS_LIST;
   
   int array[array_size];
   
   // inputs integers to integer array
   for (unsigned int i = 0; i < array_size; i++) {
      scanf("%d", &array[i]);
   }
   
   if (IsArrayMult10(array, array_size))            // if 10 divides all numbers in array
      printf("all multiples of 10\n");
   else if (IsArrayNoMult10(array, array_size))     // if 10 doesn't divide any number in array
      printf("no multiples of 10\n");
   else                                             // neither case
      printf("mixed values\n");

   return 0;
}


#include <stdio.h>

/**
 *  Description:        This module prints a formatted arrow to the console.
 *  Author names:       Darren Peralta, Henry Choy
 *  Author emails:      {darrencarl.peralta,henry.choy}@sjsu.edu
 *  Last modified date: 02/05/2023
 *  Creation date:      01/25/2023
 */

/**
 * This function prints a formatted arrow to the console.
 * No assumptions, input parameters.
 * Returns 0 for success.
 */
int main(void) {
   int baseInt;
   int headInt;
   scanf("%d %d", &baseInt, &headInt);
   
   // prints an arrow line by line. The arrow takes 7 lines
   for (int i = 1; i <=7; i++) {
      // left half of the arrow. this will be baseInt or ' '.
      for (int j = 0; j < 4; j++) {
	 // if it is the middle of the arrow
         if (i >= 3 && i <= 5) {
            printf("%d",baseInt);
         } else {
            printf(" ");
         }
      }

      int upperLimit;		// maximum number of characters in the right half of the arrow
      // top of the arrow
      if (i > 4) upperLimit = 8 - i;
      else upperLimit = i;

      // right half of the arrow
      for (int j = 0; j < upperLimit; j++) {
         printf("%d",headInt);
      }
      printf("\n");
   }

   return 0;
}


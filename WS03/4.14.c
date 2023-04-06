/**
 *	Description:		Program that prints the binary digits of a positive decimal integer in reverse.
 *
 *	Author names:		Darren Peralta, Henry Choy
 *	Author emails:		{darrencarl.peralta, henry.choy}@sjsu.edu
 *	Last modified date:	02/17/2023
 *	Created date:		02/17/2023
 */
#include <stdio.h>

/**
 * 	Main method that executes the described code.
 * 	Assumptions:		None
 * 	Input params:		Any integer. Nothing would happen if the user inputs a nonpositive integer.
 * 	Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int x;
   scanf("%d", &x);
   
   // executes while there are still binary digits to write
   // by checking whether x > 0
   while (x > 0) {
      printf("%d", x % 2);
      x /= 2;
   }
   printf("\n");
   
   return 0;
}


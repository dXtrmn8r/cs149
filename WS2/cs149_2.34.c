#include <stdio.h>
/**
 * Program that prints a custom welcome message.
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:  02/12/2023
 * Creation date:       02/10/2023
 */

/**
 * Main method that prints welcome message.
 * Assumptions:         All inputs are character arrays.
 * Input params:        userName - character array that can accept a maximum of fifty elements.
 *                                 It is also the name of the user.
 * Returns 0 for success.
 */
int main(void) {
   char userName[50];
   
   scanf("%s", userName);
   /* Type your code here. */
   printf("Hello %s, and welcome to CS Online!\n", userName);

   return 0;
}


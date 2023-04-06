/**
 * Program that prints a line of text as input, and outputs that line of text in reverse.
 * This program ends when the user inputs "Done", "done", or "d".
 *
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified:       03/06/2023
 * Date created:        02/21/2023
 */
#include <stdio.h>
#include <string.h>

/**
 * Main method that does the above program.
 *
 * Assumptions:         all input is parsable by text.
 *                      only the first fifty characters will be reversed.
 * Input params:        none
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   char input[50] = "";
   while (1) {                // non-zero value means true, zero means false
      fgets(input, 50, stdin);
      if (strcmp(input, "Done\n") == 0 || strcmp(input, "done\n") == 0 || strcmp(input, "d\n") == 0)
         break;
      else {
         for (int i = strlen(input) - 2; i >= 0; i--)
            printf("%c", input[i]);
         printf("\n");
      }
   }
   
   return 0;
}


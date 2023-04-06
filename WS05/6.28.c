/**
 * Program that removes non-alphabetic characters.
 *
 * Authors:                 Darren Peralta, Henry Choy
 * Author emails:           {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:      03/06/2023
 * Date created:            02/21/2023
 **/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define your function here */

/**
 * Removes non-alphabetic characters from the string.
 *
 * Assumptions:             Only considers the first fifty characters in the text.
 * Input Parameters:        char userString[] - string to remove non-alphabetic characters from.
 *                          char userStringAlphaOnly[] - string containing only alphabetic characters.
 *
 * Returns nothing.
 */
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   
   int j = 0;
   
   for (int i = 0; i < strlen(userString); i++) {
      if (isalpha(userString[i])) {
          userStringAlphaOnly[j] = userString[i];
          j++;
      }
   }
}

/**
 * Main method that implements RemoveNonAlpha by taking user input and removing non-alphabetic characters.
 *
 * Assumptions:             Only considers the first fifty characters in the text.
 * Input Parameters:        none
 *
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   char input[50] = "";
   char result[50] = "";
   
   fgets(input, 50, stdin);
   
   RemoveNonAlpha(input, result);
   
   printf("%s\n", result);

   return 0;
}


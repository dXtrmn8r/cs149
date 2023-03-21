/**
 * Program that checks if a word or phrase is a palindrome (meaning it is the same when read forward or backward).
 * It accounts for multiple words as well.
 *
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified:       03/13/2023
 * Date created:        03/10/2023
 */

#include <stdio.h>
#include <string.h>

/**
 * Main method that does the above program.
 *
 * Assumptions:         all input is parsable by text.
<<<<<<< HEAD
 *                      the inputted string will not exceed 50 characters.
=======
 *                      the inputted string will not excceed 50 characters.
>>>>>>> e1f7b51385118b04337fd55c905dff15b69f83b2
 * Input params:        none
 * Returns 0 for success.
 */
int main(void) {
   char userStr[51];
   char strNoSpaces[51];
<<<<<<< HEAD

   int leftC = 0;

   fgets(userStr,  51, stdin);

   strcpy(strNoSpaces, userStr);

   int rightC = strlen(strNoSpaces) - 1;

   while (rightC > leftC){ //Loops while the rightCharacter index is greater than the leftCharacter index
      if(strNoSpaces[leftC] == ' '){
         strNoSpaces[leftC++] = strNoSpaces[leftC];
      }
      if(strNoSpaces[rightC] == ' '){
         strNoSpaces[rightC--] = strNoSpaces[rightC];
=======
   
   int leftC = 0;
   
   fgets(userStr,  51, stdin);
   
   strcpy(strNoSpaces, userStr);
   
   int rightC = strlen(strNoSpaces) - 1;
      
   while (rightC > leftC){ //Loops while the rightCharacter index is greater than the leftCharacter index
      if(strNoSpaces[leftC] == ' '){
         strNoSpaces[leftC] = strNoSpaces[leftC + 1];
         leftC++;
      }
      if(strNoSpaces[rightC] == ' '){
         strNoSpaces[rightC] = strNoSpaces[rightC - 1];
         rightC--;
>>>>>>> e1f7b51385118b04337fd55c905dff15b69f83b2
      }
      if(strNoSpaces[leftC++] != strNoSpaces[rightC--]){
         printf("not a palindrome: %s\n", userStr);
         return 0;
      }
   }
<<<<<<< HEAD

=======
   
>>>>>>> e1f7b51385118b04337fd55c905dff15b69f83b2
   printf("palindrome: %s\n", userStr);
   return 0;
}

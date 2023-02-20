/**
 * Program that prints all the words from a user-inputted list with a certain character that is also inputted by the user.
 *
 * Author names:                    Darren Peralta, Henry Choy
 * Author emails:                   {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:              02/20/2023
 * Creation date:                   02/15/2023
 */

#include <stdio.h>
#include <string.h>

#define MAX_WORDS       20
#define MAX_CHARACTERS  10

/**
 * Program that accepts an integer followed by that many strings/character arrays.
 * This is then followed by a single character to search in each string on the list.
 * Assumptions:                     There will be a maximum of twenty words in each list.
 *                                  Each word is a maximum of ten characters.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int numValues;                   // number of words on the list to input
   scanf("%d", &numValues);
   
   char wordList[MAX_WORDS][MAX_CHARACTERS]; // array of words
   
   // allows the user to input words
   for (int i = 0; i < numValues; i++) {
       scanf("%s", wordList[i]);
   }
   
   char search;
   scanf(" %c", &search);
   
   // searches each word for the search character in the list
   for (int i = 0; i < numValues; i++) {
       // if there is no occurrence of the word in the list
       if (strchr(wordList[i], search) != NULL) {
           printf("%s,", wordList[i]);
       }
   }
   printf("\n");

   return 0;
}


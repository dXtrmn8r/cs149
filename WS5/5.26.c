#include <stdio.h>
#include <string.h>

#define MAX_CHARS 50

int main(void) {
   
   /* Type your code here. */
   char input[MAX_CHARS];
   
   fgets(input, MAX_CHARS, stdin);
   
   unsigned int disallowedCharacters = 0;
   
   for (int i = 0; i < strlen(input); i++) {
      if (input[i] == ' ' || input[i] == '.' || input[i] == '!' || input[i] == ',' || input[i] == '\n')
         disallowedCharacters++;
   }
   
   printf("%ld\n", strlen(input) - disallowedCharacters);
   
   return 0;
}


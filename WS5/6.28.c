#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Define your function here */
void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   
   int j = 0;
   
   for (int i = 0; i < strlen(userString); i++) {
      if (isalpha(userString[i])) {
          userStringAlphaOnly[j] = userString[i];
          j++;
      }
   }
}

int main(void) {

   /* Type your code here. */
   char input[50] = "";
   char result[50] = "";
   
   fgets(input, 50, stdin);
   
   RemoveNonAlpha(input, result);
   
   printf("%s\n", result);

   return 0;
}


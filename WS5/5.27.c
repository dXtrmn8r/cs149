#include <stdio.h>
#include <string.h>

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


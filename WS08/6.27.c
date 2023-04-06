#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 50

/* Define your function here */
int CalcNumCharacters(char* userString, char userChar) {
   int count = 0;

    for (int i = 0; i < strlen(userString); ++i) {
        if (userString[i] == userChar)
            count++;
    }

   return count;
}

int main(void) {

   /* Type your code here. */
   char c;
   char *str = (char*) malloc(MAX_CHARS * sizeof(char));
   scanf("%c", &c);
   scanf("%s", str);

   int count = CalcNumCharacters(str, c);
   printf("%d %c", count, c);
   if (count != 1) printf("'s");

   printf("\n");
   free(str);

   return 0;
}

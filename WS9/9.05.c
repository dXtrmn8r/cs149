#include <stdio.h>
#include <string.h>

#define MAX_CHARS 100

int main() {
    char input[MAX_CHARS] = {}, str1[MAX_CHARS] = {}, str2[MAX_CHARS] = {};

    while (1) {
        // Prompt user to enter two strings separated by a comma
        printf("Enter input string:\n");
        fgets(input, MAX_CHARS, stdin);                             // gets input
        if (strcmp(input,"q\n") == 0) break;                        // input for quitting
        strcpy(str1,"\0");                                          // tries to clear str1
        strcpy(str2,"\0");                                          // tries to clear str2
        
        // reads up to any character before spaces and commas, puts to string 1, puts any non-whitespace char after comma to str2
        int numStrings = sscanf(input, "%[^ ,] ,%s", str1, str2);
        // returns number of strings properly read and stored

        if (numStrings != 2) {                                      // invalid
            printf("Error: No comma in string.\n\n");
        } else {                                                    valid
            printf("First word: %s\n", str1);
            printf("Second word: %s\n\n", str2);
        }
    }

    return 0;
}

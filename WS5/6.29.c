#include <stdio.h>
#include <string.h>

/* Define your functions here */ 
void IntToReverseBinary(int integerValue, char binaryValue[]) {
   int x = integerValue;
   
   if (x == 0) {
      binaryValue[0] = '0';
   } else {
      int i = 0;
      while (x != 0) {
         binaryValue[i] = (x % 2) + 48;
         x = x / 2;
         i++;
      }
   }
}

void StringReverse(char inputString[], char reversedString[]) {
   
   int length = strlen(inputString);
   
   for (int i = 0; i < length; i++) {
      reversedString[i] = inputString[length-1 - i];
   }
   reversedString[length] = '\0';
}

int main(void) {

   /* Type your code here. 
      Your code must call IntToReverseBinary() to get
      the binary string of an integer in a reverse order.
      Then call StringReverse() to reverse the string 
      returned from IntToReverseBinary().*/
   int input;
   scanf("%d", &input);
   
   char revresult[32] = "";            // this is a 32-bit/8-byte integer
   char result[32] = "";
   
   IntToReverseBinary(input, revresult);
   StringReverse(revresult, result);
   
   printf("%s\n", result);

   return 0;
}


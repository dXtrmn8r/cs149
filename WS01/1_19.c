#include <stdio.h>

/**
 *  Description:        This module two integers (one inputted at a time), then prints out any mathematical statements. 
 *  Author names:       Darren Peralta, Henry Choy
 *  Author emails:      {darrencarl.peralta,henry.choy}@sjsu.edu
 *  Last modified date: 02/05/2023
 *  Creation date:      01/25/2023
 */

/**
 * Prints out mathematical statements.
 * No assumptions.
 * Two integers inputted (userNum, secondNum) using scanf.
 * Returns 0 for success.
 */
int main(void) {
   int userNum;
   
   printf("Enter integer: ");
   scanf("%d", &userNum);
   /* Type your code here. */
   printf("You entered: %d\n", userNum);
   printf("%d squared is %d\n", userNum, userNum * userNum);
   printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);
   
   int secondNum;
   printf("Enter another integer: ");
   scanf("%d", &secondNum);
   printf("%d + %d is %d\n", userNum, secondNum, userNum + secondNum);
   printf("%d * %d is %d\n", userNum, secondNum, userNum * secondNum);

   return 0;
}


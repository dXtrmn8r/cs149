#include <stdio.h>

/**
 * Description:         Program that prints the smallest of three inputted integers.
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:  02/12/2023
 * Creation date:       02/10/2023
 */
 
/**
 * Main method that prints the smallest of three integers inputted by the user to the console.
 * Assumptions:         All inputs can be parsed to integers.
 * Input Params:        min, x, y - three integers whose minimum needs to be printed to the console.
 * Returns 0 for success.
 */
int main(void) {

   /* Type your code here. */
   int min;
   scanf("%d", &min);
   
   int x;
   scanf("%d", &x);
   if (x < min)
      min = x;
      
   int y;
   scanf("%d", &y);
   if (y < min)
      min = y;
   
   printf("%d\n", min);

   return 0;
}


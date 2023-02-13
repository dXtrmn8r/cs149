#include <stdio.h>
/**
 * Description:         Program that prints the price of a house listing,
 *                      change of that prince since last month,
 *                      and the estimated monthly mortgage according to some formula.
 * 
 * Author names:        Darren Peralta, Henry Choy
 * Author emails:       {darrencarl.peralta,henry.choy}@sjsu.edu
 * Last modified date:  02/12/2023
 * Creation date:       02/10/2023
 */

/**
 * Main method that fulfills description of printing house listing price, 
 * change from previous month, and estimated monthly mortgage.
 * Assumptions:         All inputs can be parsed as integers.
 * Input Params:        currentPrice - current price of the house.
 *                      lastMonthsPrice - price of the house in the month before current.
 * Returns 0 for success.
 */
int main(void) {
   int currentPrice;
   int lastMonthsPrice;
   
   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);
   
   /* Type your code here. */
   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthsPrice);
   printf("The estimated monthly mortgage is $%lf.\n", ((double)currentPrice * 0.051) / 12.0);

   return 0;
}


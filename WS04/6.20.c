#include <stdio.h>
/**
 * Program that converts number of laps to number of miles.
 *
 * Author names:            Darren Peralta, Henry Choy
 * Author emails:           {darrencarl.peralta,henry.choy}@sjsu.edu
 *
 * Last modified date:      02/27/2023
 * Creation date:           02/26/2023
 */

/* Define your function here */
/**
 * Converts number of laps to number of miles by using miles = laps / 4.0
 * Assumptions:             None
 * Input params:            userLaps - number of laps (partial and whole) completed
 * Returns:                 Number of miles by dividing laps by 4.0
 */
double LapsToMiles(double userLaps) {
   return userLaps / 4.0;
}

/**
 * Main method that implements program
 * Assumptions:             All input can be parsed as 64-bit floating point numbers.
 * Input params:            None
 * Returns 0 for success
 */
int main(void) {

   /* Type your code here. Your code must call the function.  */
   double laps;
   scanf("%lf", &laps);

   double miles = LapsToMiles(laps);

   printf("%0.2lf\n", miles);

   return 0;
}

#include <stdio.h>
#include <math.h>

/**
 * Description:     Given three floating point numbers x, y, and z, prints x**z, x**(y**2), absolute value of y, and sqrt(pow(x*y,z)) to standard output.
 * Author:          Darren Peralta, Henry Choy
 * Author emails:   {darrencarl.peralta, henry.choy}@sjsu.edu
 * Last modified:   02/12/2023
 * Date created:    02/10/2023
 */

/**
 * Prints x**z, x**(y**2), |y|, and sqrt((x*y)**z) to standard output.
 * Assumptions:     All inputs are 32-bit floating point numbers.
 * Input:           x, y, z - all 32-bit floating point numbers to use for mathematical operations.
 * Returns 0 for success.
 */
int main(void) {
   double x;
   double y;
   double z;

   /* Type your code here. Note: Include the math library above first. */
   scanf("%lf %lf %lf", &x, &y, &z);
   
   printf("%0.2lf ", pow(x,z));
   printf("%0.2lf ", pow(x,pow(y,2)));
   printf("%0.2lf ", fabs(y));
   printf("%0.2lf\n", sqrt(pow(x*y,z)));

   return 0;
}


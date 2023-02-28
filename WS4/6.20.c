#include <stdio.h>

/* Define your function here */
double LapsToMiles(double userLaps) {
   return userLaps / 4.0;
}

int main(void) {

   /* Type your code here. Your code must call the function.  */
   double laps;
   scanf("%lf", &laps);

   double miles = LapsToMiles(laps);

   printf("%0.2lf\n", miles);

   return 0;
}

#include<stdio.h>
#include<conio.h>
#include<math.h>

/* Define function here */
#define f(x) (pow(x,2)+(sin(x)/x))

int main()
{
 float lower, upper, integration=0.0, stepSize, k;
 int i, subInterval;
 /* Input */
 
 printf("Enter lower limit of integration: ");
 scanf("%f", &lower);
 printf("Enter upper limit of integration: ");
 scanf("%f", &upper);
 printf("Enter number of sub intervals: ");
 scanf("%d", &subInterval);

 /* Calculation */
 /* Finding step size */
 stepSize = (upper - lower)/subInterval;

 /* Finding Integration Value */
 integration = f(lower) + f(upper);
 for(i=1; i<= subInterval-1; i++)
 {
  k = lower + i*stepSize;
  if(i%3 == 0)
  {
   integration = integration + 2 * f(k);
  }
  else
  {
   integration = integration + 3 * f(k);
  }
 }
 integration = integration * stepSize*3/8;
 printf("\nRequired value of integration is: %.3f", integration);
 printf("\nThis code was run be Shaurav Bhandari");

 return 0;
}

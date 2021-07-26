/* to Evaluate the arithmetic expression ((a -b / c * d + e) * (f +g)) and display its solution. Read the values of the variables from the user through console. */

#include<stdio.h>

void main()
	{
		float a, b, c, d, e, f, g, result;
		
		printf("\n Enter the 7 values: ");
		scanf("%f%f%f%f%f%f%f", &a, &b, &c, &d, &e, &f, &g);

		result = ((a -b / c * d + e) * (f +g));

		printf("\n ((a -b / c * d + e) * (f +g)) = %.2f \n", result);
	}



#include <stdio.h>
#include <math.h>

// taylor approximation of f(x) = e^x
int main(void){

	const double epsilon = 0.00000001;

	double x;
	printf("x for e^x?:");
	scanf("%lf", &x);

	double totalValue = 1.0;
	double currentValue;
	double factorial = 1.0;
	double xpow = 1.0;
	int n = 1;

	do{
		xpow *= x;
		factorial *= n;
		currentValue = xpow / factorial;
		totalValue += currentValue;
		n++;
		printf("%.15lf\n", currentValue);
	}while(fabs(currentValue) > epsilon);

	printf("Berechnete Glieder: %d\n", n);
	printf("e^%lf = %lf\n", x, totalValue);

	return 0;
}
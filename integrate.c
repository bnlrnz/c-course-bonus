#include <stdio.h>
#include <math.h>

typedef double (*function)(double);

//x⁵+2x²+x+1
double func1(double x){
	return x*x*x*x*x + 2*x*x + x + 1;
}

//sin(x) + log(x*x) + 2
double func2(double x){
	return sin(x) + log(x*x) + 2;
}

double integrate(function func, double start, double end, double step){
	double sum = 0.0;
	while(start<end){
		sum += func(start);
		start += step;
	}
	return sum*step;
}

int main(void){
	printf("%f\n", integrate(&func1, 0, 2, 0.0001));
	printf("%f\n", integrate(&func2, 0, 2, 0.0001));
	return 0;
}
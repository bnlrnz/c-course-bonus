#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	srand(time(NULL));
	int magicNumber = rand() % 100 + 1;
	int max = 100;
	int min = 1;

	int current = 0;

	while (magicNumber != current){
		printf("Guess number between %d and %d:\n", min, max);
		scanf("%d", &current);

		if (current < magicNumber){
			printf("too small...\n");
			min = current;
		}

		if (current > magicNumber){
			printf("to big...\n");
			max = current;
		} 
	}

	printf("Found it!\n");
	
	return 0;
}
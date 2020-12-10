#include <stdio.h>

int main(void)
{
    int number = 0;
    int i = 2;

    printf("Number (>2): ");
    scanf("%i", &number);

    while (i <= number){
        if (number % i == 0){
            printf("%i*", i);
            number /= i;
        }
        else{
            i++;
        }
    }


    return 0;
}
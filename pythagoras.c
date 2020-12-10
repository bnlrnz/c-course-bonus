#include <stdio.h>

int main(void)
{

    // a < b < c
    // a² + b² = c²
    // Find a + b + c = 1000

    int a = 0;
    int b = 0;
    int c = 0;

    for (size_t a = 0; a < 998; a++)
    {
        for (size_t b = a+1; b < 999; b++)
        {
            for (size_t c = b+1; c < 1000; c++)
            {        
                if (a*a + b*b == c*c && a + b + c == 1000)
                {
                    printf("a=%d\nb=%d\nc=%d\n\n", a, b, c);
                }
            }
        }
    }

    return 0;
}
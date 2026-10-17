
#include <stdio.h>

long long factorial(int n)
{
    long long result = 1;

    for (int i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}

int main(void)
{
    int n;

    printf("Enter a non-negative integer n: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    if (n < 0)
    {
        printf("Error: n cannot be negative.\n");
    }
    else if (n > 20)
    {
        printf("Error: n is too large.\n");
    }
    else
    {
        printf("%d! = %lld\n", n, factorial(n));
    }

    return 0;
}

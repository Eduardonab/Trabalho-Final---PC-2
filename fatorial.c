#include "fatorial.h"

/* Fun��o iterativa para c�lculo de fatorial */
unsigned long long fatorial_iterativo(unsigned long long n)
{
    unsigned long long resultado = 1;
    unsigned long long i;

    for (i = 1; i <= n; i++)
    {
        resultado *= i;
    }

    return resultado;
}

/* Fun��o recursiva para c�lculo de fatorial */
unsigned long long fatorial_recursivo(unsigned long long n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * fatorial_recursivo(n - 1);
    }
}


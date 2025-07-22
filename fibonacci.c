#include "fibonacci.h"

/* Função iterativa para cálculo do n-ésimo termo da sequência de Fibonacci */
unsigned long long fibonacci_iterativo(unsigned long long n)
{
    unsigned long long a = 0;
    unsigned long long b = 1;
    unsigned long long i;
    unsigned long long temp;

    if (n == 0){
        return 0;
    }
    else if (n == 1){
        return 1;
	}
    for (i = 2; i <= n; i++)
    {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}

/* Função recursiva para cálculo do n-ésimo termo da sequência de Fibonacci */
/* Atenção: para valores grandes, a recursiva é muito lenta */
unsigned long long fibonacci_recursivo(unsigned long long n)
{
    if (n == 0){
        return 0;
    }
    else if (n == 1){
        return 1;
    }
    else{
        return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
    }
}


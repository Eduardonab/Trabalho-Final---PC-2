#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "fatorial.h"
#include "fibonacci.h"

#define REP_FAC 1000000     // REP para fatorial (função rápida)
#define REP_FIB 100000      // REP para Fibonacci iterativo (moderada)
#define REP_FIB_REC 200     // REP para Fibonacci recursivo (lenta)

// Cores padronizadas
#define COR_RESET    "\x1b[0m"
#define COR_TEXTO    "\x1b[36m"  // Ciano claro para bordas e menus
#define COR_TITULO   "\x1b[33m"  // Amarelo para títulos
#define COR_OPCAO    "\x1b[32m"  // Verde para opções numéricas
#define COR_FINAL    "\x1b[33m"  // Amarelo para encerramento
#define COR_ALERTA   "\x1b[31m"  // Vermelho para alertas e mensagens importantes
#define COR_CODIGO   "\x1b[0m"   // Neutro para código fonte

void mostrar_codigo(const char *nome_arquivo)
{
    FILE *fp;
    char linha[256];

    fp = fopen(nome_arquivo, "r");
    if (fp == NULL)
    {
        printf(COR_ALERTA "Erro ao abrir arquivo: %s\n" COR_RESET, nome_arquivo);
        perror(nome_arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        printf(COR_TEXTO "| " COR_CODIGO);
        printf("%s", linha);
    }

    fclose(fp);
}

void imprimir_tabela_comparativa(unsigned long long res1, double t1,
                                 unsigned long long res2, double t2,
                                 const char *metodo1, const char *metodo2)
{
    printf(COR_TITULO);
    printf("+-------------------+-----------------------+---------------------+\n");
    printf("|     Método        |       Resultado       |   Tempo médio (s)   |\n");
    printf("+-------------------+-----------------------+---------------------+\n");
    printf("| %-17s | %21llu | %19.9f |\n", metodo1, res1, t1);
    printf("| %-17s | %21llu | %19.9f |\n", metodo2, res2, t2);
    printf("+-------------------+-----------------------+---------------------+\n");
    printf(COR_RESET);
}

int main(void)
{
    system("color 0A");

    int continuar;
    unsigned long long valor;
    int opcao_problema, ordem_execucao, tipo_exibicao;

    setlocale(LC_ALL, "Portuguese");

    do
    {
        system("cls");

        clock_t inicio, fim;
        double tempo1 = 0, tempo2 = 0;
        volatile unsigned long long resultado1 = 0, resultado2 = 0;
        int i, rep1 = 0, rep2 = 0;

        // Menu principal
        do
        {
            system("cls");
            printf(COR_TEXTO "[]==================================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "                                                  " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "        " COR_TITULO "BEM-VINDO AO PROGRAMA DE CÁLCULO" COR_RESET "          " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "          " COR_TITULO "DE FATORIAL E FIBONACCI" COR_RESET "                 " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "  " COR_TITULO "USANDO DUAS ABORDAGENS: ITERATIVA E RECURSIVA" COR_RESET "   " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "                      " COR_TITULO "!!!" COR_RESET "                         " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "                                                  " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]==================================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]                  " COR_TITULO "MENU PRINCIPAL" COR_RESET "                  " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]==================================================[]\n" COR_RESET);
            printf(COR_TEXTO "[] Problema clássico a ser abordado:                []\n" COR_RESET);
            printf(COR_TEXTO "[] " COR_OPCAO "[1]" COR_RESET " Cálculo de Fatorial                          " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[] " COR_OPCAO "[2]" COR_RESET " Sequência de Fibonacci                       " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]==================================================[]\n" COR_RESET);
            printf(COR_ALERTA "Opção: " COR_RESET);
            if (scanf("%d", &opcao_problema) != 1)
            {
                while (getchar() != '\n');
                opcao_problema = 0;
            }
        } while (opcao_problema != 1 && opcao_problema != 2);

        // Entrada valor
        do
        {
            system("cls");
            printf(COR_TEXTO "[]=================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "   Digite um valor de entrada    " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]=================================[]\n" COR_RESET);
            printf(COR_ALERTA "Valor: " COR_RESET);
            if (scanf("%llu", &valor) != 1)
            {
                while (getchar() != '\n');
                valor = 94;
            }
        } while (valor > 93);

        // Escolha da ordem de execução
        do
        {
            system("cls");
            printf(COR_TEXTO "[]=================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "   ORDEM DAS FORMAS DE CÁLCULO   " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]=================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET COR_OPCAO "[3]" COR_RESET " Iterativo -> Recursivo       " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET COR_OPCAO "[4]" COR_RESET " Recursivo -> Iterativo       " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]=================================[]\n" COR_RESET);
            printf(COR_ALERTA "Opção: " COR_RESET);
            if (scanf("%d", &ordem_execucao) != 1)
            {
                while (getchar() != '\n');
                ordem_execucao = 0;
            }
        } while (ordem_execucao != 3 && ordem_execucao != 4);

        // Escolha do tipo de exibição no terminal
        do
        {
            system("cls");
            printf(COR_TEXTO "[]================================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET "            EXIBIÇÃO DOS RESULTADOS             " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]================================================[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET COR_OPCAO "[5]" COR_RESET " Mostrar somente tempo de execução           " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET COR_OPCAO "[6]" COR_RESET " Mostrar somente o código fonte implementado " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]" COR_RESET COR_OPCAO "[7]" COR_RESET " Mostrar ambos                               " COR_TEXTO "[]\n" COR_RESET);
            printf(COR_TEXTO "[]================================================[]\n" COR_RESET);
            printf(COR_ALERTA "Opção: " COR_RESET);
            if (scanf("%d", &tipo_exibicao) != 1)
            {
                while (getchar() != '\n');
                tipo_exibicao = 0;
            }
        } while (tipo_exibicao != 5 && tipo_exibicao != 6 && tipo_exibicao != 7);

        if (opcao_problema == 1)
        {
            rep1 = rep2 = REP_FAC;
        }
        else
        {
            if (valor > 40)
            {
                printf(COR_ALERTA "?? Atenção: valor muito alto para versão recursiva de Fibonacci! Limitando a 40.\n" COR_RESET);
                valor = 40;
            }

            if (ordem_execucao == 3)
            {
                rep1 = REP_FIB;
                rep2 = REP_FIB_REC;
            }
            else
            {
                rep1 = REP_FIB_REC;
                rep2 = REP_FIB;
            }
        }

        fatorial_iterativo(valor);
        fatorial_recursivo(valor);
        fibonacci_iterativo(valor);
        fibonacci_recursivo(valor);

        if (opcao_problema == 1)
        {
            if (ordem_execucao == 3)
            {
                inicio = clock();
                for (i = 0; i < rep1; i++) resultado1 = fatorial_iterativo(valor);
                fim = clock();
                tempo1 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep1;

                inicio = clock();
                for (i = 0; i < rep2; i++) resultado2 = fatorial_recursivo(valor);
                fim = clock();
                tempo2 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep2;
            }
            else
            {
                inicio = clock();
                for (i = 0; i < rep1; i++) resultado1 = fatorial_recursivo(valor);
                fim = clock();
                tempo1 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep1;

                inicio = clock();
                for (i = 0; i < rep2; i++) resultado2 = fatorial_iterativo(valor);
                fim = clock();
                tempo2 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep2;
            }

            system("cls");
            printf(COR_TITULO "+---------------------+-------------------------+-----------------+\n" COR_RESET);
            printf(COR_TITULO "|" COR_RESET COR_TEXTO "                             RESULTADOS                             " COR_RESET COR_TITULO "|\n" COR_RESET);
            imprimir_tabela_comparativa(resultado1, tempo1, resultado2, tempo2,
                                        (ordem_execucao == 3) ? "Iterativo" : "Recursivo",
                                        (ordem_execucao == 3) ? "Recursivo" : "Iterativo");

            if (tipo_exibicao == 6 || tipo_exibicao == 7)
            {
                printf("\n--- Código fonte de Fatorial ---\n\n");
                mostrar_codigo("Fatorial.h");
                printf("\n");
                mostrar_codigo("Fatorial.c");
            }
        }
        else
        {
            if (ordem_execucao == 3)
            {
                inicio = clock();
                for (i = 0; i < rep1; i++) resultado1 = fibonacci_iterativo(valor);
                fim = clock();
                tempo1 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep1;

                inicio = clock();
                for (i = 0; i < rep2; i++) resultado2 = fibonacci_recursivo(valor);
                fim = clock();
                tempo2 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep2;
            }
            else
            {
                inicio = clock();
                for (i = 0; i < rep1; i++) resultado1 = fibonacci_recursivo(valor);
                fim = clock();
                tempo1 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep1;

                inicio = clock();
                for (i = 0; i < rep2; i++) resultado2 = fibonacci_iterativo(valor);
                fim = clock();
                tempo2 = ((long double)(fim - inicio)) / CLOCKS_PER_SEC / rep2;
            }

            system("cls");
            printf(COR_TITULO "+---------------------+-------------------------+-----------------+\n" COR_RESET);
            printf(COR_TITULO "|" COR_RESET COR_TEXTO "                             RESULTADOS                          " COR_RESET COR_TITULO "|\n" COR_RESET);
            imprimir_tabela_comparativa(resultado1, tempo1, resultado2, tempo2,
                                        (ordem_execucao == 3) ? "Iterativo" : "Recursivo",
                                        (ordem_execucao == 3) ? "Recursivo" : "Iterativo");

            if (tipo_exibicao == 6 || tipo_exibicao == 7)
            {
                printf("\n--- Código fonte de Fibonacci ---\n\n");
                mostrar_codigo("Fibonacci.h");
                printf("\n");
                mostrar_codigo("Fibonacci.c");
            }
        }

        printf(COR_OPCAO "\nDeseja fazer uma nova rodada? (1 = Sim / 0 = Não): " COR_RESET);
        if (scanf("%d", &continuar) != 1) continuar = 0;
        printf("\n");

    } while (continuar == 1);

    printf(COR_FINAL "[]================================================[]\n" COR_RESET);
    printf(COR_FINAL "[]               PROGRAMA ENCERRADO               []\n" COR_RESET);
    printf(COR_FINAL "[]================================================[]\n" COR_RESET);

    return 0;
}


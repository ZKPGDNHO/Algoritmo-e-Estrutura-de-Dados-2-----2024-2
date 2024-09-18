#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct pile
{
    float valor;
    struct pile *prox;

} pilha;

pilha *empilhar(pilha *p, float v)
{
    pilha *new = (pilha *)malloc(sizeof(pilha));

    if (new != NULL)
    {
        new->valor = v;
        new->prox = p;
        return new;
    }
    else
    {
        printf("Deu pau em alocar memoria\n");
        return NULL;
    }
}

pilha *desempilhar(pilha **p)
{
    pilha *remove = NULL;

    if (*p)
    {
        remove = *p;
        *p = remove->prox;
    }
    else
    {
        printf("Pilha vazia\n");
    }

    return remove;
}

float operacao(float a, float b, char x)
{
    switch (x)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '/':
        return a / b;
    case '*':
        return a * b;
    default:
        printf("Operador invalido\n");
        return 0;
    }
}

float resolver_expressao(char x[])
{
    char *pointer;
    pilha *n1, *n2, *p = NULL;
    float num;

    // Usando strtok para dividir a string com base no espaço
    pointer = strtok(x, " ");
    while (pointer != NULL)
    {
        if (pointer[0] == '+' || pointer[0] == '-' || pointer[0] == '/' || pointer[0] == '*')
        {
            n1 = desempilhar(&p);
            n2 = desempilhar(&p);
            num = operacao(n2->valor, n1->valor, pointer[0]);
            p = empilhar(p, num);
            free(n1);
            free(n2);
        }
        else
        {
            num = strtof(pointer, NULL); // Converte o token para float
            p = empilhar(p, num);
        }
        pointer = strtok(NULL, " ");
    }
    n1 = desempilhar(&p);
    num = n1->valor;
    free(n1);
    return num;
}

int main()
{
    char exp[MAX];

    printf("Por favor, digite uma expressao posfixada (separada por espacos):\n");
    fgets(exp, MAX, stdin); // Lê a expressão digitada pelo usuário

    // Remover o caractere de nova linha do final da string, se existir
    exp[strcspn(exp, "\n")] = 0;

    printf("Resultado de %s=\t", exp);
    printf("%.2f\n", resolver_expressao(exp));

    return 0;
}

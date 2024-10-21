#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main()
{
    Node *root = NULL;
    int value, searchValue, steps, found;

    // Inserção de valores na árvore
    printf("Insira valores inteiros na árvore (digite -1 para encerrar):\n");
    while (1)
    {
        scanf("%d", &value);
        if (value == -1)
        {
            break; // Condição de término da inserção
        }
        root = insertNode(root, value); // Insere o valor na árvore
    }

    // Busca por um valor na árvore
    printf("Digite um valor para buscar na árvore: ");
    scanf("%d", &searchValue);

    // Realiza a busca e conta os passos
    steps = 0;
    found = searchNode(root, searchValue, &steps);

    // Exibe o resultado da busca
    if (found)
    {
        printf("Valor %d encontrado em %d passo(s).\n", searchValue, steps);
    }
    else
    {
        printf("Valor %d não encontrado na árvore.\n", searchValue);
    }

    return 0;
}

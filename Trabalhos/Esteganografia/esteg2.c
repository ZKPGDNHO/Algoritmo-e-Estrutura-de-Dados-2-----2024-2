#include <stdio.h>
#include "encryp_png.h"

int main()
{
    int op = 0;

    char mensagem[256];
    FILE *arquivo;
    do
    {
        printf("O que gostaria de fazer?\n");
        printf("1 - Mostrar Mensagem \n");
        scanf("%d", &op);
        if (op == 1)
        {
            print_message("NewShrek.png");
        }

        if (op != 1 && op != 2)
        {
            printf("Opcao invalida\n");
        }
    } while (op != 1 && op != 2);

    return 0;
}
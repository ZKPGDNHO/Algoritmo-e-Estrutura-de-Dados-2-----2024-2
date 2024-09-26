#include <stdio.h>
#include "encryp_png.h"

int main()
{
    int op = 0;
    char *msg = "inText.txt";
    do
    {
        printf("O que gostaria de fazer?\n");
        printf("1 - Esconder Mensagem \n"
               "2 - Mostrar Imagem \n");
        scanf("%d", &op);
        if (op == 1)
        {
            // metodo de esconder;
            hide("Shrek.png", "NewShrek.png", msg);
            printf("Mensagem escondida com sucesso\n");
        }
        if (op == 2)
        {
            // metodo de mostrar;
            print_message("NewShrek.png");
        }
        if (op != 1 && op != 2)
        {
            printf("Opcao invalida\n");
        }
    } while (op != 1 && op != 2);

    return 0;
}
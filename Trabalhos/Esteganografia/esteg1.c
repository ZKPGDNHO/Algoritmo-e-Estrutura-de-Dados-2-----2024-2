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
        printf("1 - Esconder Mensagem \n");
        scanf("%d", &op);
        if (op == 1)
        {
            // Solicita que o usuário digite uma mensagem
            printf("Digite uma mensagem: ");
            getchar();
            fgets(mensagem, sizeof(mensagem), stdin);

            // Abre o arquivo "mensagem.txt" em modo de escrita (write mode)
            arquivo = fopen("inText.txt", "w");

            // Verifica se o arquivo foi aberto com sucesso
            if (arquivo == NULL)
            {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            // Escreve a mensagem no arquivo
            fprintf(arquivo, "%s", mensagem);

            // Fecha o arquivo
            fclose(arquivo);
            char *msg = "inText.txt";

            // metodo de esconder;
            hide("Shrek.png", "NewShrek.png", msg);
            printf("Mensagem escondida com sucesso\n");
        }

        if (op != 1 && op != 2)
        {
            printf("Opcao invalida\n");
        }
    } while (op != 1 && op != 2);

    return 0;
}
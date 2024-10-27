#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_SIZE 256
#define ENDM '\0'
//---------------------------------Funcoes da tabela de Frequencia----------------------------------------------
void Start_chart(unsigned int chrt[])
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        chrt[i] = 0;
    }
}

void Start_Frequency(unsigned char text[], unsigned int chrt[])
{
    int i = 0;
    while (text[i] != ENDM)
    {
        chrt[text[i]]++;
        i++;
    }
}

void print_chart(unsigned chrt[])
{
    printf("Tabela de Frequencias:\n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (chrt[i] > 0)
        {
            printf("\n\t%d - %d = %c\n", i, chrt[i], i);
        }
    }
}
//----------------------------------------Funcoes para criar o dicionario--------------------------------------------------------------------
char **dicionario(int cols)
{
    char **d;

    d = malloc(sizeof(char *) * MAX_SIZE);

    for (int i = 0; i < MAX_SIZE; i++)
    {
        d[i] = calloc(cols, sizeof(char));
    }
    return d;
}

void create_dicionario(char **d, Node *raiz, char *path, int cols)
{
    char left[cols], right[cols];

    if (raiz->left == NULL && raiz->right == NULL)
    {
        strcpy(d[raiz->letra], path);
    }
    else
    {
        strcpy(left, path);
        strcpy(right, path);

        strcat(left, "0");
        strcat(right, "1");

        create_dicionario(d, raiz->left, left, cols);
        create_dicionario(d, raiz->right, right, cols);
    }
}

void print_dicionario(char **d)
{
    printf("\n\tDicionario: \n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (strlen(d[i]) > 0)
        {
            printf("\t%3d: %s\n", i, d[i]);
        }
    }
}
//-----------------------------------------------------Funcoes para codificar o texto ---------------------------------------------------------
int calc_string_size(char **d, unsigned char *texto)
{
    int i = 0, size = 0;
    while (texto[i] != ENDM)
    {
        size = size + strlen(d[texto[i]]);
        i++;
    }
    return size + 1;
}

char *codificar(char **d, unsigned char *texto)
{
    int i = 0;
    int size = calc_string_size(d, texto);
    char *codigo = calloc(size, sizeof(char));

    while (texto[i] != ENDM)
    {
        strcat(codigo, d[texto[i]]);
        i++;
    }
    return codigo;
}

//---------------------------------------------------- Funcoes para decodificar o texto -----------------------------------------------------------
char *decodificar(unsigned char text[], Node *raiz)
{
    int i = 0;
    Node *aux = raiz;

    char *decodificado = calloc(strlen(text), sizeof(char));

    char temp[2];
    while (text[i] != ENDM)
    {

        if (text[i] == '0')
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }

        if (aux->left == NULL && aux->right == NULL)
        {

            temp[0] = aux->letra;
            temp[1] = ENDM;

            strcat(decodificado, temp);
            aux = raiz;
        }
        i++;
    }
    return decodificado;
}

//------------------------------------------------------Funcoes para Compactar/Descompactar o texto ---------------------------------------------------------------
void compact(unsigned char str[])
{
    FILE *arquivo = fopen("compfile.txt", "wb");
    int i = 0, j = 7;
    unsigned char byte = 0;
    unsigned char mask = 0;

    if (arquivo)
    {
        while (str[i] != ENDM)
        {
            mask = 1;
            if (str[i] == '1')
            {
                mask = mask << j;
                byte = byte | mask;
            }
            j--;

            if (j < 0)
            {
                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                byte = 0;
                j = 7;
            }
            i++;
        }
        if (j != 7)
        {
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Erro ao abrit/criar o arquivo em compact\n");
    }
}

unsigned int Is_bit_One(unsigned char byte, int i)
{
    unsigned char mask = (1 << i);
    return byte & mask;
}

void decompact(Node *raiz)
{
    FILE *arquivo = fopen("compfile.txt", "rb");
    Node *aux = raiz;
    unsigned char byte;
    int i = 0;
    if (arquivo)
    {
        while (fread(&byte, sizeof(unsigned char), 1, arquivo))
        {
            for (i = 7; i >= 0; i--)
            {
                if (Is_bit_One(byte, i))
                {
                    aux = aux->right;
                }
                else
                {
                    aux = aux->left;
                }
                if (aux->left == NULL && aux->right == NULL)
                {
                    printf("%c", aux->letra);
                    aux = raiz;
                }
            }
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Erro ao abrit/criar o arquivo em decompact\n");
    }
}

int find_size()
{
    FILE *arquivo = fopen("teste1.txt", "r");
    int size = 0;
    if (arquivo)
    {
        while (fgetc(arquivo) != -1)
        {
            size++;
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Erro ao abrit/criar o arquivo em find_size\n");
    }
    return size;
}

void ler_texto(unsigned char *text)
{
    FILE *arquivo = fopen("teste1.txt", "r");
    char l;
    int i = 0;

    if (arquivo)
    {
        while (!feof(arquivo))
        {
            l = fgetc(arquivo);
            if (l != -1)
            {
                text[i] = l;
                i++;
            }
        }
        fclose(arquivo);
    }
    else
    {
        printf("\n Erro ao abrit/criar o arquivo em ler_texto\n");
    }
}

int main()
{
    unsigned char *text;
    unsigned int frequency_chart[MAX_SIZE];
    Lista l;
    Node *t;
    int c, size;
    char **d;
    char *codificado;
    char *decodificado;
    int op = 0;

    do
    {
        printf("Olá, gostaria de comprimir um arquivo ?\n");
        printf("1-SIM  2-NAO\n");
        scanf("%d", &op);

        if (op == 1)
        {

            size = find_size();
            printf("\nTAMANHO: %d\n", size);

            text = calloc(size * 2, sizeof(unsigned char));
            ler_texto(text);

            Start_chart(frequency_chart);
            Start_Frequency(text, frequency_chart);

            create_list(&l);
            insert_list(frequency_chart, &l);

            t = create_tree(&l);

            c = altura_tree(t) + 1;

            d = dicionario(c);

            create_dicionario(d, t, "", c);

            codificado = codificar(d, text);
            printf("\n\t Texto codificado: %s\n", codificado);

            decodificado = decodificar(codificado, t);
            printf("\n\t Texto decoficado: %s\n", decodificado);

            compact(codificado);
            printf("\nTEXTO DECODIFICADO: \n");
            decompact(t);
            printf("\n");

            //----------------------------------------------------estatisticas do codigo, arvores, dicionario, tabela de frequencia, etc. ----------------------------------------
            printf("\n\t _________________________________ ESTATISTICAS DO ALGORITMO: ______________________________________________________\n");
            print_chart(frequency_chart);

            print_lista(&l);

            printf("\n\tArvore de Huffman: \n");
            print_tree(t, 0);

            print_dicionario(d);
        }
        else if (op == 2)
        {
            printf("Ok, até mais. \n");
            return 0;
        }

        if (op != 1 && op != 2)
        {
            printf("Opcao invalida\n");
        }

    } while (op != 1 && op != 2);

    free(text);
    free(codificado);
    free(decodificado);

    return 0;
}
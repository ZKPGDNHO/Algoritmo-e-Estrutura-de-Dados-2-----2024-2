#include <stdlib.h>
#include <stdio.h>
#include "list.h"

#define MAX_SIZE 256
#define ENDM '\0'

void create_list(Lista *l)
{
    l->begin = NULL;
    l->size = 0;
}
void insert_ordenado(Lista *l, Node *n)
{
    Node *aux;
    if (l->begin == NULL)
    {
        l->begin = n;
    }
    else if (n->freq < l->begin->freq)
    {
        n->next = l->begin;
        l->begin = n;
    }
    else
    {
        aux = l->begin;
        while (aux->next != NULL && aux->next->freq <= n->freq)
        {
            aux = aux->next;
        }
        n->next = aux->next;
        aux->next = n;
    }
    l->size++;
}
void insert_list(unsigned int chrt[], Lista *l)
{
    Node *new;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (chrt[i] > 0)
        {
            new = malloc(sizeof(Node));
            if (new)
            {
                new->letra = i;
                new->freq = chrt[i];
                new->left = NULL;
                new->right = NULL;
                new->next = NULL;

                insert_ordenado(l, new);
            }
            else
            {
                printf("Erro ao alocar memoria em insert_list \n");
                break;
            }
        }
    }
}

Node *remove_inicio(Lista *l)
{
    Node *aux = NULL;

    if (l->begin)
    {
        aux = l->begin;
        l->begin = aux->next;
        aux->next = NULL;
        l->size--;
    }

    return aux;
}

Node *create_tree(Lista *l)
{
    Node *primeiro;
    Node *segundo;
    Node *new;

    while (l->size > 1)
    {
        primeiro = remove_inicio(l);
        segundo = remove_inicio(l);
        new = malloc(sizeof(Node));

        if (new)
        {
            new->letra = '+';
            new->freq = primeiro->freq + segundo->freq;
            new->left = primeiro;
            new->right = segundo;
            new->next = NULL;

            insert_ordenado(l, new);
        }
        else
        {
            printf("\n\t Erro alocando memoria em create_tree\n");
            break;
        }
    }
    return l->begin;
}

int altura_tree(Node *raiz)
{
    int esq, dir;
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        esq = altura_tree(raiz->left) + 1;
        dir = altura_tree(raiz->right) + 1;
        if (esq > dir)
        {
            return esq;
        }
        else
            return dir;
    }
}

void print_tree(Node *raiz, int size)
{
    if (raiz->left == NULL && raiz->right == NULL)
    {
        printf("\tFolhas: %c\tAltura: %d\n", raiz->letra, size);
    }
    else
    {
        print_tree(raiz->left, size + 1);
        print_tree(raiz->right, size + 1);
    }
}

void print_lista(Lista *l)
{
    Node *aux = l->begin;
    printf("\n\tLista: Size: %d\n", l->size);
    while (aux)
    {
        printf("\tLetra: %c Frequencia: %d \n", aux->letra, aux->freq);
        aux = aux->next;
    }
}
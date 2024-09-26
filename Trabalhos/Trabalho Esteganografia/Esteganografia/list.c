#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Lista criar_lista()
{
    Lista new;
    new.primeiro = NULL;
    new.ultimo = NULL;
    new.size = 0;

    return new;
}

Celula *criar_celula(int valor)
{
    Celula *temp = NULL;
    do
    {
        temp = (Celula *)malloc(sizeof(Celula));
    } while (temp == NULL);
    temp->valor = valor;
    temp->prox = NULL;
    temp->last = NULL;
    return temp;
}

void inserir_elemento(Lista *lista, Celula *adr)
{
    if (lista->size >= 1)
    {
        (lista->ultimo)->prox = adr;
        adr->last = lista->ultimo;
        lista->ultimo = adr;
        lista->size++;
    }
    else
    {
        lista->ultimo = adr;
        lista->primeiro = adr;
        lista->size++;
    }
}

void imprimir_lista(Lista *lista)
{
    if (lista->size >= 1)
    {
        Celula *temp = lista->primeiro;
        printf("Lista:");
        for (int i = 0; i < lista->size; i++)
        {
            printf("%d", temp->valor);
            temp = temp->prox;
        }
        putchar('\n');
    }
    else
    {
        printf("Lista está vazia\n");
    }
}

void deletar_elemento(Lista *lista, Celula *adr)
{
    if (adr != NULL)
    {
        if (adr == lista->primeiro)
        {
            lista->primeiro = adr->prox;
            free(adr);
        }
        else if (adr == lista->ultimo)
        {
            lista->ultimo = (lista->ultimo)->last;
            free(adr);
        }
        else
        {
            (adr->last)->prox = adr->prox;
            (adr->prox)->last = adr->last;
            free(adr);
        }
        lista->size--;
        if (lista->size == 0)
        {
            lista->primeiro = NULL;
            lista->ultimo = NULL;
        }
    }
}

void liberar_lista(Lista *lista)
{
    int tamanho = lista->size;
    Celula *temp = lista->primeiro;
    if (tamanho == 1)
    {
        free(lista->primeiro);
        lista->ultimo = NULL;
        lista->primeiro = NULL;
    }
    else if (tamanho > 1)
    {
        Celula *t2 = NULL;
        for (int i = 0; i < tamanho; i++)
        {
            t2 = temp->prox;
            free(temp);
            temp = t2;
        }
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    lista->size = 0;
}
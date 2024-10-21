#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pilha.h"

PilhaNode *createNode(char data)
{
    PilhaNode *new = (PilhaNode *)malloc(sizeof(PilhaNode));

    if (!new)
    {
        fprintf(stderr, "Memória insuficiente\n");
        exit(EXIT_FAILURE);
    }

    new->data = data;
    new->next = NULL;

    return new;
}

void initStack(Pilha *s)
{
    s->topo = NULL;
    s->size = 0;
}
int isPilhaEmpty(Pilha *s)
{
    return s->topo == NULL;
}

void push(Pilha *s, char data)
{
    PilhaNode *new = createNode(data);
    new->next = s->topo;
    s->topo = new;
    s->size++;
}
char pop(Pilha *s)
{

    if (isPilhaEmpty(s))
    {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    PilhaNode *temp = s->topo;
    char pdata = temp->data;
    s->topo = s->topo->next;
    free(temp);
    s->size--;
    return pdata;
}
char peek(Pilha *s)
{
    if (isPilhaEmpty(s))
    {
        fprintf(stderr, "A pilha está vazia\n");
        exit(EXIT_FAILURE);
    }
    return s->topo->data;
}
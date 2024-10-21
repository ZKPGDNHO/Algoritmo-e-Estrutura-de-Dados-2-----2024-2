#ifndef PILHA_H
#define PILHA_H

typedef struct pilhanode
{
    char data;
    struct pilhanode *next;
} PilhaNode;

typedef struct
{
    PilhaNode *topo;
    int size;
} Pilha;

PilhaNode *createNode(char data);
void initStack(Pilha *s);
int isPilhaEmpty(Pilha *s);
void push(Pilha *s, char data);
char pop(Pilha *s);
char peek(Pilha *s);

#endif
#ifndef LISTA_H
#define LISTA_H

typedef struct node
{
    unsigned char letra;
    int freq;
    struct node *left, *right, *next;
} Node;

typedef struct list
{
    Node *begin;
    int size;
} Lista;

void create_list(Lista *l);
void insert_ordenado(Lista *l, Node *n);
void insert_list(unsigned int chrt[], Lista *l);
Node *remove_inicio(Lista *l);
Node *create_tree(Lista *l);
int altura_tree(Node *raiz);
void print_tree(Node *raiz, int size);
void print_lista(Lista *l);

#endif
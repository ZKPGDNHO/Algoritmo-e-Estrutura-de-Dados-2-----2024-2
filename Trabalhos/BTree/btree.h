#ifndef BTREE_H
#define BTREE_H

// Definição da estrutura do nó da árvore
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node *createNode(int value);

// Função para inserir um valor na Árvore Binária de Busca
Node *insertNode(Node *root, int value);

// Função para buscar um valor na Árvore Binária de Busca e contar os passos
int searchNode(Node *root, int value, int *steps);

#endif // ARVORE_BINARIA_H

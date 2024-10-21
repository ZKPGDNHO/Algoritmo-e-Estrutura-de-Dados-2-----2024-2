#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// Função para criar um novo nó
Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na Árvore Binária de Busca
Node *insertNode(Node *root, int value)
{
    if (root == NULL)
    {
        // Se a árvore estiver vazia, cria um novo nó
        return createNode(value);
    }

    // Caso contrário, insere o valor na subárvore à esquerda ou à direita
    if (value < root->data)
    {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Função para buscar um valor na Árvore Binária de Busca e contar os passos
int searchNode(Node *root, int value, int *steps)
{
    // Se a árvore está vazia ou o valor não for encontrado
    if (root == NULL)
    {
        return 0; // Valor não encontrado
    }

    (*steps)++; // Conta o passo

    // Se o valor foi encontrado
    if (root->data == value)
    {
        return 1; // Valor encontrado
    }

    // Recursão à esquerda ou à direita
    if (value < root->data)
    {
        return searchNode(root->left, value, steps);
    }
    else
    {
        return searchNode(root->right, value, steps);
    }
}

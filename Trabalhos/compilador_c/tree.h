#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

#define ResWords 179
#define MaxLenght 200

typedef struct node
{
    char data[MaxLenght];
    struct node *left;
    struct node *right;
    int altura;
} TreeNode;

typedef struct
{
    TreeNode *root;
} Arvore;

typedef struct
{
    bool left;
    bool right;
    int qtd;
} Answer;

TreeNode *Create_Node(char *x);
TreeNode *RightRotation(TreeNode *Nunb);
TreeNode *LeftRotation(TreeNode *Nunb);
TreeNode *RightLeft(TreeNode *Nunb);
TreeNode *LeftRight(TreeNode *Nunb);
TreeNode *balance(TreeNode *raiz);
TreeNode *inserir(TreeNode *raiz, char *x);
TreeNode *remove_node(TreeNode *root, char *chave);
int FatorDeBalanceamento(TreeNode *no);
int AlturaDoNo(TreeNode *no);
void imprimir(TreeNode *raiz, int nivel);
void FreeMemory(TreeNode *raiz);
bool Encontrar(TreeNode *raiz, char *chave);
Answer Criar_Answer(int qtd, bool direita, bool esquerda);
Answer Qtd_Filhos(TreeNode *root, char *chave);

#endif
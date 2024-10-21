#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

TreeNode *Create_Node(char *x)
{
    TreeNode *NewNo = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(NewNo->data, x);
    NewNo->left = NULL;
    NewNo->right = NULL;
    NewNo->altura = 0;

    return NewNo;
}

Answer Criar_Answer(int qtd, bool direita, bool esquerda)
{
    Answer x;
    x.qtd = qtd;
    x.right = direita;
    x.left = esquerda;
    return x;
}

int maior(int a, int b)
{
    return (a > b) ? a : b;
}

int AlturaDoNo(TreeNode *no)
{
    return (no == NULL) ? -1 : no->altura;
}

int FatorDeBalanceamento(TreeNode *no)
{
    if (no)
    {
        return (AlturaDoNo(no->left) - AlturaDoNo(no->right));
    }
    else
    {
        return 0;
    }
}

int altura(TreeNode *root)
{
    if (root == NULL)
        return -1;
    else
    {
        int esquerda = altura(root->left);
        int direita = altura(root->right);
        if (esquerda > direita)
        {
            return esquerda + 1;
        }
        else
        {
            return direita + 1;
        }
    }
}

TreeNode *RightRotation(TreeNode *Nunb)
{

    TreeNode *f1;
    TreeNode *f2;

    f1 = Nunb->left;
    f2 = f1->right;

    f1->right = Nunb;
    Nunb->left = f2;

    Nunb->altura = maior(AlturaDoNo(Nunb->left), AlturaDoNo(Nunb->right)) + 1;
    f1->altura = maior(AlturaDoNo(f1->left), AlturaDoNo(f1->right)) + 1;

    return f1;
}
TreeNode *LeftRotation(TreeNode *Nunb)
{

    TreeNode *f1;
    TreeNode *f2;

    f1 = Nunb->right;
    f2 = f1->left;

    f1->left = Nunb;
    Nunb->right = f2;

    Nunb->altura = maior(AlturaDoNo(Nunb->left), AlturaDoNo(Nunb->right)) + 1;
    f1->altura = maior(AlturaDoNo(f1->left), AlturaDoNo(f1->right)) + 1;

    return f1;
}
TreeNode *RightLeft(TreeNode *Nunb)
{
    Nunb->right = RightRotation(Nunb->right);
    return LeftRotation(Nunb);
}
TreeNode *LeftRight(TreeNode *Nunb)
{
    Nunb->left = LeftRotation(Nunb->left);
    return RightRotation(Nunb);
}

TreeNode *balance(TreeNode *raiz)
{
    short bounce = FatorDeBalanceamento(raiz);

    if (bounce < -1 && FatorDeBalanceamento(raiz->right) <= 0)
    {

        raiz = LeftRotation(raiz);
    }
    else if (bounce > 1 && FatorDeBalanceamento(raiz->left) >= 0)
    {
        raiz = RightRotation(raiz);
    }
    else if (bounce > 1 && FatorDeBalanceamento(raiz->left) < 0)
    {
        raiz = LeftRight(raiz);
    }
    else if (bounce < -1 && FatorDeBalanceamento(raiz->right) > 0)
    {
        raiz = RightLeft(raiz);
    }

    return raiz;
}

TreeNode *inserir(TreeNode *raiz, char *x)
{
    if (raiz == NULL)
    {
        return Create_Node(x);
    }
    else
    {
        int comp = strcmp(x, raiz->data);
        if (comp < 0)
        {
            raiz->left = inserir(raiz->left, x);
        }
        else if (comp > 0)
        {
            raiz->right = inserir(raiz->right, x);
        }
        else
        {
            return raiz;
        }
    }

    raiz->altura = maior(AlturaDoNo(raiz->left), AlturaDoNo(raiz->right)) + 1;

    int d = FatorDeBalanceamento(raiz);
    if (d > 1 || d < -1)
    {
        raiz = balance(raiz);
    }

    return raiz;
}

void imprimir(TreeNode *raiz, int nivel)
{
    if (raiz)
    {
        imprimir(raiz->right, nivel + 1);
        printf("\n\n");
        for (int i = 0; i < nivel; i++)
        {
            printf("\t");
        }
        printf("comando:%s\n", raiz->data);
        imprimir(raiz->left, nivel + 1);
    }
}

Answer Qtd_Filhos(TreeNode *root, char *chave)
{
    if (root != NULL)
    {

        Answer x;
        if (strcmp(root->data, chave))
        {
            if (root->right != NULL && root->left != NULL)
            {
                x = Criar_Answer(2, true, true);
            }
            else if (root->right == NULL && root->left != NULL)
            {
                x = Criar_Answer(1, false, true);
            }
            else if (root->right != NULL && root->left == NULL)
            {
                x = Criar_Answer(1, true, false);
            }
            else
            {
                x = Criar_Answer(0, false, false);
            }

            return x;
        }
        else
        {
            int comparacao = strcmp(chave, root->data);
            if (comparacao > 0)
            {
                return Qtd_Filhos(root->right, chave);
            }
            else
            {
                return Qtd_Filhos(root->left, chave);
            }
        }
    }
    else
    {
        printf("Nó não está presente na árvore\n");
        Answer x = Criar_Answer(0, false, false);
        return x;
    }
}

TreeNode *remove_node(TreeNode *raiz, char *chave)
{
    if (raiz != NULL)
    {
        if (strcmp(raiz->data, chave) == 0)
        {
            if (raiz->left == NULL && raiz->right == NULL)
            {
                free(raiz);
                return NULL;
            }
            else
            {
                Answer x = Qtd_Filhos(raiz, chave);
                TreeNode *aux = NULL;
                if (x.qtd == 1)
                {
                    if (x.right)
                    {
                        aux = raiz->right;
                    }
                    else
                    {
                        aux = raiz->left;
                    }
                    free(raiz);
                    return aux;
                }
                else
                {
                    TreeNode *aux = raiz->left;
                    while (aux->right != NULL)
                    {
                        aux = aux->right;
                    }
                    strcpy(raiz->data, aux->data);
                    strcpy(aux->data, chave);
                    raiz->left = remove_node(raiz->left, chave);
                    return raiz;
                }
            }
        }
        else
        {
            int comp = strcmp(chave, raiz->data);
            if (comp < 0)
            {
                raiz->left = remove_node(raiz->left, chave);
            }
            else
            {
                raiz->right = remove_node(raiz->right, chave);
            }
            raiz->altura = maior(AlturaDoNo(raiz->left), AlturaDoNo(raiz->right)) + 1;

            raiz = balance(raiz);
            return raiz;
        }
    }
    else
    {
        printf("O nó não está presente na arvore \n");
        return NULL;
    }
}
bool Encontrar(TreeNode *raiz, char *chave)
{
    if (raiz == NULL)
    {
        return false;
    }
    int comparacao = strcmp(raiz->data, chave);
    if (comparacao == 0)
    {
        return true;
    }
    else if (comparacao > 0)
    {
        return Encontrar(raiz->left, chave);
    }
    else
    {
        return Encontrar(raiz->right, chave);
    }
}

void FreeMemory(TreeNode *raiz)
{
    if (raiz != NULL)
    {
        FreeMemory(raiz->left);
        FreeMemory(raiz->right);
        free(raiz);
    }
}

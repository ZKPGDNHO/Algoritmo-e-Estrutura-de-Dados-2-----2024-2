#include <stdio.h>
#include <stdlib.h>

// Definição de um nó da árvore binária
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para inserir um valor na árvore binária de busca
struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data >= root->data)
        root->right = insert(root->right, data);

    return root;
}

// Função para encontrar o valor mínimo em uma árvore binária
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;

    // Percorre a subárvore esquerda para encontrar o menor valor
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Função para remover um nó da árvore binária
struct Node *deleteNode(struct Node *root, int data)
{
    if (root == NULL)
        return root;

    // Se o valor a ser removido for menor, percorre a subárvore esquerda
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // Se o valor a ser removido for maior, percorre a subárvore direita
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // Se o valor for igual ao do nó, este é o nó a ser removido
    else
    {
        // Nó com apenas um filho ou nenhum
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos: pega o sucessor (menor valor da subárvore direita)
        struct Node *temp = minValueNode(root->right);

        // Copia o valor do sucessor para este nó
        root->data = temp->data;

        // Remove o sucessor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Função para realizar um percurso em ordem na árvore
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Função principal
int main()
{
    int values[] = {1, 2, 3, 5, 6, 4, 7, 8, 8, 9, 9}; // Valores a serem inseridos na árvore
    int n = sizeof(values) / sizeof(values[0]);

    struct Node *root = NULL;

    // Inserindo os valores na árvore binária de busca
    for (int i = 0; i < n; i++)
    {
        root = insert(root, values[i]);
    }

    printf("Árvore em ordem antes de remover o 7º valor inserido: ");
    inorder(root);
    printf("\n");

    // Removendo o 7º valor inserido (valor 7 no array)
    root = deleteNode(root, values[6]); // O 7º valor inserido é "7" (índice 6 no array)

    printf("Árvore em ordem após remover o 7º valor inserido: ");
    inorder(root);
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRINCIPAL 1000
#define NUM_CHAVES 3000

// Estrutura para a lista encadeada (colisão)
typedef struct Node
{
    int key;
    struct Node *next;
} Node;

// Função hash
int hashFunction(int key)
{
    return (key % MAX_PRINCIPAL) + 1;
}

// Insere chave na tabela hash
void insert(int table[], Node *overflow[], int key)
{
    int pos = hashFunction(key);
    if (table[pos - 1] == 0)
    {
        table[pos - 1] = key;
    }
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->key = key;
        newNode->next = overflow[pos - 1];
        overflow[pos - 1] = newNode;
    }
}

// Busca chave na tabela hash
int search(int table[], Node *overflow[], int key)
{
    int pos = hashFunction(key);
    int steps = 1;

    if (table[pos - 1] == key)
    {
        return steps;
    }

    Node *current = overflow[pos - 1];
    while (current != NULL)
    {
        steps++;
        if (current->key == key)
        {
            return steps;
        }
        current = current->next;
    }

    return -1;
}

// Mostra os resultados finais
void showResults(int table[], Node *overflow[])
{
    int occupied = 0, empty = 0;

    for (int i = 0; i < MAX_PRINCIPAL; i++)
    {
        if (table[i] != 0)
        {
            occupied++;
        }
        else if (overflow[i] == NULL)
        {
            empty++;
        }
    }

    printf("\nEspaços ocupados: %d\n", occupied);
    printf("Espaços vazios: %d\n", empty);
}

// Libera a memória
void freeOverflow(Node *overflow[])
{
    for (int i = 0; i < MAX_PRINCIPAL; i++)
    {
        Node *current = overflow[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Lê as chaves de um arquivo
int readKeysFromFile(const char *filename, int *keys)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int count = 0;
    while (fscanf(file, "%d", &keys[count]) != EOF && count < NUM_CHAVES)
    {
        count++;
    }

    fclose(file);
    return count;
}

int main()
{
    int table[MAX_PRINCIPAL] = {0};
    Node *overflow[MAX_PRINCIPAL] = {NULL};

    // Lê chaves de um arquivo
    int keys[NUM_CHAVES];
    int numKeys;
    char filename[100];

    printf("Digite o nome do arquivo que contém as chaves: ");
    scanf("%s", filename); // nome do arquivo com as chaves: DesafioHash.txt

    numKeys = readKeysFromFile(filename, keys);
    if (numKeys == -1)
    {
        return 1;
    }

    for (int i = 0; i < numKeys; i++)
    {
        insert(table, overflow, keys[i]);
    }

    int searchKey;
    while (1)
    {
        printf("\nDigite uma chave para buscar (-1 para sair): ");
        scanf("%d", &searchKey);

        if (searchKey == -1)

            break;

        int steps = search(table, overflow, searchKey);
        if (steps != -1)
        {
            printf("Chave encontrada em %d passo(s).\n", steps);
        }
        else
        {
            printf("Chave não encontrada.\n");
        }
    }

    showResults(table, overflow);

    freeOverflow(overflow);

    return 0;
}

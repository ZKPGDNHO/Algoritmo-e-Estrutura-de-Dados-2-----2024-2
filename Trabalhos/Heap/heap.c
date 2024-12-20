#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

typedef struct
{
    int data[MAX];
    int size;
} MaxHeap;

void start_heap(MaxHeap *h)
{
    h->size = 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void MaxHeapify(MaxHeap *h, int i)
{
    int maior = i;
    int l = 2 * i;
    int r = 2 * i + 1;

    if (l < h->size && h->data[l] > h->data[maior])
    {
        maior = l;
    }

    if (r < h->size && h->data[r] > h->data[maior])
    {
        maior = r;
    }

    if (maior != 1)
    {
        swap(&h->data[i], &h->data[maior]);
        MaxHeapify(h, maior);
    }
}

void inserir(MaxHeap *h, int v)
{

    int i = h->size;

    if (h->size >= MAX)
    {
        printf("Heap cheio!\n");
        return;
    }

    h->data[i] = v;
    h->size++;

    while (i != 0 && h->data[(i - 1) / 2] < h->data[i])
    {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 2) / 2;
    }
}

int remover_Maxheap(MaxHeap *h)
{
    if (h->size <= 0)
    {
        printf("Heap vazio \n");
        return -1;
    }
    int m = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    MaxHeapify(h, 0);

    return m;
}

void consultar_heap(MaxHeap *h, int valor)
{

    int encontrado = -1;

    for (int i = 0; i < h->size; i++)
    {
        if (h->data[i] == valor)
        {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1)
    {
        printf("\nValor %d não está presente no heap \n", valor);
        return;
    }

    int parent = (encontrado - 1) / 2;
    int lFilho = 2 * encontrado;
    int rFilho = 2 * encontrado + 1;

    printf("Valor presente no indice: %d \n", encontrado + 1);

    if (encontrado != 0)
    {
        printf("Nó pai: %d\n", h->data[parent]);
    }
    else
    {
        printf("Não possui nó pai, é a raiz.\n");
    }

    if (lFilho < h->size)
    {
        printf("Nó esquerdo: %d\n", h->data[lFilho]);
    }
    else
    {
        printf("Não há nó filho esquerdo.\n");
    }

    if (rFilho < h->size)
    {
        printf("Nó direito: %d\n", h->data[rFilho]);
    }
    else
    {
        printf("Não há nó filho direito.\n");
    }
}

void print_heap(MaxHeap *h)
{
    printf("Heap: ");
    for (int i = 0; i < h->size; i++)
    {
        printf("%d - ", h->data[i]);
    }
    printf("\n");
}

int main()
{
    MaxHeap h;
    start_heap(&h);

    int op, valor;

    inserir(&h, 64);
    inserir(&h, 10);
    inserir(&h, 32);
    inserir(&h, 12);
    inserir(&h, 8);
    inserir(&h, 5);
    inserir(&h, 3);
    inserir(&h, 9);
    inserir(&h, 11);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Inserir\n");
        printf("2. Remover Máximo\n");
        printf("3. Consultar\n");
        printf("4. Imprimir Heap\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            inserir(&h, valor);
            break;
        case 2:
            valor = remover_Maxheap(&h);
            if (valor != -1)
            {
                printf("Valor máximo removido: %d\n", valor);
            }
            break;
        case 3:
            printf("Digite o valor para consultar: ");
            scanf("%d", &valor);
            consultar_heap(&h, valor);
            break;
        case 4:
            print_heap(&h);
            break;
        case 5:
            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }
}
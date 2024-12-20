#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int data[MAX_SIZE];
    int size;
} MaxHeap;

void initializeHeap(MaxHeap *heap)
{
    heap->size = 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
    {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&heap->data[i], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

void insert(MaxHeap *heap, int value)
{
    if (heap->size >= MAX_SIZE)
    {
        printf("Heap está cheio!\n");
        return;
    }

    int i = heap->size;
    heap->data[i] = value;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i])
    {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int removeMax(MaxHeap *heap)
{
    if (heap->size <= 0)
    {
        printf("Heap está vazio!\n");
        return -1;
    }

    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return max;
}

void consulta(MaxHeap *heap, int valor)
{
    int found = -1;

    for (int i = 0; i < heap->size; i++)
    {
        if (heap->data[i] == valor)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Valor %d não encontrado no heap.\n", valor);
        return;
    }

    int parent = (found - 1) / 2;
    int leftChild = 2 * found + 1;
    int rightChild = 2 * found + 2;

    printf("Valor encontrado no índice %d.\n", found);

    if (found != 0)
    {
        printf("Nó pai: %d\n", heap->data[parent]);
    }
    else
    {
        printf("Este é o nó raiz, sem nó pai.\n");
    }

    if (leftChild < heap->size)
    {
        printf("Nó filho esquerdo: %d\n", heap->data[leftChild]);
    }
    else
    {
        printf("Não há nó filho esquerdo.\n");
    }

    if (rightChild < heap->size)
    {
        printf("Nó filho direito: %d\n", heap->data[rightChild]);
    }
    else
    {
        printf("Não há nó filho direito.\n");
    }
}

void printHeap(MaxHeap *heap)
{
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main()
{
    MaxHeap heap;
    initializeHeap(&heap);

    int opcao, valor;

    insert(&heap, 64); // valores pre-inseridos no heap
    insert(&heap, 10);
    insert(&heap, 32);
    insert(&heap, 12);
    insert(&heap, 8);
    insert(&heap, 5);
    insert(&heap, 3);
    insert(&heap, 9);
    insert(&heap, 11);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Inserir\n");
        printf("2. Remover Máximo\n");
        printf("3. Consultar\n");
        printf("4. Imprimir Heap\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            insert(&heap, valor);
            break;
        case 2:
            valor = removeMax(&heap);
            if (valor != -1)
            {
                printf("Valor máximo removido: %d\n", valor);
            }
            break;
        case 3:
            printf("Digite o valor para consultar: ");
            scanf("%d", &valor);
            consulta(&heap, valor);
            break;
        case 4:
            printHeap(&heap);
            break;
        case 5:
            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}

#ifndef LISTA_H
#define LISTA_H

// Estrutura de uma célula (nó) da lista
typedef struct Celula
{
    int valor; // Valor armazenado na célula
    struct Celula *prox;
    struct Celula *last; // Ponteiro para o próximo nó
} Celula;

// Estrutura da lista encadeada
typedef struct Lista
{
    int size;
    Celula *primeiro; // Ponteiro para o primeiro nó da lista
    Celula *ultimo;   // Ponteiro para o último nó da lista
} Lista;

// Funções para manipulação da lista encadeada
Lista criar_lista();

Celula *criar_celula(int valor);

void liberar_lista(Lista *lista);

void inserir_elemento(Lista *lista, Celula *adr);

void imprimir_lista(Lista *lista);

void deletar_elemento(Lista *lista, Celula *adr);

#endif

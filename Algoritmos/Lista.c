#include <stdio.h>
#include <stdlib.h>

typedef struct Lista
{

    int data;
    struct Lista *next;

} Lista;

Lista *createLista(int qtd)
{
    int i = 0;
    Lista *head = NULL;
    Lista *temp = NULL;
    Lista *p = NULL;

    for (i = 0; i < qtd; i++)
    {

        temp = (Lista *)malloc(sizeof(Lista)); // cria um node(temp) isolado da Lista;
        printf("Insira um dado para o node %d da lista :", i + 1);
        scanf("%d", &(temp->data));
        temp->next = NULL;

        if (head == NULL)
        { // se a lista estiver vazia, o temp vira o primeiro elemento da lista;
            head = temp;
        }
        else
        {
            p = head;
            while (p->next != NULL)
            { // caso contrario, ele passa por toda a lista ate o final dela e coloca o novo elemento 'temp';
                p = p->next;
            }
            p->next = temp;
        }
    }
    return head;
}

void ImprimeLista(Lista *head)
{ // imprime todos os elementos sa lista, interando p até que chegue no ponteiro NULL;
    Lista *p = head;

    while (p != NULL)
    {
        if (p->next != NULL)
        {

            printf("%d->", p->data);
        }
        else
        {
            printf("%d", p->data);
        }

        p = p->next;
    }
    printf("\n");
}

int main()
{
    int qtd = 0;
    Lista *head = NULL;
    printf("Olá, informe quantos nodes sua lista terá:");
    scanf("%d", &qtd);
    head = createLista(qtd);

    ImprimeLista(head);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno
{
    float notas;
    float frequencia;
    struct Aluno *next;

} Aluno;

Aluno *createAluno(float n, float f)
{ // instancia um novo aluno;
    Aluno *alunoNew = (Aluno *)malloc(sizeof(Aluno));
    alunoNew->frequencia = f;
    alunoNew->notas = n;
    alunoNew->next = NULL;
    return alunoNew;
}

void addAluno(Aluno **head, float n, float f)
{
    Aluno *alunoNew = createAluno(n, f);
    alunoNew->next = *head;
    *head = alunoNew;
}

Aluno *reverterLista(Aluno *head)
{
    Aluno *prev = NULL;
    Aluno *atual = head;
    Aluno *next = NULL;

    while (atual != NULL)
    {
        next = atual->next;
        atual->next = prev;
        prev = atual;
        atual = next;
    }
    return prev;
}

void calcularResultados(Aluno *head)
{
    Aluno *atual = head;
    float soma_notas = 0;
    int total_alunos = 0, aprovados = 0, reprovados = 0;

    while (atual != NULL)
    {
        soma_notas += atual->notas;
        total_alunos++;

        if (atual->notas >= 6.0 && atual->frequencia >= 75.0)
        {
            aprovados++;
        }
        else
        {
            reprovados++;
            printf("\nAluno %d reprovado por: ", total_alunos);
            if (atual->notas < 6.0 && atual->frequencia < 75.0)
            {
                printf("nota e frequencia.\n");
            }
            else if (atual->notas < 6.0)
            {
                printf("nota.\n");
            }
            else
            {
                printf("frequencia.\n");
            }
        }
        atual = atual->next;
    }

    printf("Média geral da sala: %.2f\n", soma_notas / total_alunos);
    printf("Aprovados: %d\n", aprovados);
    printf("Reprovados: %d\n", reprovados);
}

int main()
{
    Aluno *head = NULL;
    float nota, freq;

    for (int i = 0; i < 3; i++)
    {
        printf("Aluno %d:\n", i + 1);
        printf("Digite a nota do aluno:");
        scanf("%f", &nota);
        printf("Digite a frequenciado aluno: ");
        scanf("%f", &freq);
        addAluno(&head, nota, freq);
    }

    head = reverterLista(head);

    calcularResultados(head);

    Aluno *att = head;
    while (att != NULL)
    {
        Aluno *temp = att;
        att = att->next;
        free(temp);
    }

    return 0;
}
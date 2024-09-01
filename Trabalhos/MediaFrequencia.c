#include <stdio.h>

#define N_ALUNOS 30

int main()
{

    int aprovados = 0, reprovados = 0;
    int i = 0;
    float media = 0;

    float notafreq[N_ALUNOS][2]; // 2 colunas, a 0 guarda as notas e a 1 as frequencias;

    for (i = 0; i < N_ALUNOS; i++)
    {

        printf("Aluno Numero %d:\n", i + 1);
        printf("Digite a nota do aluno: ");

        scanf("%f", &notafreq[i][0]);

        printf("Digite a frequencia do aluno: ");
        scanf("%f", &notafreq[i][1]);
    }

    for (i = 0; i < N_ALUNOS; i++)
    {
        media += notafreq[i][0];

        if (notafreq[i][0] >= 6.0 && notafreq[i][1] >= 75.0)
        {
            aprovados++;
        }
        else
        {
            reprovados++;
            printf("Aluno Numero %d reprovado por:", i + 1);

            if (notafreq[i][0] < 6.0 && notafreq[i][1] < 75.0)
            {
                printf("Nota e frequencia\n");
            }

            else if (notafreq[i][0] < 6.0)
            {
                printf("Nota\n");
            }

            else
            {
                printf("Frequencia\n");
            }
        }
    }

    printf("Media Geral da sala: %f\n", media / N_ALUNOS);
    printf("Alunos aprovados: %d\n", aprovados);
    printf("Alunos reprovados: %d\n", reprovados);

    return 0;
}
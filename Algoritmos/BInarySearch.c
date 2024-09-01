#include <stdio.h>

int BinarySearch(int busca, int *vector)
{
    int meio = 0;
    int inicio = 0, final = 9;
    int chute = 0;

    while (inicio <= final)
    {
        meio = (inicio + final) / 2;
        chute = vector[meio];

        if (chute == busca)
        {
            return meio;
        }
        if (chute > busca)
        {
            final = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }
    return meio;
}
int main()
{
    int bsearch = 0, busca = 0;
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    scanf("%d", &busca);
    bsearch = BinarySearch(busca, v);

    printf("%d\n", bsearch);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int DistMin(int dist[], int sptSet[], int qtdv)
{
    int min = MAX;
    int min_index;

    for (int v = 0; v < qtdv; v++)
    {
        if (sptSet[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printSolution(int dist[], int qtdv)
{
    printf("Vertice \t Distancia do vertice origem \n");
    for (int i = 0; i < qtdv; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void djikstra(int **graph, int origem, int qtdv)
{
    int dist[qtdv];
    int sptSet[qtdv];

    for (int i = 0; i < qtdv; i++)
    {
        dist[i] = MAX;
        sptSet[i] = 0;
    }

    dist[origem] = 0;

    for (int count = 0; count < qtdv - 1; count++)
    {
        int u = DistMin(dist, sptSet, qtdv);

        sptSet[u] = 1;

        for (int v = 0; v < qtdv; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printSolution(dist, qtdv);
}
int main()
{
    int qtdv, qtde;
    int mcost[MAX][MAX];
    int u, v, peso, origem;
    printf("Insira a quantidade de vertices: \n");
    scanf("%d", &qtdv);

    printf("Insira a quantidade de arestas: \n");
    scanf("%d", &qtde);

    int **graph = (int **)malloc(qtdv * sizeof(int *));

    for (int i = 0; i < qtdv; i++)
    {
        graph[i] = (int *)malloc(qtdv * sizeof(int));
    }

    for (int i = 0; i < qtdv; i++)
    {
        for (int j = 0; j < qtdv; j++)
        {
            graph[i][j] = 0;
        }
    }

    printf("Insira a ordem das arestas e o peso: \n");
    for (int i = 0; i < qtde; i++)
    {
        printf("Aresta %d:", i + 1);
        scanf("%d %d %d", &u, &v, &peso);
        graph[u][v] = peso;
        graph[v][u] = peso;
    }

    printf("Informe o vertice de origem: \n");
    scanf("%d", &origem);

    djikstra(graph, origem, qtdv);

    for (int i = 0; i < qtdv; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX // Representa a ausência de caminho
#define V 5         // numero de quantos vertices existem no grafo

// Função para imprimir a matriz de distâncias
void printDist(int dist[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Função para encontrar e imprimir o caminho mais curto usando o algoritmo de Floyd-Warshall
void floydWarshall(int graph[V][V])
{
    int dist[V][V]; // Matriz de distâncias
    int next[V][V]; // Matriz para reconstrução do caminho

    // Inicializa as matrizes de distâncias e próximos passos
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }

    // Atualiza distâncias com base no algoritmo de Floyd-Warshall
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Mostra a matriz final de distâncias
    printf("Matriz de distâncias mais curtas:\n");
    printDist(dist);

    // Solicita ao usuário os pontos de origem e destino
    int origem, destino;
    printf("\nDigite o ponto de origem (0 a %d): ", V - 1);
    scanf("%d", &origem);
    printf("Digite o ponto de destino (0 a %d): ", V - 1);
    scanf("%d", &destino);

    // Mostra o caminho ou informa que não há caminho possível
    if (dist[origem][destino] == INF)
    {
        printf("Não existe caminho entre os pontos %d e %d.\n", origem, destino);
    }
    else
    {
        printf("Caminho mais curto entre %d e %d: ", origem, destino);
        int atual = origem;
        while (atual != destino)
        {
            printf("%d -> ", atual);
            atual = next[atual][destino];
        }
        printf("%d\n", destino);
        printf("Distância total: %d\n", dist[origem][destino]);
    }
}

// Função principal
int main()
{
    int graph[V][V] = {
        {0, 3, INF, INF, 5},
        {2, 0, INF, 6, INF},
        {INF, 7, 0, 4, 2},
        {INF, INF, 1, 0, INF},
        {INF, INF, INF, 2, 0}};

    printf("Grafo inicial:\n");
    printDist(graph);

    floydWarshall(graph);

    return 0;
}

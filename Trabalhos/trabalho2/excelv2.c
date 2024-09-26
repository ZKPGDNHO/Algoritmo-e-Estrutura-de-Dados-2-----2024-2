#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define ROWS 30 // Número de alunos (linhas)
#define COLS 30 // Número de atributos (colunas: nota 1, nota 2, frequência, média, situação)

typedef struct tuple
{
    float n1;
    float n2;
    float freq;
    float media;
    char situacao;
} Tupla;

void inserirDados(Tupla matriz[ROWS])
{
    for (int i = 0; i < ROWS; i++)
    {
        printf("Inserindo dados para o aluno %d:\n", i + 1);
        printf("Nota 1: ");
        scanf("%f", &matriz[i].n1);
        printf("Nota 2: ");
        scanf("%f", &matriz[i].n2);
        printf("Frequência (em %%): ");
        scanf("%f", &matriz[i].freq);

        // Define a situação com base nas notas e na frequência
    }
}

// Função para exibir os dados da matriz formatados por linhas e colunas (colunas representando atributos)
void mostrarMatriz(Tupla matriz[ROWS])
{
    // Cabeçalho
    for (int w = 0; w < 5; w++)
    {
        printf("        %c", 'A' + w); // Letras do alfabeto para as colunas
    }
    printf("\n");

    // Exibe os dados de cada aluno
    for (int i = 0; i < ROWS; i++)
    {

        printf("Aluno %d:  %6.2f  %6.2f   %6.2f   %6.2f     %c\n",
               i + 1, matriz[i].n1, matriz[i].n2, matriz[i].freq, matriz[i].media, matriz[i].situacao);
    }
}

int isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função para definir a precedência dos operadores
int precedence(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

// Função para realizar a operação entre dois números
float applyOperator(float a, float b, char operator)
{
    switch (operator)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}

// Função para converter referência como "A1" para o valor correto na matriz
float getValueFromReference(char col, int row, Tupla matriz[ROWS])
{
    int rowIndex = row - 1;            // Convertendo o índice da linha para 0-based
    int colIndex = toupper(col) - 'A'; // Convertendo a letra para um índice 0-based

    if (rowIndex >= ROWS || colIndex >= COLS || rowIndex < 0 || colIndex < 0)
    {
        printf("Erro: Referência fora dos limites da matriz!\n");
        return 0.0;
    }

    switch (colIndex)
    {
    case 0:
        return matriz[rowIndex].n1;
    case 1:
        return matriz[rowIndex].n2;
    case 2:
        return matriz[rowIndex].freq;
    case 3:
        return matriz[rowIndex].media;
    default:
        printf("Erro: Coluna inválida!\n");
        return 0.0;
    }
}

// Função para avaliar a expressão usando pilhas
float evaluateExpression(char *expression, Tupla matriz[ROWS])
{
    float values[100];   // Pilha para valores
    char operators[100]; // Pilha para operadores
    int valIndex = -1, opIndex = -1;

    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == ' ')
            continue; // Ignorar espaços em branco

        // Substituição de referências do tipo A1, B2, etc.
        if (isalpha(expression[i]) && isdigit(expression[i + 1]))
        {
            char col = expression[i];
            int row = expression[i + 1] - '0';
            float value = getValueFromReference(col, row, matriz);
            values[++valIndex] = value;
            i++; // Pular o próximo caractere (número da linha)
        }
        // Se for um número, adicionar à pilha de valores
        else if (isdigit(expression[i]))
        {
            float num = 0;
            while (isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Retroceder um caractere
            values[++valIndex] = num;
        }
        // Se for um parêntese esquerdo, adicionar à pilha de operadores
        else if (expression[i] == '(')
        {
            operators[++opIndex] = expression[i];
        }
        // Se for um parêntese direito, resolver até encontrar '('
        else if (expression[i] == ')')
        {
            while (opIndex >= 0 && operators[opIndex] != '(')
            {
                float val2 = values[valIndex--];
                float val1 = values[valIndex--];
                char op = operators[opIndex--];
                values[++valIndex] = applyOperator(val1, val2, op);
            }
            opIndex--; // Remover '(' da pilha de operadores
        }
        // Se for operador, processar operadores anteriores com maior precedência
        else if (isOperator(expression[i]))
        {
            while (opIndex >= 0 && precedence(operators[opIndex]) >= precedence(expression[i]))
            {
                float val2 = values[valIndex--];
                float val1 = values[valIndex--];
                char op = operators[opIndex--];
                values[++valIndex] = applyOperator(val1, val2, op);
            }
            operators[++opIndex] = expression[i];
        }
    }

    // Processar os operadores restantes
    while (opIndex >= 0)
    {
        float val2 = values[valIndex--];
        float val1 = values[valIndex--];
        char op = operators[opIndex--];
        values[++valIndex] = applyOperator(val1, val2, op);
    }

    // O resultado final estará no topo da pilha de valores
    return values[valIndex];
}

void checkSituação(Tupla matriz[ROWS])
{
    int i = 0;

    for (i = 0; i < COLS; i++)
    {
        if (matriz[i].media >= 6.0 && matriz[i].freq >= 75.0)
        {
            matriz[i].situacao = 'A'; // Aprovado
        }
        else
        {
            matriz[i].situacao = 'R'; // Reprovado
        }
    }
}

int main()
{
    Tupla matriz[COLS] = {0};
    int option;
    char expression[20];
    int n1row, n1col, n2row, n2col;
    float n1, n2, result;
    int e = 0;

    do
    {
        mostrarMatriz(matriz); // Mostra a planilha atual

        printf("\nMenu:\n");
        printf("1. Inserir valor na planilha\n");
        printf("2. Realizar operação\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1: // Insere os valores na matriz
            inserirDados(matriz);
            break;

        case 2: // Realiza uma operação entre os valores da matriz
            printf("Escolha a linha a linha onde quer realizar a operaçao:");
            scanf("%d", &e);
            getchar();
            printf("Digite a expressão: ");
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = 0; // Remove o \n final

            printf("Expressão: %s\n", expression);

            // Avalia a expressão
            result = evaluateExpression(expression, matriz);
            matriz[e - 1].media = result; // Armazena o resultado na coluna "média"
            printf("Resultado: %.2f\n", result);
            checkSituação(matriz);
            usleep(700000); // Pausa por 0.7 segundos
            break;

        case 0: // Sai do programa
            printf("Saindo...\n");
            break;

        default: // Opção inválida
            printf("Opção inválida!\n");
        }
    } while (option != 0);

    return 0;
}

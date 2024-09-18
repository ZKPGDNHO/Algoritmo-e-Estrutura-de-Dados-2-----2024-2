#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define ROWS 30
#define COLS 4

void displaySheet(float sheet[ROWS][COLS])
{
    int i = 0, j = 0;
    printf("\nPlanilha atual:\n");
    for (int w = 0; w < COLS; w++)
    {
        printf("COLUNA:%d \t", w + 1);
    }
    printf("\n");
    for (i = 0; i < ROWS; i++)
    {

        for (j = 0; j < COLS; j++)
        {
            printf("LINHA %d:", j + 1);
            printf("%6.2f |", sheet[i][j]);
        }
        printf("\n");
    }
}

void inputData(float sheet[ROWS][COLS])
{
    int row, col;
    float value;
    printf("Digite a linha, coluna e o valor a ser inserido (Exemplo: 0 1 10.5): ");
    scanf("%d %d %f", &row, &col, &value);

    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    {
        sheet[row][col] = value;
    }
    else
    {
        printf("Posição inválida!\n");
    }
}

// Função para determinar se um caractere é operador
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

// Função para avaliar a expressão usando pilhas
float evaluateExpression(char *expression, float n1, float n2)
{
    float values[100];   // Pilha para valores
    char operators[100]; // Pilha para operadores
    int valIndex = -1, opIndex = -1;

    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == ' ')
            continue; // Ignorar espaços em branco

        // Substituição das variáveis 'n1' e 'n2'
        if (expression[i] == 'n' && expression[i + 1] == '1')
        {
            values[++valIndex] = n1;
            i++; // Pular o próximo caractere
        }
        else if (expression[i] == 'n' && expression[i + 1] == '2')
        {
            values[++valIndex] = n2;
            i++; // Pular o próximo caractere
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

void avaliaSituacao(float s[ROWS][COLS])
{
    int aprovados = 0;
    int reprovados = 0;
    for (int i = 0; i < ROWS; i++)
    {

        if (s[i][3] >= 6.0 && s[i][2] >= 75.0)
        {
            aprovados++;
        }
        else
        {
            reprovados++;
            printf("Aluno Numero %d reprovado por:", i + 1);

            if (s[i][3] < 6.0 && s[i][2] < 75.0)
            {
                printf("Nota e frequencia\n");
            }

            else if (s[i][3] < 6.0)
            {
                printf("Nota\n");
            }

            else
            {
                printf("Frequencia\n");
            }
        }
    }

    printf("Alunos aprovados: %d\n", aprovados);
    printf("Alunos reprovados: %d\n", reprovados);
}

int main()
{
    float sheet[ROWS][COLS] = {0}; // Inicializa a planilha com zeros
    int option;
    int n1row, n1col, n2row, n2col;
    char expression[20];
    float n1 = 0, n2 = 0;
    float result = 0, freq = 0;

    do
    {
        displaySheet(sheet);

        printf("\nMenu:\n");
        printf("1. Inserir valor na planilha\n");
        printf("2. Realizar operação\n");
        printf("3. Avaliar situacao dos Alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1: // coloca os valores na matriz;
            inputData(sheet);

            break;
        case 2: // aqui os valores já deve3m estar alocados, por isso pede a posicao;
            printf("Digite as linhas e as colunas respectivas de qual operação deseja realizar: (EX.: 0 0 0 1)");
            scanf("%d %d %d %d", &n1row, &n1col, &n2row, &n2col);
            getchar();

            n1 = sheet[n1row][n1col], n2 = sheet[n2row][n2col];

            printf("Digite a expressão (use n1 e n2 como variáveis): "); // parte que pega a expressao, transforma os chars dela e resolve
            fgets(expression, sizeof(expression), stdin);
            expression[strcspn(expression, "\n")] = 0;

            printf("Expressão: %s\n", expression);
            printf("n1 = %.2f, n2 = %.2f\n", n1, n2);

            result = evaluateExpression(expression, n1, n2);
            sheet[n2row][n2col + 2] = result;
            freq = sheet[n2row][n2col + 1];
            printf("Resultado: %.2f\n", result);
            usleep(700000);
            break;
        case 3:
            avaliaSituacao(sheet);
            usleep(700000);
            break;
        case 0:
            printf("Saindo...\n");

            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (option != 0);

    return 0;
}
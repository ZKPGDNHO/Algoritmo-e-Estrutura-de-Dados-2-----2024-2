#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int main()
{
    float m[2][2];
    printf("Digite a expressão (use n1 e n2 como variáveis): ");
    scanf("%f %f %f %f", &m[0][0], &m[0][1], &m[1][0], &m[1][1]);

    float n1 = m[0][0], n2 = m[0][1];
    char expression[100];

    getchar();
    printf("Digite a expressão (use n1 e n2 como variáveis): ");
    fgets(expression, sizeof(expression), stdin);

    expression[strcspn(expression, "\n")] = 0;

    printf("Expressão: %s\n", expression);
    printf("n1 = %.2f, n2 = %.2f\n", n1, n2);

    float result = evaluateExpression(expression, n1, n2);
    printf("Resultado: %.2f\n", result);

    return 0;
}

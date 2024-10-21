#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"
#include "pilha.h"

#define ResWords 179
#define MaxLenght 200

char *ReservedWords[] = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict",
    "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
    "_Noreturn", "_Static_assert", "_Thread_local",
    "#include", "#define", "#undef", "#if", "#ifdef", "#ifndef",
    "#else", "#elif", "#endif", "#error", "#pragma", "main",
    "printf", "scanf", "fprintf", "fscanf", "sprintf", "sscanf",
    "snprintf", "vprintf", "vfprintf", "vsprintf", "vsnprintf",
    "putc", "getc", "getchar", "putchar", "fgets", "fputs", "rewind",
    "fopen", "fclose", "feof", "ferror", "clearerr", "remove", "rename",
    "tmpfile", "tmpnam", "setbuf", "setvbuf", "fprintf", "fscanf", "fflush",
    "fseek", "ftell", "rewind", "fgetpos", "fsetpos", "perror", "fileno",
    "malloc", "calloc", "realloc", "free", "exit", "atexit", "system",
    "abort", "atexit", "getenv", "system", "clock", "difftime", "time",
    "asctime", "ctime", "gmtime", "localtime", "mktime", "strftime",
    "signal", "raise", "sig_atomic_t", "SIG_DFL", "SIG_ERR", "SIG_IGN",
    "rand", "srand", "rand_r", "abort", "system", "bsearch", "qsort",
    "abs", "labs", "llabs", "div", "ldiv", "lldiv", "atoi", "atol", "atof",
    "strtod", "strtof", "strtold", "strtol", "strtoul", "strtoll", "strtoull",
    "itoa", "ltoa", "lltoa", "utoa", "ultoa", "ulltoa", "getchar", "putchar",
    "gets", "puts", "fgets", "fputs", "scanf", "sscanf", "sprintf", "snprintf",
    "vsprintf", "vsnprintf", "memcpy", "memmove", "memcmp", "memset",
    "strcpy", "strncpy", "strcat", "strncat", "strcmp", "strncmp",
    "strcoll", "strxfrm", "strchr", "strrchr", "strspn", "strcspn",
    "strpbrk", "strstr", "strtok", "strtok_r", "strlen", "strerror",
    "memset", "memcpy", "memmove", "memcmp", "memchr",
    "isalnum", "isalpha", "iscntrl", "isdigit", "isgraph", "islower",
    "isprint", "ispunct", "isspace", "isupper", "isxdigit", "tolower",
    "toupper", "isblank", "isascii", "toascii",
    "log", "log10", "exp", "sqrt", "fabs", "floor", "ceil", "pow", "fmod", "round", "trunc",
    "acos", "asin", "atan", "atan2", "cos", "sin", "tan", "cosh", "sinh", "tanh", "acosh", "asinh", "atanh",
    "errno", "math_errhandling", "INFINITY", "NAN", "HUGE_VAL", "HUGE_VALF", "HUGE_VALL", "M_E", "M_LOG2E", "M_LOG10E",
    "M_LN2", "M_LN10", "M_PI", "M_PI_2", "M_PI_4", "M_1_PI", "M_2_PI", "M_2_SQRTPI", "M_SQRT2", "M_SQRT1_2"};

char TempWord[MaxLenght];

Pilha stack_parenteses_abrir;
Pilha stack_parenteses_fechar;
Pilha stack_chaves_abrir;
Pilha stack_chaves_fechar;
Pilha stack_Colchetes_abrir;
Pilha stack_Colchetes_fechar;
Pilha stack_aspasduplas;
Pilha stack_aspas_simples;
Arvore verifyTree;

int VerificaPilha(const char *c)
{
    Pilha p;
    initStack(&p);
    for (int i = 0; c[i] != '\0'; ++i)
    {
        char ch = c[i];
        if (ch == '{')
        {
            push(&stack_chaves_abrir, ch);
        }
        else if (ch == '(')
        {
            push(&stack_parenteses_abrir, ch);
        }
        else if (ch == '[')
        {
            push(&stack_Colchetes_abrir, ch);
        }
        else if (ch == '}')
        {
            push(&stack_chaves_fechar, ch);
        }
        else if (ch == ')')
        {
            push(&stack_parenteses_fechar, ch);
        }
        else if (ch == ']')
        {
            push(&stack_Colchetes_fechar, ch);
        }
        else if (ch == '"')
        {
            push(&stack_aspasduplas, ch);
        }
        else if (ch == '\'')
        {
            push(&stack_aspas_simples, ch);
        }
    }

    while (stack_chaves_abrir.size > 0 && stack_chaves_fechar.size > 0)
    {
        pop(&stack_chaves_abrir);
        pop(&stack_chaves_fechar);
    }
    while (stack_Colchetes_abrir.size > 0 && stack_Colchetes_fechar.size > 0)
    {
        pop(&stack_Colchetes_abrir);
        pop(&stack_Colchetes_fechar);
    }
    while (stack_parenteses_abrir.size > 0 && stack_parenteses_fechar.size > 0)
    {
        pop(&stack_parenteses_abrir);
        pop(&stack_parenteses_fechar);
    }
}

char *readFile(const char *filename)
{

    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    long fSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *conteudo = (char *)malloc(fSize + 1);
    if (!conteudo)
    {
        fprintf(stderr, "Memoria insuficiente \n");
        exit(EXIT_FAILURE);
    }

    fread(conteudo, 1, fSize, f);
    conteudo[fSize] = '\0';

    fclose(f);
    return conteudo;
}

void print_irregular()
{

    if (stack_chaves_abrir.size > 0)
    {
        printf("O codigo inserido possui erros ao fechar }\n");
    }
    else if (stack_chaves_fechar.size > 0)
    {
        printf("O codigo inserido possui erros ao abrir {\n");
    }
    if (stack_Colchetes_abrir.size > 0)
    {
        printf("O codigo inserido possui erros ao fechar ]\n");
    }
    else if (stack_Colchetes_fechar.size > 0)
    {
        printf("O codigo inserido possui erros ao abrir [\n");
    }
    if (stack_parenteses_abrir.size > 0)
    {
        printf("O codigo inserido possui erros ao fechar )\n");
    }
    else if (stack_parenteses_fechar.size > 0)
    {
        printf("O codigo inserido possui erros ao abrir (\n");
    }
    if (stack_aspasduplas.size % 2 != 0)
    {
        printf("O codigo inserido possui erros ao fechar \" \n");
    }
    if (stack_aspas_simples.size % 2 != 0)
    {
        printf("O codigo inserido possui erros ao fechar '' \n");
    }
}

void popular_tree()
{
    verifyTree.root = NULL;
    for (int i = 0; i < ResWords; i++)
    {
        verifyTree.root = inserir(verifyTree.root, ReservedWords[i]);
    }
};

void CleanWord()
{
    for (int i = 0; i < MaxLenght; i++)
    {
        TempWord[i] = '\0';
    }
}

bool Palavra_similar(char *w)
{
    float qtd = 0;
    float perc = 0;
    for (int i = 0; i < ResWords; i++)
    {
        if (strlen(w) <= strlen(ReservedWords[i]))
        {
            for (int k = 0; k < strlen(w); k++)
            {
                for (int p = 0; p < strlen(ReservedWords[i]); p++)
                {
                    if (w[k] == ReservedWords[i][p])
                    {
                        qtd++;
                    }
                }
            }
            perc = qtd / strlen(ReservedWords[i]) * 100;
            if (perc >= 60)
            {
                return true;
            }
            qtd = 0;
        }
    }
    return false;
}

bool Verify_reserved_words(char *c)
{
    int AuxIndex = 0;
    CleanWord();
    for (int i = 0; c[i] != '\0'; ++i)
    {
        if ((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') || c[i] == '#' || c[i] == '\0' || (c[i] == '<' || c[i] == '>' || c[i] == '.'))
        {
            TempWord[AuxIndex] = c[i];
            AuxIndex++;
        }
        else
        {
            if (strlen(TempWord) > 0)
            {

                if (Palavra_similar(TempWord))
                {

                    if (!Encontrar(verifyTree.root, TempWord))
                    {
                        printf("Palavra apresenta erro na sintaxe: %s\n", TempWord);
                    }
                }
                CleanWord();
                AuxIndex = 0;
            }
        }
    }
}

int main()
{
    initStack(&stack_parenteses_abrir);
    initStack(&stack_parenteses_fechar);
    initStack(&stack_chaves_abrir);
    initStack(&stack_chaves_fechar);
    initStack(&stack_Colchetes_abrir);
    initStack(&stack_Colchetes_fechar);
    initStack(&stack_aspasduplas);
    initStack(&stack_aspas_simples);

    char *conteudo = readFile("teste.c");
    VerificaPilha(conteudo);
    print_irregular();
    popular_tree();
    printf("%s", verifyTree.root->data);
    Verify_reserved_words(conteudo);

    return 0;
}
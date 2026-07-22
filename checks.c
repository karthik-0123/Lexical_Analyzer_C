#include "checks.h"
#include <string.h>
#include <ctype.h>

int checkBrackets(FILE *fp)
{
    int round = 0, curly = 0, square = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        switch (ch)
        {
            case '(':
                round++;
                break;

            case ')':
                round--;
                if (round < 0)
                {
                    printf("Error: Extra ')'\n");
                    return 0;
                }
                break;

            case '{':
                curly++;
                break;

            case '}':
                curly--;
                if (curly < 0)
                {
                    printf("Error: Extra '}'\n");
                    return 0;
                }
                break;

            case '[':
                square++;
                break;

            case ']':
                square--;
                if (square < 0)
                {
                    printf("Error: Extra ']'\n");
                    return 0;
                }
                break;
        }
    }

    if (round || curly || square)
    {
        printf("Error: Brackets are not balanced\n");
        return 0;
    }

    return 1;
}

/*32 Keywords*/
char *keywords[] = {
    "int", "char", "float", "double", "void", "if", "else", "for", "while", "do",
    "switch", "case", "break", "continue", "return", "struct", "union", "enum",
    "typedef", "const", "static", "extern", "goto", "sizeof"};

/*Operators-> Relational , Logical and Unary Opearators*/
char *operators[] = {"+", "-", "*", "/", "%",
                     "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
                     "++", "--", "+=", "-=", "*=", "/=", "%=", "&", "|", "^",
                     "~", "<<", ">>"};

/*Delimiters*/
char delimiters[] = {'(', ')', '{', '}', '[', ']', ';', ',', ':', '.'};

/* Checking whether the word is keyword or not */
int isKeyword(char *word)
{
    int size = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
/* Checking whether the word is operator or not */
int isOperator(char *word)
{
    int size = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(word, operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
/* Checking whether the word is delimeter or not */
int isDelimiter(char ch)
{
    int size = sizeof(delimiters) / sizeof(delimiters[0]);
    for (int i = 0; i < size; i++)
    {
        if (ch == delimiters[i])
        {
            return 1;
        }
    }
    return 0;
}
/* Checking whether the word is Identifier or not */
int isIdentifier(char *word)
{
    if (!(isalpha(word[0]) || word[0] == '_'))
    {
        return 0;
    }
    for (int i = 1; word[i] != '\0'; i++)
    {
        if (!(isalnum(word[i]) || word[i] == '_'))
        {
            return 0;
        }
    }
    return 1;
}
/* Checking whether the word is integer or not */
int isInteger(char *word)
{
    int i = 0;
    if (word[0] == '\0')
    {
        return 0;
    }
    while (word[i] != '\0')
    {
        if (!isdigit(word[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}
/* Checking whether the word is float or not */
int isFloat(char *word)
{
    int i = 0;
    int dotcount = 0;
    if (word[0] == '\0')
    {
        return 0;
    }
    while (word[i] != '\0')
    {
        if (word[i] == '.')
        {
            dotcount++;
        }
        else if (!isdigit(word[i]))
        {
            return 0;
        }
        i++;
    }
    if (dotcount == 1)
    {
        return 1;
    }
    return 0;
}
/* Checking whether the word is string or not */
int isString(char *word)
{
    int len = strlen(word);
    if (word[0] == '"' && word[len - 1] == '"')
    {
        return 1;
    }
    return 0;
}
/* Checking whether the word is character or not */
int isCharacter(char *word)
{
    int len = strlen(word);
    if (word[0] == '\'' && word[len - 1] == '\'' && len == 3)
    {
        return 1;
    }
    return 0;
}
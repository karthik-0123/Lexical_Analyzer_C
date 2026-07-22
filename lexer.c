#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "checks.h"
#include "tokens.h"
#include "lexer.h"
/*The Variables are using to print the final summary*/
int keywordCount = 0;
int identifierCount = 0;
int operatorCount = 0;
int delimiterCount = 0;
int integerCount = 0;
int floatCount = 0;
int stringCount = 0;
int characterCount = 0;
int preprocessorCount = 0;
int unknownCount = 0;
char symbolTable[100][50];
int symbolCount = 0;
int declarationFlag = 0;
void insertSymbol(char *name)
{
    for (int i = 0; i < symbolCount; i++)
    {
        if (strcmp(symbolTable[i], name) == 0)
            return;
    }

    strcpy(symbolTable[symbolCount++], name);
}

int searchSymbol(char *name)
{
    for (int i = 0; i < symbolCount; i++)
    {
        if (strcmp(symbolTable[i], name) == 0)
            return 1;
    }

    return 0;
}
void lexicalAnalyzer(FILE *inpFptr, FILE *outFptr)
{
    /* To print the header in output file */
    fprintf(outFptr, "==========================================================\n");
    fprintf(outFptr, "                 C LEXICAL ANALYZER\n");
    fprintf(outFptr, "==========================================================\n\n");
    fprintf(outFptr, "[INFO] Opening input file...\n");
    fprintf(outFptr, "[INFO] Reading source code...\n");
    fprintf(outFptr, "[INFO] Lexical Analysis Started...\n\n");
    fprintf(outFptr, "----------------------------------------------------------\n");
    fprintf(outFptr, "%-15s %-30s %-20s\n", "Line", "Lexeme", "Token Type");
    fprintf(outFptr, "----------------------------------------------------------\n");
    /* Declaring a variables for fetching the character and buff for validataion of next character
    line and col for printing line no and pos */
    char ch;
    char buf[500];
    int i;
    int line = 1;
    int column = 1;
    /* Fetching one character from input file */
    while ((ch = fgetc(inpFptr)) != EOF)
    {
        /* Skip the white spaces */
        if (isspace(ch))
        {
            if (ch == '\n')
            {
                line++;
                column = 1;
            }
            else
            {
                column++;
            }
            continue;
        }

        /* Preprocessor Directive */
        else if (ch == '#')
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            if (i < sizeof(buf) - 1)
                buf[i++] = ch;

            while ((ch = fgetc(inpFptr)) != '\n' && ch != EOF)
            {
                if (ch != '\r')
                    if (i < sizeof(buf) - 1)
                        buf[i++] = ch;
            }
            if (ch == '\n')
                line++;

            buf[i] = '\0';
            printToken(outFptr, buf, "Preprocessor", startLine, startColumn);
            preprocessorCount++;
        }
        /* Comments or Division*/
        else if (ch == '/')
        {
            char next = fgetc(inpFptr);

            if (next == '/')
            {
                while ((ch = fgetc(inpFptr)) != '\n' && ch != EOF)
                    ;
                line++;
                continue;
            }
            else if (next == '*')
            {
                int startLine = line;
                int startColumn = column;
                char prev = 0;
                int closed = 0;
                while ((ch = fgetc(inpFptr)) != EOF)
                {
                    if (ch == '\n')
                        line++;
                    if (prev == '*' && ch == '/')
                    {
                        closed = 1;
                        break;
                    }
                    prev = ch;
                }
                if (!closed)
                {
                    printToken(outFptr, "/*", "ERROR: Unterminated Comment", startLine, startColumn);
                    unknownCount++;
                }
                continue;
            }
            else
            {
                int startLine = line;
                int startColumn = column;
                ungetc(next, inpFptr);
                strcpy(buf, "/");
                printToken(outFptr, buf, "Operator", startLine, startColumn);
                operatorCount++;
                continue;
            }
        }
        /* Keyword or Identifier */
        else if (isalpha(ch) || ch == '_')
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            while (isalnum(ch) || ch == '_')
            {
                if (i < sizeof(buf) - 1)
                    buf[i++] = ch;

                ch = fgetc(inpFptr);
            }
            buf[i] = '\0';
            ungetc(ch, inpFptr);
            if (isKeyword(buf))
            {
                printToken(outFptr, buf, "Keyword", startLine, startColumn);
                keywordCount++;

                if (strcmp(buf, "int") == 0 ||
                    strcmp(buf, "char") == 0 ||
                    strcmp(buf, "float") == 0 ||
                    strcmp(buf, "double") == 0 ||
                    strcmp(buf, "long") == 0 ||
                    strcmp(buf, "short") == 0)
                {
                    declarationFlag = 1;
                }
            }
            else if (isIdentifier(buf))
            {
                printToken(outFptr, buf, "Identifier", startLine, startColumn);
                identifierCount++;
                if (declarationFlag)
                {
                    char next = fgetc(inpFptr);
                    ungetc(next, inpFptr);

                    if (next == '(')
                    {
                        // Function name (main, printf, etc.)
                        declarationFlag = 0;
                    }
                    else
                    {
                        insertSymbol(buf);
                    }
                }
                else
                {
                    if (!searchSymbol(buf))
                    {
                        printToken(outFptr, buf, "ERROR: Variable Not Declared", startLine, startColumn);
                        unknownCount++;
                    }
                }
            }
            else
            {
                printToken(outFptr, buf, "Unknown", startLine, startColumn);
                unknownCount++;
            }
        }
        /* Integer or Float */
        else if (isdigit(ch))
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            while (isdigit(ch) || ch == '.')
            {
                if (i < sizeof(buf) - 1)
                    buf[i++] = ch;
                ch = fgetc(inpFptr);
            }
            buf[i] = '\0';
            ungetc(ch, inpFptr);
            if (isInteger(buf))
            {
                printToken(outFptr, buf, "Integer", startLine, startColumn);
                integerCount++;
            }
            else if (isFloat(buf))
            {
                printToken(outFptr, buf, "Float", startLine, startColumn);
                floatCount++;
            }
            else
            {
                printToken(outFptr, buf, "Unknown", startLine, startColumn);
                unknownCount++;
            }
        }
        /* String Literal */
        else if (ch == '"')
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            buf[i++] = ch;
            int closed = 0;
            while ((ch = fgetc(inpFptr)) != EOF)
            {
                if (ch == '\n')
                    break;

                if (i < sizeof(buf) - 1)
                    buf[i++] = ch;

                if (ch == '"')
                {
                    closed = 1;
                    break;
                }
            }
            buf[i] = '\0';
            /*To whether the string is enclosed with last quote or not*/
            if (closed)
            {
                printToken(outFptr, buf, "String", startLine, startColumn);
                stringCount++;
            }
            else
            {
                printToken(outFptr, buf, "ERROR: Unterminated String", startLine, startColumn);
                unknownCount++;
            }
            buf[i] = '\0';
        }
        /* Character Literal */
        else if (ch == '\'')
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            buf[i++] = ch;
            int closed = 0;
            while ((ch = fgetc(inpFptr)) != EOF)
            {
                if (ch == '\n')
                    break;
                if (i < sizeof(buf) - 1)
                    buf[i++] = ch;
                if (ch == '\'')
                {
                    closed = 1;
                    break;
                }
            }
            buf[i] = '\0';
            /*To check whether character is enclosed with last quote or not*/
            if (closed)
            {
                printToken(outFptr, buf, "Character", startLine, startColumn);
                characterCount++;
            }
            else
            {
                printToken(outFptr, buf, "ERROR: Unterminated Character", startLine, startColumn);
                unknownCount++;
            }
        }

        /* Operators */
        else
        {
            int startLine = line;
            int startColumn = column;
            i = 0;
            buf[i++] = ch;
            char next = fgetc(inpFptr);
            if (next != EOF)
            {
                buf[i++] = next;
                buf[i] = '\0';
                if (isOperator(buf))
                {
                    printToken(outFptr, buf, "Operator", startLine, startColumn);
                    operatorCount++;
                }
                else
                {
                    ungetc(next, inpFptr);
                    buf[1] = '\0';
                    if (isOperator(buf))
                    {
                        printToken(outFptr, buf, "Operator", startLine, startColumn);
                        operatorCount++;
                    }
                    else if (isDelimiter(buf[0]))
                    {
                        printToken(outFptr, buf, "Delimiter", startLine, startColumn);
                        delimiterCount++;

                        if (buf[0] == ';')
                        {
                            declarationFlag = 0;
                        }
                    }
                    else
                    {
                        printToken(outFptr, buf, "Unknown", startLine, startColumn);
                        unknownCount++;
                    }
                }
            }
            else
            {
                /* Handle the last character before EOF */
                buf[1] = '\0';
                if (isOperator(buf))
                {
                    printToken(outFptr, buf, "Operator", startLine, startColumn);
                    operatorCount++;
                }
                else if (isDelimiter(buf[0]))
                {
                    printToken(outFptr, buf, "Delimiter", startLine, startColumn);
                    delimiterCount++;
                }
                else
                {
                    printToken(outFptr, buf, "Unknown", startLine, startColumn);
                    unknownCount++;
                }
            }
        }
    }
    fprintf(outFptr, "\n");
    fprintf(outFptr, "========================================\n");
    fprintf(outFptr, "          TOKEN SUMMARY\n");
    fprintf(outFptr, "========================================\n");
    fprintf(outFptr, "       Preprocessors : %d\n", preprocessorCount);
    fprintf(outFptr, "       Keywords      : %d\n", keywordCount);
    fprintf(outFptr, "       Identifiers   : %d\n", identifierCount);
    fprintf(outFptr, "       Operators     : %d\n", operatorCount);
    fprintf(outFptr, "       Delimiters    : %d\n", delimiterCount);
    fprintf(outFptr, "       Integers      : %d\n", integerCount);
    fprintf(outFptr, "       Floats        : %d\n", floatCount);
    fprintf(outFptr, "       Strings       : %d\n", stringCount);
    fprintf(outFptr, "       Characters    : %d\n", characterCount);
    fprintf(outFptr, "       Unknown       : %d\n", unknownCount);

    int total = preprocessorCount + keywordCount + identifierCount +
                operatorCount + delimiterCount + integerCount +
                floatCount + stringCount + characterCount +
                unknownCount;

    fprintf(outFptr, "----------------------------------------\n");
    fprintf(outFptr, "       Total Tokens  : %d\n", total);
    fprintf(outFptr, "========================================\n");
}
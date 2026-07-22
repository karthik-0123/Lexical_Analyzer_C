#include "tokens.h"
#include <stdio.h>

void printToken(FILE *outFptr, char *lexeme, char *tokenType, int line, int pos)
{
    fprintf(outFptr, "input.c:%2d:%2d: %-15s %s\n", line, pos, tokenType, lexeme);
}

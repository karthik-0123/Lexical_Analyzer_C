#ifndef CHECKS_H
#define CHECKS_H
#include <stdio.h>
/*To check keyword*/
int isKeyword(char *word);
/*To check identifier*/
int isIdentifier(char *word);
/*To check Integer*/
int isInteger(char *word);
/*To check Float*/
int isFloat(char *word);
/*To check operator*/
int isOperator(char *word);
/*To check delimeter*/
int isDelimiter(char ch);
/*To check string*/
int isString(char *word);
/*To check character*/
int isCharacter(char *word);
#endif
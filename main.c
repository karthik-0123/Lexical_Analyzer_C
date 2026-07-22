/*Name : Jupalli Karthik
Date : 16-07-2026
Title : Lexical Analyzer Porject
Description : Developed a Lexical Analyzer in C to tokenize C source code into keywords, identifiers, operators, delimiters, literals, and preprocessor directives.
              Implemented lexical error detection for unterminated strings, character literals, comments, unknown symbols, and invalid tokens with line and position tracking.
              Generated a detailed token report and summary, demonstrating the first phase of compiler design through efficient lexical analysis.
*/
#include <stdio.h>
#include "lexer.h"
#include <string.h>
#include "colors.h"
#include "checks.h"
int main(int argc,char *argv[])
{
    printf(BCYAN "=========================================================\n" RESET);
    printf(BGREEN "               C LEXICAL ANALYZER\n" RESET);
    printf(BCYAN "=========================================================\n\n" RESET);
    printf(BYELLOW "[INFO] Lexical Analysis Process Started...\n" RESET);
    if(argc != 2){
        printf("[ERROR] Invalid number of arguments\n");
        printf("./a.out file.c\n");
        return 1;
    }
    if(strstr(argv[1],".c") == NULL){
        printf("[ERROR] Enter .c file\n");
        return 1;
    }
    /*To open the C input file in read mode*/
    FILE *inpFptr = fopen(argv[1], "r");
    if (inpFptr == NULL)
    {
        printf(BRED "[ERROR] Unable to open source file %s\n"RESET,argv[1]);
        return 1;
    }
    printf(BGREEN "[INFO] Source file opened successfully.\n" RESET);
    if (!checkBrackets(inpFptr))
    {
        fclose(inpFptr);
        return 1;
    }

    /* Move file pointer back to the beginning */
    rewind(inpFptr);

    /*To open the Output file in write mode*/
    FILE *outFptr = fopen("output.txt", "w");
    if (outFptr == NULL)
    {
        printf(BRED "[ERROR] Unable to create output file (output.txt)\n" RESET);
        fclose(inpFptr);
        return 1;
    }
    printf(BGREEN "[INFO] Output file created successfully.\n" RESET);
    printf(BYELLOW "[INFO] Performing Lexical Analysis...\n\n" RESET);
    /*Calling function to perfrom operations*/
    lexicalAnalyzer(inpFptr, outFptr);
    /*Closing the files*/
    fclose(inpFptr);
    fclose(outFptr);
    printf(BGREEN "\n[INFO] Lexical Analysis Completed Successfully.\n" RESET);
    printf(BGREEN "[INFO] Token information stored in output.txt\n" RESET);
    printf(BCYAN "=========================================================\n" RESET);
    printf(BGREEN "                 THANK YOU\n" RESET);
    printf(BCYAN "=========================================================\n" RESET);
    return 0;
}
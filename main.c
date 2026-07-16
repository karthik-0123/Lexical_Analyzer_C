/*Name : Jupalli Karthik
Date : 16-07-2026
Title : Lexical Analyzer Porject
Description : Developed a Lexical Analyzer in C to tokenize C source code into keywords, identifiers, operators, delimiters, literals, and preprocessor directives.
              Implemented lexical error detection for unterminated strings, character literals, comments, unknown symbols, and invalid tokens with line and position tracking.
              Generated a detailed token report and summary, demonstrating the first phase of compiler design through efficient lexical analysis.*/
#include <stdio.h>
#include "lexer.h"
#include "colors.h"

int main()
{
    printf(BCYAN "=========================================================\n" RESET);
    printf(BGREEN "               C LEXICAL ANALYZER\n" RESET);
    printf(BCYAN "=========================================================\n\n" RESET);
    printf(BYELLOW "[INFO] Lexical Analysis Process Started...\n" RESET);
    /*To open the C input file in read mode*/
    FILE *inpFptr = fopen("input.c", "r");
    if (inpFptr == NULL)
    {
        printf(BRED "[ERROR] Unable to open source file (input.c)\n" RESET);
        return 1;
    }
    printf(BGREEN "[INFO] Source file opened successfully.\n" RESET);
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
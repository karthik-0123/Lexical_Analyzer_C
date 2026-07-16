#include <stdio.h>

#define SIZE 10

int main()
{
    int a = 10;
    float b = 12.34;
    char ch = 'A';
    char nl = '\n';
    char *msg = "Hello World";

    // Valid operators
    a++;
    b--;
    a += 5;
    a == 10;

    // Invalid float
    float x = 12.34.56;

    // Unterminated string
    char *str = "Hello World;

    // Unterminated character
    char c = 'X;

    // Unknown symbols
    int p = 10 @ 20;
    int q = 30 $ 40;
    int r = 50 ` 60;

    // Unterminated comment
    /*
    This comment is never closed

    return 0;
    */
}
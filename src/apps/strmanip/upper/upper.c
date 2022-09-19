/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just changes whatever was passed into the program into uppercase.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int toupper(int c)
{
    if (c > 96 && c < 127)
        c -= 32;
    return c;
}

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]);j++)
        {
            printf("%c", toupper(argv[i][j]));
        }
        printf("\n");
    }
    return 0;
}
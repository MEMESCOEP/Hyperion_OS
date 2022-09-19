/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just compares the first argument passed with the second argument.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (strlen(argv[1]) == strlen(argv[2]))
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (argv[1][i] != argv[2][i])
                printf("Change at: %d\n", i);
        }
    }
    else 
    {
        printf("%s is larger, compare ignored\n", strlen(argv[1]) > strlen(argv[2]) ? "Argument 1" : "Argument 2");
    }
    return 0;
}
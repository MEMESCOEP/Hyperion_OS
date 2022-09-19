/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just gets the rot13 of whatever was passed into the program.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    switch(atoi(argv[argc - 1]))
    {
    case 5:
        for (int i = 1; i < argc - 1; i++)
        {
            for (int j = 0; j < strlen(argv[i]);j++)
            {
                if(isdigit(argv[i][j]))
                    printf("%c", isdigit(argv[i][j] + 5) ? argv[i][j] + 5 : argv[i][j] - 5);
                else
                    printf("%c", argv[i][j]);
            }
            printf("\n");
        }
        break;
    case 13:
        for (int i = 1; i < argc - 1; i++)
        {
            for (int j = 0; j < strlen(argv[i]);j++)
            {
                if(isupper(argv[i][j]))
                    printf("%c", isupper(argv[i][j] + 13) ? argv[i][j] + 13 : argv[i][j] - 13);
                else if (islower(argv[i][j]))
                    printf("%c", islower(argv[i][j] + 13) ? argv[i][j] + 13 : argv[i][j] - 13);
                else
                    printf("%c", argv[i][j]);
            }
            printf("\n");
        }
        break;
    case 18:
        for (int i = 1; i < argc - 1; i++)
        {
            for (int j = 0; j < strlen(argv[i]);j++)
            {
                if(isdigit(argv[i][j]))
                    printf("%c", isdigit(argv[i][j] + 5) ? argv[i][j] + 5 : argv[i][j] - 5);
                else if(isupper(argv[i][j]))
                    printf("%c", isupper(argv[i][j] + 13) ? argv[i][j] + 13 : argv[i][j] - 13);
                else if (islower(argv[i][j]))
                    printf("%c", islower(argv[i][j] + 13) ? argv[i][j] + 13 : argv[i][j] - 13);
                else 
                    printf("%c", argv[i][j]);
            }
            printf("\n");
        }
        break;
    case 47:
        for (int i = 1; i < argc - 1; i++)
        {
            for (int j = 0; j < strlen(argv[i]);j++)
            {
                if(isgraph(argv[i][j]))
                    printf("%c", isgraph(argv[i][j] + 47) ? argv[i][j] + 47 : argv[i][j] - 47);
                else 
                    printf("%c", argv[i][j]);
            }
            printf("\n");
        }
        break;
    }
    return 0;
}
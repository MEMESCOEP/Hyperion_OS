/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just finds and replaces in the first string.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int offset = 0;
    char* haystack;
    if (strlen(argv[1]) == strlen(argv[2]))
    {
        if (strcmp(argv[1], argv[2]) == 0)
        {
            printf("%s\n", argv[1]);
        }
    }
    else if (strlen(argv[1]) < strlen(argv[2]))
    {
        printf("Second argument larger than first argument\n");
    }
    else 
    {
        haystack = argv[1];
        while (haystack = strstr(haystack + offset, argv[2]))
        {
            offset = strlen(argv[2]);
            for (int i = 0; i < (haystack - argv[1]);i++)
            {
                printf("%c", argv[1][i]);
            }
            printf("%s%s\n", argv[3], haystack + strlen(argv[2]));
        }
    }
    return 0;
}
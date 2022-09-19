/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just gets the number of occurrences of a string in whatever was passed into the program.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int count = 0;
    int offset = 0;
    char* haystack;
    if (strlen(argv[1]) == strlen(argv[2]))
    {
        if (strcmp(argv[1], argv[2]) == 0)
        {
            printf("Count: 1\n");
        }
        else 
        {
            printf("Count: 0\n");
        }
    }
    else if (strlen(argv[1]) < strlen(argv[2]))
    {
        printf("Count: 0\n");
    }
    else 
    {
        haystack = argv[1];
        while (haystack = strstr(haystack + offset, argv[2]))
        {
            count++;
            offset = strlen(argv[2]);
        }
        printf("Count: %d\n", count);
    }
    return 0;
}
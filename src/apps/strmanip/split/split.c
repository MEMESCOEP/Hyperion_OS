/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just splits the string passed in into n sized chunks.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int size = atoi(argv[argc - 1]);
    char* str = (char*) malloc(size + 1);
    for (int i = 1; i < argc - 1; i++)
    {
        int j;
        for (j = 0; j < strlen(argv[i]) - size; j+=size)
        {
            memcpy(str, argv[i] + j, size);
            strcat(str, "\0");
            printf("%s\n", str);
        }
        printf("%s\n", argv[i] + j);
    }
    free(str);
    return 0;
}
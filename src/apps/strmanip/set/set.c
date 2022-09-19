/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just finds and sets everything after n amounts of times in the first string (n being the number passed in).
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* save = argv[1];
    int offset = atoi(argv[3]);
    for(; argv[1] - save < offset; argv[1]++)
    {
        printf("%c", *argv[1]);
    }
    for (int i = 0;i < atoi(argv[4]); i++)
    {
        printf("%s", argv[2]);
    }
    printf("%s", argv[1] + offset);
    printf("\n");
    return 0;
}
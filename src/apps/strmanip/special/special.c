/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just sends a special message to whoever's name was passed in :)

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "Zain") == 0)
            printf("No Zain there are no turkish girls here please let me out of your basement.\n");
        else if (strcmp(argv[1], "yeabutactuallyno") == 0)
            printf("I want to die after doing this project\n");
        else if (strcmp(argv[1], "Khan") == 0)
            printf("No Khan none of us will be joining Cross Country, now please leave us alone\n");
        else if (strcmp(argv[1], "Asiful") == 0)
            printf("Ramadan is over so go right ahead\n");
        else if (strcmp(argv[1], "Kayden") == 0)
            printf("I get bitches. Source: trust me\n");
        else
            printf("Hope you have a nice day!!\n");
    }
    else 
        printf("Hope you have a nice day!!\n");

    return 0;
}


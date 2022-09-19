/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just gets the decimal value of whatever was passed into the program.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

const char* alpha_table[26] = {
    ".-",   
    "-...", 
    "-.-.", 
    "-..",  
    ".",    
    ".._.", 
    "--.",  
    "....", 
    "..",   
    ".---", 
    "-.-",  
    ".-..", 
    "--",   
    "-.",   
    "---",  
    ".--.", 
    "--.-", 
    ".-.",  
    "...",  
    "-",    
    "..-",  
    "...-", 
    ".--",  
    "-..-", 
    "-.--", 
    "--.."  
};
const char* digit_table[10] = {
    "-----",
    ".----",
    "..---",
    "...--",
    "....-",
    ".....",
    "-....",
    "--...",
    "---..",
    "----.",
};

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]);j++)
        {
            if(isdigit(argv[i][j]))
                printf("%s ", digit_table[atoi(argv[i][j])]);
            else if(isalpha(argv[i][j]))
                printf("%s ", alpha_table[toupper(argv[i][j]) - 65]);
            else 
                printf("/ ", argv[i][j]);
        }
        printf("\n");
    }
    return 0;
}
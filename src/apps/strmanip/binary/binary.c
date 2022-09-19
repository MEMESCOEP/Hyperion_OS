/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just gets the binary value of whatever was passed into the program.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strrev(char* str)
{
	char temp;
	int i, j, n;
	n = strlen(str);

	for (i = 0, j = n - 1; i < j; ++i, --j) {
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
	}
}

void itoa(int in, char* buffer, int base)
{
    int i = 0;
    if (in < 0)
    {
        in *= -1;
        do
        {
            if (in % base < 10)
                buffer[i++] = in % base + '0';
            else
                buffer[i++] = in % base + 'A' - 0xA;
            in /= base;
        } 
        while (in != 0);
        buffer[i++] = '-';
    }
    else
    {
        do
        {
            if (in % base < 10)
                buffer[i++] = in % base + '0';
            else
                buffer[i++] = in % base + 'A' - 0xA;
            in /= base;
        }
        while (in != 0);
    }
    buffer[i] = 0;
    strrev(buffer);
}

int main(int argc, char* argv[])
{
    char binary[9];
    char temp[9];
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]);j++)
        {
            itoa(argv[i][j], temp, 2);
            strncat(binary, "00000000", 8 - strlen(temp));
            strcat(binary, temp);
            printf("%s ", binary);
            temp[0] = '\0';
            binary[0] = '\0';
        }
        printf("\n");
    }
    return 0;
}
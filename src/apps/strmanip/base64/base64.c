/*
    Neptunium Operating System Application

    Author: xyve, yeabutactuallyno
    Developers: xyve
    Language: C
    Original Language: Java

    This program just gets the base 64 of whatever was passed into the program.
    I'm probably gonna merge this with the echo program, but who knows.

    This was originally written in Java by yeabutactuallyno, credit goes to him.
    He lost his mind while doing this :)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char base64_encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                       'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                       'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                       'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                       'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                       'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                       'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                       '4', '5', '6', '7', '8', '9', '+', '/'};

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
    for (int i = 1; i < argc; i++)
    {
        char* save = argv[i];
        char* binary = malloc((strlen(argv[i]) * 8) + 1);
        char itoaRet[9];
        char chunk[7];
        int n = strlen(save) * 8;
        int j;

        for (; *argv[i] != '\0'; argv[i]++)
        {
            itoa(*argv[i], itoaRet, 2);
            strncat(binary, "00000000", 8 - strlen(itoaRet));
            strcat(binary, itoaRet);
            itoaRet[0] = '\0';
        }
        binary[n] = '\0';
        switch (n % 3)
        {
        case 1:
            binary = realloc(binary, (n + 2));
            memset(binary + n, '0', 2);
            binary[n + 2] = '\0';
            break;
        case 2:
            binary = realloc(binary, (n + 4));
            memset(binary + n, '0', 4);
            binary[n + 4] = '\0';
            break;
        }
        for (j = 0; j < strlen(binary); j+=6)
        {
            strncpy(chunk, binary + j, 6);
            chunk[6] = '\0';
            printf("%c", base64_encoding_table[strtol(chunk, NULL, 2)]);
        }
        switch (n % 3)
        {
        case 1:
            printf("=");
            break;
        case 2:
            printf("==");
            break;
        }
        printf("\n");
        free(binary);
    }
    return 0;
}
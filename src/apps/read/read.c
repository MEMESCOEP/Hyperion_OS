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
void hex_handler(char* buffer)
{
    unsigned int location = 0;

    while(*buffer != '\0')
    {
        if(location % 8 == 0)
            printf("\n%08x:  ", location);

        printf("%02x ", *buffer);

        buffer++;
        location++;
    }
    printf("\n");
}
void ascii_handler(char* buffer)
{
    printf("%s\n", buffer);
}
void binary_handler(char* buffer)
{
    unsigned int location = 0;

    char binary[9];
    char temp[9];

    while(*buffer != '\0')
    {
        if(location % 8 == 0)
            printf("\n%08x:  ", location);

        itoa(*buffer, temp, 2);
        strncat(binary, "00000000", 8 - strlen(temp));
        strcat(binary, temp);
        printf("%s ", binary);
        temp[0] = '\0';
        binary[0] = '\0';

        buffer++;
        location++;
    }
    printf("\n");
}
int main(int argc, char* argv[])
{
    FILE* fp;
    char* buffer;
    long long size;
    int mode = 0;

    for(int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            i++;
            fp = fopen(argv[i], "rb");
            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            buffer = (char*)malloc(size + 1);

            fread(buffer, size, 1, fp);

            buffer[size] = 0;

            switch (argv[i - 1][1])
            {
            case 'a':
                ascii_handler(buffer);
                break;
            case 't':
                ascii_handler(buffer);
                break;
            case 'b':
                binary_handler(buffer);
                break;
            case 'h':
                hex_handler(buffer);
                break;
            case 'x':
                hex_handler(buffer);
                break;
            default:
                ascii_handler(buffer);
                break;
            }
        }
        else 
        {
            fp = fopen(argv[i], "rb");
            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            buffer = (char*)malloc(size + 1);

            fread(buffer, size, 1, fp);

            buffer[size] = 0;

            ascii_handler(buffer);
        }
    }

    free(buffer);
    fclose(fp);

    return 0;
}
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void set_echo(int fd) {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ECHO;
    tcsetattr(fd, TCSAFLUSH, &term);
}

void unset_echo(int fd) {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fd, TCSAFLUSH, &term);
}
int main(int argc, char *argv[])
{
    unset_echo(STDIN_FILENO);

    FILE* fp;
    fp = fopen(argv[1], "rb");
    fseek(fp, 0, SEEK_END);
    long long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(size + 1);

    fread(buffer, size, 1, fp);

    buffer[size] = 0;

    printf("%s\n", buffer);

    free(buffer);
    fclose(fp);

    int a;

    while (a = getchar())
    {
        switch (a)
        {
        case '\x1B':
            a = getchar();
            switch (a)
            {
            case 91:
                a = getchar();
                switch (a)
                {
                case 65:
                    printf("Up");
                    break;
                case 66:
                    printf("Down");
                    break;
                case 67:
                    printf("Right");
                    break;
                case 68:
                    printf("Left");
                    break;

                default:
                    break;
                }
                break;
            
            default:
                break;
            }
            break;
        
        default:
            break;
        }
    }
    
    return 0;
}

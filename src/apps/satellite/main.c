#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <utils/vec.h>

int main()
{
    printf("Welcome to Satellite\n");
    printf("Type 'help' for help\n");

    vec_str_t args;

    char * input = NULL;
    char * arg = NULL;

    size_t input_len;

    vec_init(&args);

    while (1)
    {
        char pwd[4096];
        getcwd(pwd, sizeof(pwd));


        printf("[\x1b[32m%s\x1b[0m]\n", pwd);
        printf("> ");

        getline(&input, &input_len, stdin);
        input[strlen(input) - 1] = '\0';

        for (size_t i = 0; i < strlen(input) + 1; i++)
        {
            if (input[i] == ' ' || input[i] == '\0')
            {
                char * str = malloc(strlen(arg) + 1);
                strcpy(str, arg);
                vec_push(&args, str);
                arg = NULL;
            }
            else if (input[i] == '\"')
            {
                i++;
                while (input[i] != '\"')
                {
                    size_t temp;
                    if(arg == NULL)
                        temp = 0;
                    else
                        strlen(arg);

                    arg = realloc(arg, temp + 2);
                    arg[temp++] = input[i];
                    arg[temp] = '\0';
                    i++;
                }
            }
            else
            {
                size_t temp;
                if(arg == NULL)
                    temp = 0;
                else
                    strlen(arg);

                arg = realloc(arg, temp + 2);
                arg[temp++] = input[i];
                arg[temp] = '\0';
            }
        }

        for (size_t i = 0; i < args.length; i++)
        {
            printf("[%lu] %s\n", i, args.data[i]);
        }
        


        free(input);
        free(arg);

        pid_t pid, wpid;
        int status;

        pid = fork();
        if (pid == 0) {
            // Child process
            if (execvp(args.data[0], args.data) == -1) {
                perror("satellite");
            }
            exit(EXIT_FAILURE);
        } 
        else if (pid < 0) {
            // Error forking
            perror("satellite");
        }
        else {
            // Parent process
            do 
            {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }


        vec_clear(&args);
    }
    
    vec_deinit(&args);
}
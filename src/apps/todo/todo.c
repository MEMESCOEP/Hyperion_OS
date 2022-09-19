#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* Declaring the variables for the input, token (the arguments passed in after separating), and the todo list */
    char* input;
    char* token;
    char* todo_file_line;
    char **todo = NULL;

    /* todo_size holds the size of the todo list, useful for resizing the list on the fly */
    size_t todo_size = 0;
    /* getline() needs this for some reason, basically pointless and doesn't get used other than the getline() function */
    size_t input_len = 0;
    size_t todo_file_input_len = 0;

    /* Reads in the todo.txt */
    FILE * todo_file_read_ptr;

    if (todo_file_read_ptr = fopen("todo.txt", "rb"))
    {
        while(getline(&todo_file_line, &todo_file_input_len, todo_file_read_ptr) != -1)
        {
            /* Increases the size of the todo array by one */
            todo_size++;
            /* Reallocates the memory for the list, now depending on the new size of the array */
            todo = realloc(todo, todo_size * sizeof(char*));
            /* Allocates memory to the last element of the todo array */
            todo[todo_size - 1] = malloc(strlen(todo_file_line));
            /* Copies the todo string passed, into the last element of the todo array*/
            strncpy(todo[todo_size - 1], todo_file_line, strlen(todo_file_line) - 1);
            todo[todo_size - 1][strlen(todo_file_line)] = '\0';
        }
        fclose(todo_file_read_ptr);
    }
    else 
    {
        FILE * todo_create;
        todo_create = fopen("todo.txt", "wb");
        fclose(todo_create);
    }

    /* Input prompt and getline getting in the input*/
    printf("> ");
    getline(&input, &input_len, stdin);
    /* This trims off the new line at the end of input, which getline() add for some reason, I have no idea why */
    input[strlen(input) - 1] = '\0';

    /* This keeps the program running until the user types in "done"  */
    while (strcmp(input, "done") != 0)
    {
        /* Checks if there is a space in the input, basically seeing if there are more than one arguments passed in */
        /* If there is a space, it will split it by the ' ' and save the token */
        if (strchr(input, ' ') != NULL)
            token = strtok(input, " ");
        else
            token = input;

        /* Checks for the add command */
        if (strcmp(token, "add") == 0)
        {
            /* Gets the rest of the string after 'add' */
            token = strtok(NULL, "\0");
            /* Increases the size of the todo array by one */
            todo_size++;
            /* Reallocates the memory for the list, now depending on the new size of the array */
            todo = realloc(todo, todo_size * sizeof(char*));
            /* Allocates memory to the last element of the todo array */
            todo[todo_size - 1] = malloc(strlen(token) + 1);
            /* Copies the todo string passed, into the last element of the todo array*/
            strcpy(todo[todo_size - 1], token);
        }
        /* Checks for the list command */
        else if (strcmp(token, "list") == 0)
        {
            /* Checks if the todo list is empty */
            if (todo_size != 0)
            {
                /* Prints out the index and the content of each todo array element */
                for (size_t todo_index = 0; todo_index < todo_size; todo_index++)
                    printf("[%d] : \"%s\"\n", todo_index, todo[todo_index]);
            }
            else 
            {
                printf("Nothing to do\n");
            }
        }
        /* Checks for remove */
        else if (strcmp(token, "remove") == 0)
        {
            /* Gets the rest of the string after 'remove' */
            token = strtok(NULL, "\0");
            /* Converts the parameter passed in into an integer */
            int remove_index = atoi(token);

            /* Checks if the index is a valid index */
            if (todo_size >= remove_index + 1)
            {
                /* Here is where shit starts to not make sense */
                /* rm_todo_index is the index we use to skip over element we wanna remove */
                /* cur_todo_index is used to go though the entire array normally */
                /* Basically, it copies the values to itself, but when it hits the index to remove, it increments rm_todo_index, skipping over it */
                size_t rm_todo_index = 0;
                size_t cur_todo_index = 0;
                /* Weird ass for loop */
                for (rm_todo_index, cur_todo_index; rm_todo_index < todo_size; cur_todo_index++, rm_todo_index++)
                {
                    if (rm_todo_index == remove_index)
                        rm_todo_index++;
                    todo[cur_todo_index] = todo[rm_todo_index];
                }
                /* Decreases the size of the todo list */
                todo_size--;
                /* Reallocated the size of todo, one less than it was, basically shrinking it */
                todo = realloc(todo, todo_size * sizeof(char*));
            }
            else 
            {
                printf("Index doesn't exist: %d\n", remove_index);
            }
            
        }
        /* Checks for clear */
        else if (strcmp(token, "clear") == 0)
        {

            /* Checks if the array is empty */
            if (todo_size > 0)
            {
                /* Reallocated the size of todo, basically 0, basically shrinking it */
                /* Frees all of the allocated memory, first going through each element of the todo array and freeing the memory */
                for (size_t todo_index = 0; todo_index < todo_size; todo_index++)
                {
                    free(todo[todo_index]);
                }
                /* Sets the size to zero */
                todo_size = 0;
            }
            else 
            {
                printf("Nothing to do, so nothing to clear\n");
            }
            
        }
        /* Unknown command handler, kinda works kinda doesn't */
        else 
        {
            printf("Unknown command\n");
        }

        /* Another input prompt, same as the one before, this time it traps the user in, input trap loop or whatever */
        printf("> ");
        getline(&input, &input_len, stdin);
        input[strlen(input) - 1] = '\0';
    }

    /* Writes in the todo.txt */
    FILE * todo_file_write_ptr;
    todo_file_write_ptr = fopen("todo.txt", "wb");

    /* Frees all of the allocated memory, first going through each element of the todo array and freeing the memory */
    for (size_t todo_index = 0; todo_index < todo_size; todo_index++)
    {
        /* Writes the todo list entries to the todo.txt file */
        fprintf(todo_file_write_ptr, "%s\n", todo[todo_index]);
        free(todo[todo_index]);
    }
    /* Finally, frees the memory for the array */
    fclose(todo_file_write_ptr);
    free(todo);

    return 0;
}
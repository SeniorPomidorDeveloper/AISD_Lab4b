#include "import.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../error_codes.h"

int import_tree(Node_Tree **tree, const char *path_file)
{
    FILE *file = fopen(path_file, "r");
    if (file == NULL) return ERROR_FILE_OPEN;
    if (init_Tree(tree) == ERROR_ALLOCATION)
    {
        fclose(file);
        return ERROR_ALLOCATION;
    }
    size_t len;
    int result = fscanf(file, "%zu", &len);
    if (result == EOF)
    {
        free_Tree(*tree);
        fclose(file);
        return EOF;
    }
    else if (result == 0)
    {
        free_Tree(*tree);
        fclose(file);
        return ERROR_FILE_READ;
    }
    char *str;
    for (size_t i = 0; i < len; ++i)
    {
        char symbol;
        do 
        {
            symbol = fgetc(file);
        } while (symbol != 10 && symbol != EOF);
        size_t BUF = 10;
        size_t str_len = 0;
        str = (char *) malloc((BUF + 1) * sizeof(char));
        if (str == NULL)
        {
            free_Tree(*tree);
            fclose(file);
            printf("1\n");
            return ERROR_ALLOCATION;
        }
        do 
        {
            symbol = fgetc(file);
            if (symbol != 10 && symbol != EOF && symbol != 13) 
            {
                str[str_len] = symbol;
                str_len++;
            } 
            if (str_len % BUF == 0 && str_len != 0) str = (char *) realloc(str, (str_len + BUF + 1) * sizeof(char));
            if (str == NULL)
            {
                free_Tree(*tree);
                fclose(file);
                return ERROR_ALLOCATION;
            }
        } while (symbol != 10 && symbol != EOF);
        str[str_len] = '\0';
        str = (char *) realloc(str, (str_len + 1) * sizeof(char));
        if (str == NULL)
        {
            free_Tree(*tree);
            fclose(file);
            printf("2");
            return ERROR_ALLOCATION;
        }
        ULLI info;
        result = fscanf(file, "%llu", &info);
        if (result == EOF)
        {
            printf("3");
            free_Tree(*tree);
            fclose(file);
            return EOF;
        } 
        else if (result == 0)
        {
            printf("4");
            fclose(file);
            return WARNING_FILE_READ;
        } 
        if (add_Tree(tree, str, info, NULL) == ERROR_ALLOCATION)
        {
            printf("5");
            free(str);
            free_Tree(*tree);
            fclose(file);
            return ERROR_ALLOCATION;
        }
        free(str);
    }
    fclose(file);
    return SUCCESS;
}
#include "input.h"

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../error_codes.h"

int input(char **line, const char *message)
{
    char symbol;
    printf("%s", message);
    size_t buf_len = 10;
    *line = (char *) malloc(buf_len * sizeof(char));
    if (*line == NULL)
    {
        return ERROR_ALLOCATION;
    }
    *line[0] = 0;
    do
    {
        symbol = fgetc(stdin);
        if (symbol == EOF)
        {
            free(*line);
        }
        if (symbol != '\n')
        {
            size_t len = strlen(*line);
            (*line)[len] = symbol;
            (*line)[len + 1] = 0;
        }
        if ((strlen(*line) + 1) % buf_len == 0)
        {
            *line = (char *) realloc(*line, (strlen(*line) + buf_len + 1) * sizeof(char));
            if (*line == NULL)
            {
                return ERROR_ALLOCATION;
            }
        }
    } while (symbol != '\n');
    *line = (char *) realloc(*line, (strlen(*line) + 1) * sizeof(char));
    if (*line == NULL)
    {
        return ERROR_ALLOCATION;
    }
    return SUCCESS;
}
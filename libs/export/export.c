#include "export.h"

#include <stdio.h>
#include <stdlib.h>

int rec_export(const Node_Tree *tree, FILE *file)
{
    if (fprintf(file, "\t%s [label = \"<f0> %s", tree->keys[0], tree->keys[0]) < 18)
    {
        return ERROR_FILE_WRITE;
    }
    for (size_t i = 1; i < 3 && tree->keys[i] != NULL; i++)
    {
        if (fprintf(file, " | <f%zu> %s", i, tree->keys[i]) < 9)
        {
            return ERROR_FILE_WRITE;
        }
    }
    if (fprintf(file, "\"];\n") < 3)
    {
        return ERROR_FILE_WRITE;
    }
    if (tree->childs[0] == NULL)
    {
        return SUCCESS;
    }
    for (size_t i = 0; i < 4 && tree->childs[i] != NULL; ++i)
    {
        if (rec_export(tree->childs[i], file) == ERROR_FILE_WRITE)
        {
            return ERROR_FILE_WRITE;
        }
    }
    for (size_t i = 0; i < 4 && tree->childs[i] != NULL; ++i)
    {
        if (fprintf(file, "\t%s -> %s;\n", tree->keys[0], tree->childs[i]->keys[0]) < 8)
        {
            return ERROR_FILE_WRITE;
        }
    }
    return SUCCESS;
}

int export_graph(const Node_Tree *tree, const char *path)
{
    FILE *file = fopen(path, "w+");
    if (file == NULL)
    {
        return ERROR_FILE_OPEN;
    }
    if (fprintf(file, "digraph Graph {\n\tnode [shape = record];\n") < 37)
    {
        fclose(file);
        return ERROR_FILE_WRITE;
    }
    if (rec_export(tree, file) == ERROR_FILE_WRITE)
    {
        fclose(file);
        return ERROR_FILE_WRITE;
    }
    if (fprintf(file, "}\n") < 2)
    {
        fclose(file);
        return ERROR_FILE_WRITE;
    }
    fclose(file);
    return SUCCESS;
}
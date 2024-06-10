#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "./libs/tree/tree.h"

int key_generator(char **key)
{
    /* A < symbol < п */
    *key = (char *) malloc(sizeof(char) * 11);
    if (*key == NULL) return ERROR_ALLOCATION;
    for (size_t i = 0; i < 10; i++)
    {
        (*key)[i] = 'A' + rand() % 'z';
    }
    (*key)[10] = '\0';
    return SUCCESS;
}

int timing(const size_t step, const size_t num)
{
    Node_Tree *tree;
    int result = init_Tree(&tree);
    if (result != SUCCESS) return result;
    srand(time(NULL));
    char *keys[step];
    for (size_t i = 0; i < num; i++) {
        for (size_t j = 0; j < step; j++) 
        {
            if (key_generator(keys + j) == ERROR_ALLOCATION) return ERROR_ALLOCATION;
        }
        for (size_t j = 0; j < 1000000;)
        {
            char *key;
            if (key_generator(&key) == ERROR_ALLOCATION) return ERROR_ALLOCATION; 
            result = add_Tree(&tree, key, 1, NULL);
            if (result == ERROR_ALLOCATION)
            {
                free_Tree(tree);
                return ERROR_ALLOCATION;
            }
            else if (result == SUCCESS) j++;
        }
        size_t count_finds = 0;
        clock_t first_time = clock();
        for (size_t j = 0; j < step; ++j)
        {
            if (find_Tree(tree, keys[j], NULL, NULL) != NULL) count_finds++;
        }
        clock_t second_time = clock();
        printf("Было найдено %zu эллементов.\n", count_finds);
        printf("Тест №%zu: Колличество узлов - %zu; Время - %ld\n", i + 1, (i + 1) * 1000000, (second_time - first_time) / 1000);
    }
    free_Tree(tree);
    return SUCCESS;
}

int main()
{
    return timing(10000, 15);
}
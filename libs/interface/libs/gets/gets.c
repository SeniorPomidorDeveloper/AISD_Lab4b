#include "gets.h"

#include "stdio.h"

bool check_positive(long long int num)
{
    return num > 0;
}

bool check_no_negative(long long int num)
{
    return num >= 0;
}

bool StandatrCheckSize_t(size_t num)
{
    return num || 1;
}

bool StandartCheckLLInt(long long int num) 
{
    return num || 1;
}

int GetSize_t(size_t *num, const char *message, bool (*CheckFunction)(const size_t))
{
    int result;
    int point = 0;
    do {
        printf("%s", message); 
        result = scanf("%zu.%d", num, &point);
        if (result == 1 && point == 0) {
            if (!CheckFunction(*num)) {
                printf("[WARNING] Значение было введено не правильно!\n");
                printf("Попробуйте ещё.\n");
                result = 0;
                scanf("%*[^\n]");
            }
        } else if (result == 0 || result == 2 || point != 0) {
            printf("[WARNING] Значение было введено не правильно!\n");
            printf("Попробуйте ещё.\n");
            result = 0;
            point = 0;
            scanf("%*[^\n]");
        }
    } while(result == 0);
    return result;
}

int GetLLInt(long long int *num, const char *message, bool (*CheckFunction)(long long int num))
{
    int result;
    int point = 0;
    do {
        printf("%s", message); 
        result = scanf("%lld.%d", num, &point);
        if (result == 1 && point == 0) {
            if (!CheckFunction(*num)) {
                printf("[WARNING] Значение было введено не правильно!\n");
                printf("Попробуйте ещё.\n");
                result = 0;
                scanf("%*[^\n]");
            }
        } else if (result == 0 || result == 2 || point != 0) {
            printf("[WARNING] Значение было введено не правильно!\n");
            printf("Попробуйте ещё.\n");
            result = 0;
            point = 0;
            scanf("%*[^\n]");
        }
    } while(result == 0);
    return result;
}
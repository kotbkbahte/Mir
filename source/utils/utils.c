#include "utils.h"

int choice_i_arr(int c, int* arr)
{
    return (arr[rand() % c]);
}

// x in [lower, upper)
int random_range(int lower, int upper)
{
    if(upper - lower == 0)
        h_error_msg("random range equals 0\n", DEFAULT_ERROR);
    return (rand() % (upper - lower)) + lower;
}


void print_int32(char* var, int a)
{
    long long i, j;
    printf("%s: ", var);
    for (i = 0; i < sizeof(int); i++)
    {
        char byte = *( ((char*)&a) + i );
        for (j = 8; j >= 0; j--)
        {
            char bit = (byte >> j) & 1;
            printf("%hhd", bit);
        }
        printf(" ");
    }
    printf("\n");
}

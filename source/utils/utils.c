#include "utils.h"

int choice_i_arr(int c, int* arr)
{
    return (arr[rand() % c]);
}

// x in [lower, upper)
int random_range(int lower, int upper)
{
     return (rand() % (upper - lower)) + lower;
}

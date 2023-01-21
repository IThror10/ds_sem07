#include <stdio.h>

#define IMPORT
#include "sum_lib.hpp"

int main()
{
    int a = 5, b = 7;
    printf("%d + %d = %d\n", a, b, lib_sum(a, b));
    return 0;
}
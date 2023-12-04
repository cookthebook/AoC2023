#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cookstr.h"

char *
cookstr_itos(int val)
{
    char *ret;
    int retlen;

    retlen = snprintf(NULL, 0, "%d", val);
    ret = malloc(retlen + 1);
    sprintf(ret, "%d", val);

    return ret;
}

char *
cookstr_ulltos(unsigned long long val)
{
    char *ret;
    int retlen;

    retlen = snprintf(NULL, 0, "%llu", val);
    ret = malloc(retlen + 1);
    sprintf(ret, "%llu", val);

    return ret;
}


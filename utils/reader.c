#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *
readline(FILE *fd)
{
    char *ret = calloc(1, 1);
    size_t retlen = 0;

    do {
        char tmp[1024];
        size_t tmplen;

        if (fgets(tmp, 1024, fd) == NULL) {
            break;
        }

        tmplen = strlen(tmp);
        if (tmplen == 0) {
            break;
        }

        ret = realloc(ret, retlen + tmplen + 1);
        memcpy(&ret[retlen], tmp, tmplen + 1);
        retlen += tmplen;
    } while(ret[retlen - 1] != '\n');

    if (retlen == 0) {
        return NULL;
    }

    return ret;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "all_days.h"

int main(int argc, char **argv)
{
    int day;
    FILE *fd;
    int is_star = 0;
    char *result;

    if (argc < 3) {
        printf(
            "Usage: aoc <day #> <input file> [<s>]\n"
            "    s - Is start\n"
        );
        return 0;
    }

    day = atoi(argv[1]);
    fd = fopen(argv[2], "r");
    if (!fd) {
        printf("File open error\n");
        return -1;
    }

    if (argc >= 4 && !strcmp(argv[3], "s")) {
        is_star = 1;
    }

    switch (day) {
    case 1:
        if (is_star) {
            result = day_01_star(fd);
        } else {
            result = day_01(fd);
        }
        break;
    default:
        result = strdup("Unknown");
        break;
    }

    printf(
        "Day %d (%s) Result:\n%s\n",
        day, is_star ? "Star" : "Not Star", result
    );
    free(result);
}

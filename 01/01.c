#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "01.h"
#include "reader.h"

static int line_to_number(const char *line);
static int line_to_number_text(const char *line);

typedef struct word_match_struct {
    const char *match;
    size_t match_len;
    int val;
} word_match_t;

word_match_t matches[] = {
    { "one", 3 },
    { "two", 3 },
    { "three", 5 },
    { "four", 4 },
    { "five", 4 },
    { "six", 3 },
    { "seven", 5 },
    { "eight", 5 },
    { "nine", 4 }
};

char *
day_01(FILE *fd)
{
    int sum = 0;
    char *line;
    char *ret;
    int retlen;

    while ((line = readline(fd)) != NULL) {
        int val = line_to_number(line);
        sum += val;
        printf("%d\n", val);
        free(line);
    }

    retlen = snprintf(NULL, 0, "%d", sum);
    ret = calloc(1, retlen + 1);
    sprintf(ret, "%d", sum);

    return ret;
}

char *
day_01_star(FILE *fd)
{
    int sum = 0;
    char *line;
    char *ret;
    int retlen;

    while ((line = readline(fd)) != NULL) {
        int val = line_to_number_text(line);
        sum += val;
        printf("%d\n", val);
        free(line);
    }

    retlen = snprintf(NULL, 0, "%d", sum);
    ret = calloc(1, retlen + 1);
    sprintf(ret, "%d", sum);

    return ret;
}

static int
line_to_number(const char *line)
{
    char tmp[3];
    size_t linelen = strlen(line);

    tmp[0] = '0';
    tmp[1] = '0';
    tmp[3] = '\0';

    for (size_t i = 0; i < linelen; i++) {
        if ((line[i] >= '0') && (line[i] <= '9')) {
            tmp[0] = line[i];
            break;
        }
    }

    for (size_t i = linelen - 1; i >= 0; i--) {
        if ((line[i] >= '0') && (line[i] <= '9')) {
            tmp[1] = line[i];
            break;
        }
    }

    return atoi(tmp);
}


static int
word_to_int(const char *word, size_t len)
{
    for (int i = 0; i < (sizeof(matches)/sizeof(word_match_t)); i++) {
        word_match_t *match = &matches[i];
        if (
            (len >= match->match_len) &&
            !memcmp(word, match->match, match->match_len)
        ) {
            return (i + 1);
        }
    }

    return -1;
}

static int
line_to_number_text(const char *line)
{
    char tmp[3];
    size_t linelen = strlen(line);

    tmp[0] = '0';
    tmp[1] = '0';
    tmp[3] = '\0';

    for (size_t i = 0; i < linelen; i++) {
        if ((line[i] >= '0') && (line[i] <= '9')) {
            tmp[0] = line[i];
            break;
        }

        int val = word_to_int(&line[i], linelen - i);
        if (val >= 0) {
            tmp[0] = val + '0';
            break;
        }
    }

    for (size_t i = linelen - 1; i >= 0; i--) {
        if ((line[i] >= '0') && (line[i] <= '9')) {
            tmp[1] = line[i];
            break;
        }

        int val = word_to_int(&line[i], linelen - i);
        if (val >= 0) {
            tmp[1] = val + '0';
            break;
        }
    }

    return atoi(tmp);
}

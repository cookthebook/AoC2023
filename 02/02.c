#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "02.h"
#include "reader.h"
#include "cookstr.h"

typedef struct triplet_struct {
    int red;
    int green;
    int blue;
} triplet_t;

typedef struct game_struct {
    triplet_t *hands;
    int hands_n;
} game_t;

static int game_makes_sense(const game_t *game, const triplet_t *bag);
static game_t *line_to_game(const char *line);
static void free_game(game_t *game);

char *
day_02(FILE *fd)
{
    triplet_t bag = {
        .red = 12,
        .green = 13,
        .blue = 14
    };
    char *line;
    int ctr = 1;
    int ret = 0;

    while ((line = readline(fd)) != NULL) {
        game_t *game = line_to_game(line);
        free(line);

        if (!game) {
            break;
        }

        if (game_makes_sense(game, &bag)) {
            ret += ctr;
            printf("Good game %d\n", ctr);
        }

        ctr++;
        free_game(game);
    }

    return cookstr_itos(ret);
}

char *
day_02_star(FILE *fd)
{
    unsigned long long ret = 0;
    char *line;

    while ((line = readline(fd)) != NULL) {
        triplet_t max = { 0 };
        game_t *game = line_to_game(line);
        free(line);

        if (!game) {
            break;
        }

        for (int i = 0; i < game->hands_n; i++) {
            triplet_t *hand = &game->hands[i];

            if (hand->red > max.red) {
                max.red = hand->red;
            }
            if (hand->green > max.green) {
                max.green = hand->green;
            }
            if (hand->blue > max.blue) {
                max.blue = hand->blue;
            }
        }

        unsigned long long pow = max.red * max.green * max.blue;
        ret += pow;
        free_game(game);
    }

    return cookstr_ulltos(ret);
}

static int
game_makes_sense(const game_t *game, const triplet_t *bag)
{
    for (int i = 0; i < game->hands_n; i++) {
        triplet_t *hand = &game->hands[i];
        if (
            (bag->red < hand->red) ||
            (bag->green < hand->green) ||
            (bag->blue < hand->blue)
        ) {
            return 0;
        }
    }

    return 1;
}

static game_t *
line_to_game(const char *line)
{
    /* Game <num>: <num> <color>, <num> <color>; <num> <color>, ... */
    char *line_cpy = strdup(line);
    char *p = line_cpy;
    game_t *ret = NULL;

    /* scan to : */
    while ((*p) != ':') {
        if ((*p) == '\0') {
            goto parse_error;
        }
        p++;
    }

    ret = malloc(sizeof(game_t));
    ret->hands = calloc(1, sizeof(triplet_t));
    ret->hands_n = 1;

    while (1) {
        /* parse any number of "<num> <color>," or "<num> <color>;" */
        int val;
        char *val_str;
        triplet_t *hand = &ret->hands[ret->hands_n - 1];

        p++;
        /* " <num>" */
        if ((*p) != ' ') {
            goto parse_error;
        }
        p++;
        val_str = p;
        while ((*p) >= '0' && (*p) <= '9') {
            p++;
        }
        if ((*p) != ' ') {
            goto parse_error;
        }
        (*p) = '\0';
        val = atoi(val_str);
        (*p) = ' ';

        /* " <color>"*/
        p++;
        if (!memcmp(p, "red", 3)) {
            hand->red = val;
            p += 3;
        }
        else if (!memcmp(p, "green", 5)) {
            hand->green = val;
            p += 5;
        }
        else if (!memcmp(p, "blue", 4)) {
            hand->blue = val;
            p += 4;
        }
        else {
            goto parse_error;
        }

        /* do nothing */
        if ((*p) == ',') {
        }
        /* new triplet */
        else if ((*p) == ';') {
            ret->hands_n++;
            ret->hands = realloc(ret->hands, sizeof(triplet_t) * ret->hands_n);
            memset(&ret->hands[ret->hands_n - 1], 0, sizeof(triplet_t));
        }
        /* EOF or line */
        else if (
            ((*p) == '\0') ||
            ((*p) == '\r') ||
            ((*p) == '\n')
        ) {
            break;
        } else {
            goto parse_error;
        }
    };

    return ret;

parse_error:
    free(line_cpy);
    free_game(ret);
    return NULL;
}

static void
free_game(game_t *game)
{
    if (game) {
        if (game->hands) {
            free(game->hands);
        }
        free(game);
    }
}

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "tle.h"

static tle_data *new_tle_data() {
    tle_data *data = calloc(1, sizeof(*data));
    return data;
}

/**
 * Designed to parse space-track.org title lines, they are
 * prefixed with "0 " so the max len would be 26 and not 24
 *
 * @param data the data to fill
 * @param title the title line
 * @return 0 if invalid length
 */
static int parse_title(tle_data *data, char *title) {
    size_t len = strlen(title);
    if (len > 26) {
        return 0;
    }

    /* Remove the "0 " and the newline */
    len -= 3;
    data->title_len = (unsigned char) len;

    char *temp = malloc(len);
    memcpy(temp, title + 2, len);
    data->title = temp;

    return 1;
}

static int parse_line1(tle_data *data, char *line1) {
    return 1;
}

static int parse_line2(tle_data *data, char *line2) {
    return 1;
}

tle_data *tle_parse(char *title, char *line1, char *line2) {
    tle_data *data = new_tle_data();
    if (parse_title(data, title) == 0) {
        return NULL;
    }

    if (parse_line1(data, line1) == 0) {
        return NULL;
    }

    if (parse_line2(data, line2) == 0) {
        return NULL;
    }

    return data;
}

void tle_free(tle_data *data) {
    free(data->title);
    free(data->launch_piece);
    free(data);
}
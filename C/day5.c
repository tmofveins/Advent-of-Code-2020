#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#define FRONT 'F'
#define BACK 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define ROW_MIN 1
#define ROW_MAX 128
#define SEAT_MIN 1
#define SEAT_MAX 8
#define ROW_CHARS 7
#define SEAT_CHARS 3

enum mode { ROW, SEAT };

int get_npasses(FILE* input) {
    char line[ROW_CHARS + SEAT_CHARS + 2];
    int npasses = 0;

    while(fgets(line, sizeof(line), input)) {
        npasses += 1;
    }

    return npasses;
}

void fill_passes(FILE* input, char** passes, int npasses) {
    char line[ROW_CHARS + SEAT_CHARS + 2];
    int i = 0;

    while (fgets(line, sizeof(line), input)) {
        strcat(passes[i], line);
        i += 1;
    }
}

int find_seat_or_row(char* instructions, enum mode mode) {
    if (mode == ROW) {
        double upper = ROW_MAX;
        double lower = ROW_MIN;
        int i = 0;

        while (i < strlen(instructions)) {

            if (instructions[i] == FRONT) {
                upper = floor(upper - ((upper - lower) / 2));
            } else if (instructions[i] == BACK) {
                lower = ceil(lower + ((upper - lower) / 2));
            }

            i += 1;
        }

        return lower - 1;

    } else if (mode == SEAT) {
        double upper = SEAT_MAX;
        double lower = SEAT_MIN;
        int i = 0;

        while (i < strlen(instructions)) {

            if (instructions[i] == LEFT) {
                upper = floor(upper - ((upper - lower) / 2));
            } else if (instructions[i] == RIGHT) {
                lower = ceil(lower + ((upper - lower) / 2));
            }

            i += 1;
        }

        return upper - 1;
    }

    return 0;
}

int highest_seatid_part1(char** passes, int npasses, int* seat_ids) {
    int max = INT_MIN;

    for (int i = 0; i < npasses; i++) {
        char* row = (char*)malloc(sizeof(char) * ROW_CHARS + 1);
        row = strncpy(row, passes[i], ROW_CHARS);
        row[ROW_CHARS] = '\0';

        char* seat = (char*)malloc(sizeof(char) * SEAT_CHARS + 1);
        seat = strncpy(seat, &passes[i][ROW_CHARS], SEAT_CHARS);
        seat[SEAT_CHARS] = '\0';

        int row_num = find_seat_or_row(row, ROW);
        int seat_num = find_seat_or_row(seat, SEAT);

        int seat_id = row_num * 8 + seat_num;

        seat_ids[i] = seat_id;

        if (seat_id >= max) max = seat_id;
    }

    return max;
}

int cmpfunc (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

int find_seatid_part2(int* seat_ids, int npasses) {
    qsort(seat_ids, npasses, sizeof(int), cmpfunc);

    for (int i = 0; i < npasses - 1; i++) {
        if (seat_ids[i] != (seat_ids[i + 1] - 1)) return seat_ids[i] + 1;
    }

    return 0;
}

int main() {
    FILE* input = fopen("day5-input.txt", "r");
    assert(input);

    int npasses = get_npasses(input);
    printf("No. of passes: %d\n", npasses);

    fseek(input, 0, SEEK_SET);

    char** passes = (char**)malloc(sizeof(char*) * npasses);
    for (int i = 0; i < npasses; i++) {
        passes[i] = (char*)malloc(sizeof(char) * (ROW_CHARS + SEAT_CHARS + 2));
        passes[i][0] = '\0';
    }
    assert(passes);

    int* seat_ids = (int*)malloc(sizeof(int) * npasses);
    assert(seat_ids);

    fill_passes(input, passes, npasses);

    int result_part1 = highest_seatid_part1(passes, npasses, seat_ids);
    printf("Highest seat ID (Part 1): %d\n", result_part1);

    int result_part2 = find_seatid_part2(seat_ids, npasses);
    printf("My seat ID (Part 2): %d\n", result_part2);

    fclose(input);

    for (int i = 0; i < npasses; i++) free(passes[i]);
    free(passes);

    return 0;
}
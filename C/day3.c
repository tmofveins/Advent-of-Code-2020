#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HEIGHT 323
#define WIDTH 31
#define TREE '#'

void print_map(char map[][WIDTH + 1]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH + 1; j++) {
            printf("%c", map[i][j]);
        }
    }
}

int traverse_and_count(char map[][WIDTH + 1], int right_move, int down_move) {
    int tree_count = 0;
    int x_pos = 0;
    int y_pos = 0;

    while (y_pos <= HEIGHT) {
        x_pos += right_move;
        if (x_pos >= WIDTH) x_pos = x_pos % WIDTH;
        y_pos += down_move;
        
        if (map[y_pos][x_pos] == TREE) tree_count += 1;
    }

    return tree_count;
}

int main() {
    FILE* input = fopen("day3-input.txt", "r");

    char map[HEIGHT][WIDTH + 1];

    fread(map, 1, sizeof(map), input);

    int result_part1 = traverse_and_count(map, 3, 1);
    printf("Number of trees encountered (Part 1): %d\n", result_part1);

    int traverse1 = traverse_and_count(map, 1, 1);
    int traverse2 = traverse_and_count(map, 5, 1);
    int traverse3 = traverse_and_count(map, 7, 1);
    int traverse4 = traverse_and_count(map, 1, 2);

    unsigned long result_part2 = 0;
    result_part2 = result_part1 * traverse1 * traverse2 * traverse3 * traverse4;
    printf("Multiple of trees encountered in above traversals (Part 2): %lu", result_part2);

    fclose(input);

    return 0;
}
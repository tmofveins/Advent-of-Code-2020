#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TABLE_SIZE 2021
#define TARGET_SUM 2020

void fill_table(int* arr, FILE* input) {
    char line[256];

    while (fgets(line, sizeof(line), input)) {
        int val = atoi(line);
        arr[val] = val;
    }

}

int find_result_part1(int* arr) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        int val = arr[i];
        if (arr[TARGET_SUM - val] != 0) return val * arr[TARGET_SUM - val];
    }

    return 0;
}

int find_result_part2(int* arr) {
    for (int i = 0; i < TABLE_SIZE - 2; i++) {
        if (arr[i] != 0) {
            int val1 = arr[i];
            int new_target = TARGET_SUM - val1;

            for (int j = i + 1; j < new_target; j ++) {
                if (arr[j] != 0) {
                    int val2 = arr[j];
                    int final_val = new_target - val2;

                    if (arr[final_val] != 0) {
                        return arr[final_val] * val1 * val2;
                    }
                }
            }
        }
    }

    return 0;
}

int main() {
    FILE *input = fopen("day1-input.txt", "r");
    assert(input);

    int* arr = (int*) malloc(sizeof(int) * TABLE_SIZE);
    assert(arr);

    for(int i = 0; i < TABLE_SIZE; i++) arr[i] = 0;

    fill_table(arr, input);

    int result = find_result_part1(arr);
    printf("Part 1 answer: %d\n", result);

    int result2 = find_result_part2(arr);
    printf("Part 2 answer: %d\n", result2);

    fclose(input);
    free(arr);

    return 0;
}
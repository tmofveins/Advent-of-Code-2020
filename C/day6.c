#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SPACE ' '
#define NEWLINE '\n'
#define N_ALPHABETS 26

int get_ngroups(FILE* input) {
    char line[256];
    int ngroups = 0;

    while(fgets(line, sizeof(line), input)) {
        if (strcmp(line, "\n") == 0) ngroups += 1;
    }

    ngroups += 1;

    return ngroups;
}

void fill_groups(FILE* input, char** groups) {
    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), input)) {
        if (strcmp(line, "\n") != 0) {
            strcat(groups[i], line);
        } else{
            i++;
        }
    }
}

void remove_newlines_and_delims(char* group) {
    int length = strlen(group);

    char* separated_data = (char*)malloc(sizeof(char) * length + 2);

    for (int i = 0; i < length; i++) {
        if (group[i] == SPACE || group[i] == NEWLINE) {
            separated_data[i] = ' ';
        } else {
            separated_data[i] = group[i];
        }
    }
    separated_data[length] = '\0';
    
    strcpy(group, separated_data);
}

int count_unique_answers(char* group) {
    int* track_letters = (int*)calloc(N_ALPHABETS, sizeof(int));
    assert(track_letters);

    int count = 0;

    for (int i = 0; i < strlen(group); i++) {
        int num = group[i] - 'a';
        track_letters[num] = 1;
    }

    for (int i = 0; i < N_ALPHABETS; i++) {
        if (track_letters[i] == 1) count += 1;
    }

    free(track_letters);

    return count;
}

int get_result_part1(char** group, int ngroups) {
    int result = 0;

    for (int i = 0; i < ngroups; i++) {
        remove_newlines_and_delims(group[i]);
        result += count_unique_answers(group[i]);
    }

    return result;
}

int count_people(char* group) {
    int people = 0;
    char* token = strtok(group, " ");
    
    while (token) {
        people += 1;
        token = strtok(NULL, " ");
    }

    return people;
}

int count_common_answers(char* group) {
    char* cpy = (char*)malloc(sizeof(char) * strlen(group) + 2);
    cpy = strcpy(cpy, group); 

    int npeople = count_people(cpy);    
    free(cpy);

    int** track = (int**)malloc(sizeof(int*) * npeople);
    assert(track);

    int count = 0;
    int i = 0;

    char* token = strtok(group, " ");

    while (token) {
        int* track_letters = (int*)calloc(N_ALPHABETS, sizeof(int));
        assert(track_letters);

        for (int j = 0; j < strlen(token); j++) {
            int num = token[j] - 'a';
            track_letters[num] = 1;
        }

        track[i] = track_letters;
        i += 1;

        token = strtok(NULL, " ");
    }

    for (int i = 0; i < N_ALPHABETS; i++) {
        int common = 1;

        for (int j = 0; j < npeople; j++) {
            if (track[j][i] == 0) common = 0;
        }

        if (common) {
            count += 1; 
        }
    }

    for (int i = 0; i < npeople; i++) free(track[i]);
    free(track);
    
    return count;
}

int get_result_part2(char** groups, int ngroups) {
    int result = 0;

    for (int i = 0; i < ngroups; i++) {
        remove_newlines_and_delims(groups[i]);
        int count = count_common_answers(groups[i]);
        result += count;
    }

    return result;
}

void print_groups(char** groups, int ngroups) {
    for (int i = 0; i < ngroups; i++) printf("%s\n", groups[i]);
}

int main() {
    FILE* input = fopen("day6-input.txt", "r");
    assert(input);
    
    int ngroups = get_ngroups(input);
    
    fseek(input, 0, SEEK_SET);

    char** groups = (char**)malloc(sizeof(char*) * ngroups);
    for (int i = 0; i < ngroups; i++) {
        groups[i] = (char*) malloc(sizeof(char) * 256);
        groups[i][0] = '\0';
    }
    assert(groups);

    fill_groups(input, groups);

    int result_part1 = get_result_part1(groups, ngroups);
    printf("Sum of unique answers to questions (Part 1): %d\n", result_part1);

    int result_part2 = get_result_part2(groups, ngroups);
    printf("Sum of unique answers to questions (Part 2): %d\n", result_part2);

    fclose(input);

    for (int i = 0; i < ngroups; i++) free(groups[i]);
    free(groups);

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PASSWORD_DELIM ":"
#define RULE_DELIM "-"
#define DELIM " "

typedef struct {
    int lower_bound;
    int upper_bound;
    char letter[2];
    char password[256];
} password_t;

int count_passwords(FILE* file) {
    int npasswords = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') npasswords += 1;
    }
    
    npasswords += 1;

    return npasswords;
}

void fill_passwords(FILE* file, password_t passwords[]) {
    char line[256];
    char* token;
    int i = 0;

    while(fgets(line, sizeof(line), file)) {
        token = strtok(line, RULE_DELIM);
        passwords[i].lower_bound = atoi(token);

        token = strtok(NULL, DELIM);
        passwords[i].upper_bound = atoi(token);

        token = strtok(NULL, PASSWORD_DELIM);
        strcpy(passwords[i].letter, token);

        token = strtok(NULL, DELIM);
        strcpy(passwords[i].password, token);

        i += 1;
    }
}

int check_password_legality_part1(char* password, char* target, int lower_bound, int upper_bound) {
    int length = strlen(password);
    int count = 0;

    for (int i = 0; i < length; i++) {
        if (password[i] == target[0]) {
            count += 1;
        }
    }

    return (count >= lower_bound) && (count <= upper_bound);
}

int count_legal_passwords_part1(password_t passwords[], int npasswords) {
    int count = 0;

    for (int i = 0; i < npasswords; i++) {
        if (check_password_legality_part1(passwords[i].password, passwords[i].letter, 
                    passwords[i].lower_bound, passwords[i].upper_bound)) {
            count += 1;
        }
    }

    return count;
}

int check_password_legality_part2(char* password, char* target, int lower_bound, int upper_bound) {
    int legal = 0;

    if (password[lower_bound - 1] == target[0]) legal = !legal;
    if (password[upper_bound - 1] == target[0]) legal = !legal;

    return legal;
}

int count_legal_passwords_part2(password_t passwords[], int npasswords) {
    int count = 0;

    for (int i = 0; i < npasswords; i++) {
        if (check_password_legality_part2(passwords[i].password, passwords[i].letter, 
                    passwords[i].lower_bound, passwords[i].upper_bound)) {
            count += 1;
        }
    }

    return count;
}

int main() {
    FILE *input = fopen("day2-input.txt", "r");
    assert(input);

    int npasswords = count_passwords(input);

    password_t* passwords = (password_t*)malloc(sizeof(password_t) * npasswords);
    assert(passwords);

    fseek(input, 0, SEEK_SET);

    fill_passwords(input, passwords);

    int result = count_legal_passwords_part1(passwords, npasswords);
    printf("Number of legal passwords (Part 1): %d\n", result);

    int result2 = count_legal_passwords_part2(passwords, npasswords);
    printf("Number of legal passwords (Part 2): %d", result2);

    fclose(input);
    free(passwords);

    return 0;
}
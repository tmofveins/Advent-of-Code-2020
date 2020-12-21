#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define SEP1 ':'
#define SEP2 ' '
#define SEP3 '\n'
#define CID "cid"
#define NFIELDS 8
#define FIELD_LEN 4

typedef struct passport_t {
    int byr;
    int iyr;
    int eyr;
    char hgt[6];
    char hcl[8];
    char ecl[4];
    int pid;
    int cid;
} passport_t;

int get_npassports(FILE* input) {
    char line[256];
    int npassports = 0;

    while(fgets(line, sizeof(line), input)) {
        if (strcmp(line, "\n") == 0) npassports += 1;
    }

    npassports += 1;

    return npassports;
}

void fill_passports(FILE* input, char** passports, int npassports) {
    char line[128];
    int i = 0;

    while (fgets(line, sizeof(line), input)) {
        if (strcmp(line, "\n") != 0) {
            strcat(passports[i], line);
        } else{
            i++;
        }
    }
}

void remove_newlines_and_delims(char* passport) {
    int length = strlen(passport);

    char* separated_data = (char*)malloc(sizeof(char) * length + 1);

    for (int i = 0; i < length; i++) {
        if (passport[i] == SEP1 || passport[i] == SEP2 || passport[i] == SEP3) {
            separated_data[i] = ' ';
        } else {
            separated_data[i] = passport[i];
        }
    }
    
    strcpy(passport, separated_data);
}

int check_legality_part1(char* passport, const char** fields) {
    int cid_present = 0;
    int nlegal_fields = 0;

    char* token = strtok(passport, " ");

    while (token) {
        for (int i = 0; i < NFIELDS; i++) {
            if (strcmp(token, fields[i]) == 0) {
                nlegal_fields += 1;
                if (strcmp(fields[i], CID) == 0) {
                    cid_present = 1;
                }
            }
        }

        token = strtok(NULL, " ");
    }

    if (cid_present) {
        return (nlegal_fields == 8);
    } else { 
        return (nlegal_fields == 7);
    }
}

int count_legal_passports_part1(char** passports, int npassports, const char** fields) {
    int nlegal_passports = 0;

    for (int i = 0; i < npassports; i++) {
        remove_newlines_and_delims(passports[i]);
        if (check_legality_part1(passports[i], fields)) nlegal_passports += 1;
    }

    return nlegal_passports;
}

int main() {
    const char* fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

    FILE* input = fopen("day4-input.txt", "r");
    assert(input);
    
    int npassports = get_npassports(input);
    
    fseek(input, 0, SEEK_SET);

    char** passports = (char**)malloc(sizeof(char*) * npassports);
    for (int i = 0; i < npassports; i++) {
        passports[i] = (char*) malloc(sizeof(char) * 256);
        passports[i][0] = '\0';
    }
    assert(passports);

    fill_passports(input, passports, npassports);

    int result_part1 = count_legal_passports_part1(passports, npassports, fields);
    printf("Number of legal passports (Part 1): %d\n", result_part1);    

    fclose(input);

    for (int i = 0; i < npassports; i++) free(passports[i]);
    free(passports);

    return 0;
}
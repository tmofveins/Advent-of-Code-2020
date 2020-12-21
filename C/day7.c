#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CONTAIN "contain"
#define COMMA ","

typedef struct bag_t {
    char bag_name[128];
    struct bag_t* next_bag;
} bag_t;

typedef struct list_t {
    struct bag_t* head;
    struct bag_t* foot;
} list_t;

int get_nrules(FILE* input) {
    char line[256];
    int nrules = 0;

    while(fgets(line, sizeof(line), input)) {
        nrules += 1;
    }

    return nrules;
}

void fill_rules(FILE* input, char** rule_strings) {
    char line[256];
    int i = 0;

    while (fgets(line, sizeof(line), input)) {
        strcat(rule_strings[i], line);
        i++;
    }
}

list_t* create_empty_list(void) {
    list_t* rule = (list_t*)malloc(sizeof(list_t));
    assert(rule);

    rule -> head = NULL;
    rule -> foot = NULL;

    return rule;
}

list_t* insert_at_foot(list_t* list, char* bag_name) {
    assert(list);

	bag_t* new_bag = (bag_t*)malloc(sizeof(bag_t));
    assert(new_bag);

    strcpy(new_bag -> bag_name, bag_name);
	new_bag -> next_bag = NULL;

	if (list -> foot == NULL) {
		list -> head = new_bag;
        list -> foot = new_bag;

	} else {
		list -> foot -> next_bag = new_bag;
		list -> foot = new_bag;
	}

	return list;
}

int is_contained(char* source_string, char* target_string) {
	int contained = 0;

	for (int i = 0; target_string[i]; i++) {
		int j = 0;
		int placeholder = i;

		if (target_string[i] == source_string[j]) contained = 1;

		while (contained) {

			if (target_string[i] != source_string[j]) {
				contained = 0;
				j = 0;
			}

			placeholder++;
			j++;

			if (source_string[j] == '\0') return 1;
			if (target_string[placeholder] == '\0') return 0;
			
		}

		if (target_string[i] == '\0') return 0;
	}
	
	return 0; 
}

void parse_rule(char* rule_string) {

    for (int i = 0; i < strlen(CONTAIN); i++) {
        int found = 0;

        for (int j = 0; j < strlen(rule_string); j++) {
        }
    }
}

int main() {
    FILE* input = fopen("day7-input.txt", "r");
    assert(input);

    int nrules = get_nrules(input);

    fseek(input, 0, SEEK_SET);

    char** rule_strings = (char**)malloc(sizeof(char*) * nrules);
    for (int i = 0; i < nrules; i++) {
        rule_strings[i] = (char*)malloc(sizeof(char) * 256);
        rule_strings[i][0] = '\0';
    }
    assert(rule_strings);

    fill_rules(input, rule_strings);
    parse_rule(rule_strings[0]);

    printf("%d", is_contained("hi", "hi"));

    fclose(input);

    return 0;
}
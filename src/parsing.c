#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parsing.h"

ArrayList* tokenize(char* line, char* delimiters, ArrayList** modified_tokens) {
    if(!modified_tokens) print_error_and_exit("No ArrayList buffer to store modified tokens");
    *modified_tokens = create_array(INITIAL_ARGV_SIZE);
    ArrayList* tokens = create_array(INITIAL_ARGV_SIZE);
    if (!tokens || !*modified_tokens) print_error_and_exit("Failed to create ArrayList while tokenizing");
    char * token = strtok(line, delimiters);
    while(token != NULL) {
        char* expanded_path = expand_path(token);
        if (expanded_path) {
            token = expanded_path;
            if (!add_element(*modified_tokens, token)) print_error_and_exit("Failed to add item to ArrayList while expanding path");
        }
        if (!add_element(tokens, token)) print_error_and_exit("Failed to add item to ArrayList while tokenizing");
        token = strtok(NULL, delimiters);
    }
    add_element(tokens, NULL);
    add_element(*modified_tokens, NULL);
    return tokens;
}

char* expand_path(const char* arg) {
    if (arg[0] != '~') return NULL;
    char* result = malloc(strlen(home) + strlen(arg));
    if (!result) print_error_and_exit("Failed malloc while expanding path");
    sprintf(result, "%s%s", home, arg + 1);
    return result;
}

void free_tokens(ArrayList* tokens, ArrayList* modified_tokens) {
    if (modified_tokens) {
        for (size_t i = 0; modified_tokens -> data[i] != NULL; i++) {
            free(modified_tokens -> data[i]);
        }
        free(modified_tokens -> data);
        free(modified_tokens);
    }
    if (tokens) {
        free(tokens -> data);
        free(tokens);
    }
}
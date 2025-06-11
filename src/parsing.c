#include <string.h>
#include <stdlib.h>
#include "parsing.h"

ArrayList* tokenize(char* line, char* delimiters) {
    ArrayList* tokens = create_array(INITIAL_ARGV_SIZE);
    if (!tokens) print_error_and_exit("Failed to create ArrayList");
    char * token = strtok(line, delimiters);
    while(token != NULL) {
        if (!add_element(tokens, token)) print_error_and_exit("Failed to add item to ArrayList");
        token = strtok(NULL, delimiters);
    }
    add_element(tokens, NULL);
    return tokens;
}
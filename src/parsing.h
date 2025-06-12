#ifndef PARSING_H_
#define PARSING_H_

#define INITIAL_ARGV_SIZE 16

#include "utils.h"

extern char* home; //home directory of user.

char* expand_path(const char* arg);
ArrayList* tokenize(char* line, char* delimiters, ArrayList** modified_arguments);
void free_tokens(ArrayList* tokens, ArrayList* modified_tokens);

#endif
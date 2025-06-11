#ifndef PARSING_H_
#define PARSING_H_

#define INITIAL_ARGV_SIZE 16

#include "utils.h"

ArrayList* tokenize(char* line, char* separators);

#endif
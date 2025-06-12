#ifndef PROCESSING_H_
#define PROCESSING_H_

#include "utils.h"

void process_command(char* line, int* running);
void execute_command(ArrayList* tokens, int* running);
int execute_built_in(ArrayList* tokens, int* running);

#endif
#ifndef PROCESSING_H_
#define PROCESSING_H_

void process_command(char* line);
void execute_command(int argc, char** argv);
int execute_built_in(int argc, char** argv);

#endif
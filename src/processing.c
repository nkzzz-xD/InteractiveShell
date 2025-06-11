#include "processing.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include "parsing.h"

void process_command(char* line) {
    ArrayList* tokens = tokenize(line, " \n");
    int argc = tokens -> size;
    if (argc <= 1) { //only value being NULL
        return; 
    }
    char** argv = (char**)tokens -> data;
    int child = fork();
    if (child < 0) print_error_and_exit("Could not create child process to run command");
    else if (child == 0) {
        execute_command(argc, argv);
    }
    else {
        int status;
        waitpid(child, &status, 0);
    }
    free(tokens -> data);
    free(tokens);
}

void execute_command(int argc, char** argv) {
    if (execute_built_in(argc, argv)) return;
    if(execvp(argv[0], argv) < 0) {
        if (strchr(argv[0], '/') != NULL) {
            print_error(argv[0], 1);
        }
        else {
            const char* NOT_FOUND = "Command '%s' not found";
            size_t error_length = strlen(NOT_FOUND) + strlen(argv[0]) - 1;
            char* error = malloc(error_length);
            snprintf(error, error_length, NOT_FOUND, argv[0]);
            print_error(error, 0);
            free(error);
        }
    }
}

int execute_built_in(int argc, char** argv) {
    char* command = argv[0];
    if (!strcmp("cd", command)) {
        printf("Attempt to cd\n");
        return 1;
    }
    if (!strcmp("exit", command)) {
        printf("Exiting prorgam...\n");
        exit(EXIT_SUCCESS); //TODO Why doesn't it work?
    }
    return 0;
}
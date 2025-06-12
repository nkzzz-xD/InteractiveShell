#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include "processing.h"
#include "parsing.h"

void process_command(char* line, int* running) {
    ArrayList* modified_arguments = NULL;
    ArrayList* args = tokenize(line, " \n", &modified_arguments);
    // size = 1 when only value is NULL.
    if (args -> size <= 1 || execute_built_in(args, running)) {
        free_tokens(args, modified_arguments);
        return;
    }  
    int child = fork();
    if (child < 0) print_error_and_exit("Could not create child process to run command");
    else if (child == 0) {
        execute_command(args, running);
    }
    else {
        int status;
        waitpid(child, &status, 0);
    }
    free_tokens(args, modified_arguments);
}

void execute_command(ArrayList* tokens, int* running) {
    char** argv = (char**)tokens -> data;
    if(execvp(argv[0], argv) < 0) {
        if (strchr(argv[0], '/') != NULL) {
            print_error(argv[0], 1);
        }
        else {
            const char* NOT_FOUND = "Command '%s' not found";
            int error_length = snprintf(NULL, 0, NOT_FOUND, argv[0]); // Get required length (excluding null)
            char* error = malloc(error_length + 1);
            if (!error) print_error_and_exit("Malloc failed for error message");
            snprintf(error, error_length + 1, NOT_FOUND, argv[0]);
            print_error(error, 0);
            free(error);
        }
        *running = 0;
    }
}

int execute_built_in(ArrayList* tokens, int* running) {
    char** argv = (char**)tokens -> data;
    char* command = argv[0];
    if (!strcmp("cd", command)) {
        if (tokens -> size > 3) {
            print_error("cd: too many arguments", 0);
        }
        else {
            char* target_path = tokens -> size == 2 ? home : argv[1];
            if(chdir(target_path) < 0) {
                const char* CD_MESSAGE = "cd: %s";
                int error_length = snprintf(NULL, 0, CD_MESSAGE, target_path); // Get required length (excluding null)
                char* error = malloc(error_length + 1);
                if (!error) print_error_and_exit("Malloc failed for error message");
                snprintf(error, error_length + 1, CD_MESSAGE, target_path);
                print_error(error, 1);
                free(error);
            }
        }
        return 1;
    }
    if (!strcmp("exit", command)) {
        *running = 0;
        return 1;
    }
    return 0;
}

//TODO Register exit handlers to free memory
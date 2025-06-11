#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include "colours.h"
#include "processing.h"
#include "utils.h"

void print_prompt();

int main(void) {
    char *line = NULL;
    size_t len = 0;
    while(1) {
        print_prompt();
        ssize_t num_chars = getline(&line, &len, stdin);
        if (num_chars < 0) print_error_and_exit("Could not read line");
        process_command(line);
    }   
    free(line);
    return 0;
}


//For now we will check the environment variables each time as they could change.
void print_prompt() {
    //Get current working directory for shell.
    char* cwd = getcwd(NULL, 0);
    if (!cwd) print_error_and_exit("Error retrieving working directory");

    //Get the username.
    char* username = getenv("LOGNAME");
    struct passwd *pw = getpwuid(getuid());
    if (!username) {
        if (pw && pw -> pw_name) username = pw -> pw_name;
        else username = "?";
    }

    //Get the user's home directory
    char* home = getenv("HOME");
    if (!home) {
        if (pw && pw -> pw_dir) home = pw -> pw_dir;
        else goto print;
    };
    
    //Replace the HOME section of the directory with ~
    char* path_compression = strstr(cwd, home);
    if (path_compression) {
        char* new_cwd = cwd + strlen(home); // Starting from after the home part of directory
        size_t new_path_length = strlen(new_cwd);
        memmove(cwd + 1, new_cwd, new_path_length + 1);
        char* realloced_cwd = realloc(cwd, new_path_length + 2);
        if (realloced_cwd == NULL) print_error_and_exit("Realloc failed when assigning new_cwd");
        cwd = realloced_cwd;
        // Add the path compression ~
        cwd[0] = '~';
    }
    print:
    printf("%s%s@InteractiveShell%s:%s%s%s$ ", VIOLET, username, RESET, BLUE, cwd, RESET);
    free(cwd);
}
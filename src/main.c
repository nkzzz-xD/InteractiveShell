#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include "colours.h"

void print_prompt();

//TODO Add "Pishell" to the error messages
// TODO Make a way to handle errors in a shorter way.
int main(void) {
    char *line = NULL;
    size_t len = 0;
    while (1) {
        print_prompt();
        size_t num_chars = getline(&line, &len, stdin);
        if (num_chars < 0) {
            perror("Could not read line");
            exit(EXIT_FAILURE);
        }
        //execute command
    }   
    free(line);
    return 0;
}


//For now we will check the environment variables each time as they could change.
void print_prompt() {
    char* cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("Error retrieving working directory");
        exit(EXIT_FAILURE);
    }

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
    
    char* path_compression = strstr(cwd, home);
    if (path_compression) {
        char* modified_cwd;
        modified_cwd = strdup(cwd + strlen(home));
        if (!modified_cwd) {
            perror("Malloc failed when duplicating cwd string");
            exit(EXIT_FAILURE);
        }
        char* new_cwd = realloc(cwd, strlen(modified_cwd) + 2);
        if (new_cwd == NULL) {
            perror("Realloc failed when assigning new_cwd");
            exit(EXIT_FAILURE);
        }
        cwd = new_cwd;
        strcpy(cwd + 1, modified_cwd);
        free(modified_cwd);
        // Add the path compression ~
        cwd[0] = '~';
    }
    print:
    printf("%s%s@InteractiveShell%s:%s%s%s$ ", VIOLET, username, RESET, BLUE, cwd, RESET);
    free(cwd);
}
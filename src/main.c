#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include "colours.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "processing.h"
#include "utils.h"

char* home;

char* get_prompt();

int main(void) {
    using_history();
    int running = 1;
    while(running) {
        char* prompt = get_prompt();
        char *line = readline(prompt);
        free(prompt);
        if (!line) {
            print_error_and_exit("Could not read line");
        }
        if (strlen(line) > 0) {
            process_command(line, &running);
            add_history(line);
        }
        free(line);
    }
    clear_history();
    rl_free_line_state();  // Frees internal line buffer
    return 0;
}

//For now we will check the environment variables each time as they could change.
char* get_prompt() {
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
    home = getenv("HOME");
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
    const char* FORMAT_STRING = "%s%s@InteractiveShell%s:%s%s%s$ ";
    int prompt_length = snprintf(NULL, 0, FORMAT_STRING, VIOLET, username, RESET, BLUE, cwd, RESET); // Get required length (excluding null)
    char* prompt = malloc(prompt_length + 1);
    if (!prompt) print_error_and_exit("Malloc failed for error message");
    snprintf(prompt, prompt_length + 1, FORMAT_STRING, VIOLET, username, RESET, BLUE, cwd, RESET);
    free(cwd);
    return prompt;
}
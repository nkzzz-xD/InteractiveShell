#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void print_error(char* error, int print_lib_err) {
    static const char* PROGRAM_NAME = "InteractiveShell: ";
    size_t length = strlen(error) + strlen(PROGRAM_NAME) + 1;
    char* final_message = malloc(length);
    strcpy(final_message, PROGRAM_NAME);
    strcat(final_message, error);
    if (print_lib_err) {
        perror(final_message);
    }
    else {
        printf("%s\n", final_message);
    }
    free(final_message);
}

void print_error_and_exit(char* error) {
    print_error(error, 1);
    exit(EXIT_FAILURE);
}

ArrayList* create_array(int capacity) {
    if (capacity <= 0) capacity = DEFAULT_ARRAY_SIZE;
    ArrayList* array = malloc(sizeof(ArrayList));
    if (!array) return NULL;
    array -> capacity = capacity;
    array -> size = 0;
    array -> data = calloc(capacity, sizeof(void*)); //make sure everything is zero
    if (!array -> data) return NULL;
    return array;
}

int add_element(ArrayList* array, void* element) {
    if (!array) return 0;
    if (array -> size >= array -> capacity) {
        array -> capacity = array -> capacity * 1.5;
        void** new_data = realloc(array -> data, array -> capacity);
        if (!new_data) return 0;
        array -> data = new_data;
    }
    (array -> data)[array -> size++] = element;
    return 1;
};
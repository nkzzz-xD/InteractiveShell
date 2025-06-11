#ifndef UTILS_H_
#define UTILS_H_

void print_error(char* error, int print_lib_err);
void print_error_and_exit(char* error);

//Arraylist to store data of a any type (Up to the programmer the type of each item of data).
typedef struct {
    void** data;
    int capacity;
    int size;
} ArrayList;

#define DEFAULT_ARRAY_SIZE 10

ArrayList* create_array(int capacity);

int add_element(ArrayList* array, void* element);

#endif
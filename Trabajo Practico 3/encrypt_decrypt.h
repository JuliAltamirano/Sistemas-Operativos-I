#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include  <stdbool.h>

struct Errors {

    bool is_error;
    int error_number;

} errors;

struct commonVariables {
 
    char *option[5];

} common_variables;

void encrypt();
void decrypt();
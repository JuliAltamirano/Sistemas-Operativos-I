#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

struct Errors {

    bool is_error;
    int error_number;

} errors;

void encrypt();
void decrypt();
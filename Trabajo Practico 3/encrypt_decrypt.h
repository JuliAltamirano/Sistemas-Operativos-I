#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define ENCRYPT "encrypt"   // Device number 1
#define DECRYPT "decrypt"   // Device number 2

struct Errors {

    bool is_error;
    int error_number;
    char device[7];

} errors;

void encrypt();
void decrypt();
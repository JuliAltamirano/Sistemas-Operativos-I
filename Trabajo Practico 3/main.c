#include "encrypt_decrypt.h"

#define ERROR -1

void errorMessage();

int main(){

    bool opt_fail;
    int result;
    char option[10];
    size_t size_option;

    // Initialize 'Errors' structure
    errors.is_error = false;
    errors.error_number = 0;
    for ( int i = 0; i < 500; i++ ) 
		errors.device[i] = 0;
   
    do {
        opt_fail = false;
        printf("Ingrese la opcion que desea realizar:\n"
               "a) Encriptar cadena.\n"
               "b) Desencriptar cadena.\n");

        result = scanf("%[^\n]%*c", option);
        size_option = strlen(option);

        if( result == EOF ){
            errors.is_error = true;
            errors.error_number = 1;
            errorMessage();
            return EOF;
        }

        if( size_option != 1 || ( option[0] != 'a' && option[0] != 'b' )){
            printf("OPCION INCORRECTA\n");
            opt_fail = true;
        }
        
    } while (opt_fail);

    if( option[0] == 'a' ){
        encrypt();
    }
    else if( option[0] == 'b' ){
        decrypt();
    }

    if( errors.is_error ){
        errorMessage();
        return ERROR;
    }
    return 0;
}

void errorMessage() {
    
    switch( errors.error_number )
    {
        case 1:
            printf("ERROR: no se pudo obtener los caracteres ingresados por el usuario\n");
            break;
        case 2:
            printf("ERROR: no se pudo abrir el archivo del dispositivo '%s'\n", errors.device);
            break;
        case 3:
            printf("ERROR: no se pudo escribir en el archivo del dispositivo '%s'\n", errors.device);
            break;
        case 4:
            printf("ERROR: no se pudo leer el archivo del dispositivo '%s'\n", errors.device);
            break;
        default:
            break;
    }
}
#include "encrypt_decrypt.h"

void errorMessage();

int main(){

    bool opt_fail;
    int result;
    char option[10];
    size_t size_option;
    
    errors.is_error = false;    // Initialize 'is_error' varible
   
    do {
        opt_fail = false;
        printf( "Ingrese la opcion que desea realizar: \n"
                "a) Encriptar cadena. \n"
                "b) Desencriptar cadena. \n");

        result = scanf("%[^\n]%*c", option);
        size_option = strlen(option);

        if(result == EOF){
            printf("ERROR\n");              // TODO: change message
            return EOF;
        }

        if( size_option != 1 || ( option[0] != 'a' && option[0] != 'b' )){
            
            printf("OPCION INCORRECTA\n");  // TODO: change message
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
        return -1;
    }
    return 0;
}

void errorMessage() {
    // TODO
    return;
}
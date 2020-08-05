#include "encrypt_decrypt.h"

void errorMessage();

int main(){

    bool opt_fail;
    int result;
    char *option;
    size_t size_buffer;
    
    errors.is_error = false;    // Initialize 'is_error' varible
   
    do {
        opt_fail = false;
        printf( "Ingrese la opcion que desea realizar: \n"
                "a) Encriptar cadena. \n"
                "b) Desencriptar cadena. \n");

        result = scanf("%s[^\n]", option); 
        size_buffer = strlen(option);
        
        if(result == EOF){
            printf("ERROR\n");              // TODO: change message
            return EOF;
        }

        if( (strcmp(option, "a") != 0) && (strcmp(option, "b") != 0)){
            
            printf("OPCION INCORRECTA\n");  // TODO: change message
            opt_fail = true;
        }
        
    } while (opt_fail);

    if ( strcmp(option, "a") == 0 ){
        encrypt();
    }
    else if( strcmp(option, "b") == 0 ){
        decrypt();
    }

    if (errors.is_error){
        errorMessage();
        return -1;
    }
    return 0;
}

void errorMessage() {
    // TODO
    return;
}
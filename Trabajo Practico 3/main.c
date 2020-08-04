#include "encrypt_decrypt.h"

int main(){

    bool opt_fail;
    char option;

    printf( "Ingrese la opcion que desea realizar: \n"
            "a) Encriptar cadena. \n"
            "b) Desencriptar cadena. \n");
    
    do{
        opt_fail = false;
        printf( "Ingrese la opcion que desea realizar: \n"
                "a) Encriptar cadena. \n"
                "b) Desencriptar cadena. \n");
        option = getchar();
        
        if(option != 'a' && option != 'b'){
            printf("OPCION INCORRECTA\n"); //ver mensaje
            opt_fail = true;
        }
        
    }while (opt_fail);

    if ( option == 'a' ){
        encrypt();
    }
    else if( option == 'b' ){
        decrypt();
    }

    return 0;

}

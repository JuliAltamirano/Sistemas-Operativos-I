#include "encrypt_decrypt.h"

#define NRO_ENCRYPT  3    

void encrypt(){

    FILE *fp_1, *fp_2;
    char buffer[5000], option[10];
    size_t size_buffer, size_option;
    bool opt_fail;
    int result, tmp = 0;

    fp_1 = fopen("/dev/decrypter", "w"); 
    fp_2 = fopen("/dev/encrypter", "r+");             
    
    if ( fp_1 == NULL ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fp_2 == NULL ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a encriptar:\n");

    result = scanf("%[^\n]%*c", buffer);
    size_buffer = strlen(buffer);

    if( result == EOF ){
        printf("ERROR\n");              // TODO: change message
        return;
    }

    result = fwrite(buffer, 1, size_buffer, fp_1);
    /*if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }*/

    char encrypted_str[size_buffer];  // encrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        encrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",encrypted_str);  check
    }

    result = fwrite(encrypted_str, 1, strlen(encrypted_str), fp_2);
    /*if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }*/

    printf ("La cadena ha sido encriptada exitosamente\n");

    do{
        opt_fail = false;
        printf("Desea ver la cadena encriptada? s/n\n");
        
        result = scanf("%[^\n]%*c", option);
        size_option = strlen(option);
        
        if(result == EOF){
            printf("ERROR\n");              // TODO: change message
            return;
        }

        if( size_option != 1 || ( option[0] != 's' && option[0] != 'n' )){
            printf("OPCION INCORRECTA\n"); //ver mensaje
            opt_fail = true;
        }
        
    } while (opt_fail);

    if( option[0] == 's' ){
        char *read_str;
        result = fread(read_str, 1, size_buffer, fp_2);

        /*if( result == -1){                // ferror o 0?
            perror("ERROR: No se pudo leer el archivo \n");
            return;
        }*/

        printf("%s\n", read_str);
    }

    fclose(fp_1);
    fclose(fp_2);    
}

void decrypt(){

    FILE *fp_1, *fp_2;
    char buffer[5000], option[10];
    size_t size_buffer, size_option;
    bool opt_fail;
    int result, tmp = 0;
    
    fp_1 = fopen("/dev/encrypter", "w"); 
    fp_2 = fopen("/dev/decrypter", "r+"); 
                
    if ( fp_1 == NULL ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fp_2 == NULL ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a desencriptar:\n");

    result = scanf("%[^\n]%*c", buffer);
    size_buffer = strlen(buffer);

    if( result == EOF ){
        printf("ERROR\n");              // TODO: change message
        return;
    }

    result = fwrite(buffer, 1, size_buffer, fp_1);
    /*if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }*/

    char decrypted_str[size_buffer];  // decrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        decrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",decrypted_str);  check
    }

    result = fwrite(decrypted_str, 1, strlen(decrypted_str), fp_2);
    /*if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }*/

    printf ("La cadena ha sido desencriptada exitosamente\n");

    do{
        opt_fail = false;
        printf("Desea ver la cadena desencriptada? s/n\n");
        
        result = scanf("%[^\n]%*c", option);
        size_option = strlen(option);
        
        if(result == EOF){
            printf("ERROR\n");              // TODO: change message
            return;
        }

        if( size_option != 1 || ( option[0] != 's' && option[0] != 'n' )){
            printf("OPCION INCORRECTA\n"); //ver mensaje
            opt_fail = true;
        }
        
    } while (opt_fail);

    if( option[0] == 's' ){
        char *read_str;
        result = fread(read_str, 1, size_buffer, fp_2);

        /*if( result == -1){                // ferror o 0?
            perror("ERROR: No se pudo leer el archivo \n");
            return;
        }*/

        printf("%s", read_str);
    }

    fclose(fp_1);
    fclose(fp_2);
}
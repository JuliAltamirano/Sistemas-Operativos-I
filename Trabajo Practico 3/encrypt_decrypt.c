#include "encrypt_decrypt.h"

#define NRO_ENCRYPT  3    

void encrypt(){

    int fd_1, fd_2;
    char buffer[5000], option[10];
    size_t size_buffer, size_option;
    bool opt_fail;
    int result, tmp = 0;

    fd_1 = open("/dev/decrypt", O_RDWR); //O_WRONLY
    fd_2 = open("/dev/encrypt", O_RDWR);             
    
    if ( fd_1 == -1 ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fd_2 == -1 ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a encriptar:\n");

    result = scanf("%[^\n]%*c", buffer);
    size_buffer = strlen(buffer);

    //printf("%s", buffer);

    if( result == EOF ){
        printf("ERROR\n");              // TODO: change message
        return;
    }

    result = write(fd_1, buffer, size_buffer);
    if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }

    char encrypted_str[size_buffer];  // encrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        encrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",encrypted_str);  check
    }

    result = write(fd_2, encrypted_str, strlen(encrypted_str));
    if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }

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
        result = read(fd_2, read_str, size_buffer);

        if( result == -1){                // ferror o 0?
            perror("ERROR: No se pudo leer el archivo \n");
            return;
        }        
        printf("%s\n", read_str);
    }

    close(fd_1);
    close(fd_2);    
}

void decrypt(){

    int fd_1, fd_2;
    char buffer[5000], option[10];
    size_t size_buffer, size_option;
    bool opt_fail;
    int result, tmp = 0;
    
    fd_1 = open("/dev/encrypt", O_RDWR);    //O_WR
    fd_2 = open("/dev/decrypt", O_RDWR); 
                
    if ( fd_1 == -1 ){
        printf("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fd_2 == -1 ){
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

    result = write(fd_1, buffer, size_buffer);
    if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }

    char decrypted_str[size_buffer];  // decrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        decrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",decrypted_str);  check
    }

    result = write(fd_2, decrypted_str, strlen(decrypted_str));
    if( result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }

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
        result = read(fd_2, read_str, size_buffer);

        if( result == -1){                // ferror o 0?
            perror("ERROR: No se pudo leer el archivo \n");
            return;
        }
        printf("%s", read_str);
    }

    close(fd_1);
    close(fd_2);
}
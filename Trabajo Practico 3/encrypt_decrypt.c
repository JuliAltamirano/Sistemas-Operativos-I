#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include  <stdbool.h>

#define NRO_ENCRYPT  3    

void encrypt(){

    int fd_1, fd_2;
    char *buffer; 
    int tmp= 0;
    bool opt_fail;
    char option;
    size_t size_buffer;
    
    fd_1 =  open ("/dev/decrypter",O_WRONLY); 
    fd_2 = open("/dev/encrypter", O_RDWR);             
    
    if ( fd_1 == -1 ){
        perror("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fd_2 == -1 ){
        perror("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a encriptar: \n");
    //scanf("%[^\n]%*c", buffer); 
    scanf("%s", buffer); 
    size_buffer = strlen(buffer);

    int w_result = write(fd_1, buffer, size_buffer);
    if( w_result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }
    if( w_result == 0){
        printf("Cadena vacia");
        //return
    }


    char encrypted_str[size_buffer];  // encrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        encrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",encrypted_str);  check
    }

    w_result = write(fd_2, encrypted_str, strlen(encrypted_str));
    if( w_result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }
    if( w_result == 0){
        printf("Cadena vacia");
        //return
    }

    printf ("La cadena ha sido encriptada exitosamente \n");

    do{
        opt_fail = false;
        printf("Desea ver la cadena encriptada? s/n ");
        option = getchar();
        
        if(option != 's' && option != 'n'){
            printf("OPCION INCORRECTA\n"); //ver mensaje
            opt_fail = true;
        }
        
    }while (opt_fail);

    if(option == 's'){
        char *read_str;
        read(fd_2, read_str, size_buffer);
        printf("%s", read_str);
    }

    close(fd_1);
    close(fd_2);
    
}

void decrypt(){

    int fd_1, fd_2;
    char *buffer; 
    int tmp= 0;
    bool opt_fail;
    char option;
    size_t size_buffer;
    
    fd_1 = open("/dev/encrypter", O_WRONLY); 
    fd_2 =  open ("/dev/decrypter",O_RDWR); 
                
    if ( fd_1 == -1 ){
        perror("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }
    else if( fd_2 == -1 ){
        perror("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a desencriptar: \n");
    //scanf("%[^\n]%*c", buffer); 
    scanf("%s", buffer); 
    size_buffer = strlen(buffer);

    int w_result = write(fd_1, buffer, size_buffer);
    if( w_result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }
    if( w_result == 0){
        printf("Cadena vacia");
        //return
    }


    char decrypted_str[size_buffer];  // decrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        decrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",decrypted_str);  check
    }

    w_result = write(fd_2, decrypted_str, strlen(decrypted_str));
    if( w_result == -1){
        perror("ERROR: No se pudo escribir en el archivo \n");
        return;
    }
    if( w_result == 0){
        printf("Cadena vacia");
        //return
    }

    printf ("La cadena ha sido desencriptada exitosamente \n");

    do{
        opt_fail = false;
        printf("Desea ver la cadena desencriptada? s/n ");
        option = getchar();
        
        if(option != 's' && option != 'n'){
            printf("OPCION INCORRECTA\n"); //ver mensaje
            opt_fail = true;
        }
        
    }while (opt_fail);

    if(option == 's'){
        char *read_str;
        read(fd_2, read_str, size_buffer);
        printf("%s", read_str);
    }

    close(fd_1);
    close(fd_2);
}
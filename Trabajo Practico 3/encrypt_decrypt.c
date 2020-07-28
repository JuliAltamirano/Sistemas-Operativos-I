#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include  <stdbool.h>

#define NRO_ENCRYPT  3    

void encrypt(){

    int fd;
    char *buffer; 
    int tmp= 0;
    bool opt_fail;
    char option;
    size_t size_buffer;
    

    fd = open("/dev/encrypt", O_RDWR);             
    //fp=  open ("/dev/desencr_char",O_RDWR); 
    if ( fd == -1 ){
        perror("ERROR: No se pudo abrir el dispositivo \n");
        perror(errno + "" );
        return;
    }

    printf("Escriba la cadena a encriptar: \n");
    //scanf("%[^\n]%*c", buffer); 
    scanf("%s", buffer); 
    size_buffer = strlen(buffer);


    char encrypted_str[size_buffer];  // encrypted string 

    for(int i=0; i< size_buffer ; i++){
        tmp = buffer[i];
        tmp += NRO_ENCRYPT;
        encrypted_str[i] = tmp;
        //tmp = 0; check 
        //printf("%s\n",encrypted_str);  check
    }

    int w_result = write(fd, encrypted_str, strlen(encrypted_str));
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
        read(fd, read_str, size_buffer);
        printf("%s", read_str);
    }

    close(fd);
    
}

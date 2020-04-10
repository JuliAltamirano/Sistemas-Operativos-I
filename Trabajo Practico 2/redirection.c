#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "structures.h"

void  output(){

	char mensaje[30];

	for(int i= 1; instruction_values.buffer[i] !=NULL; i++) {
		
		if( (strcmp( ">" , instruction_values.buffer[i])) == 0 ){
			/*int fd= open(instruction_values.buffer[i+1], O_CREAT, O_WRONLY);
			printf("%d\n", fd );*/
			//printf("%s\n", mensaje );
			FILE *fp;
			fp = fopen ( instruction_values.buffer[i+1], "w+" );        
			if( fp == NULL ){
				 exit (1);
			}
		  	
		  	fputs(mensaje, fp);
			fclose ( fp );

		}
		else{
			strcat(mensaje, instruction_values.buffer[i]);
			strcat(mensaje, " " );
		}
	}
}

void input(){

	char mensaje[30]= {0};
	char buffer[50]= {0};

	for(int i=1; instruction_values.buffer[i] != NULL; i++){

		if( (strcmp("<", instruction_values.buffer[i])) == 0 ){
			FILE *fp;
			fp= fopen( instruction_values.buffer[i+1], "r+");
			if( fp == NULL){
				printf("No existe archivo solicitado en directorio actual");
				exit(1);
			} 
			fgets(buffer, 50, fp);
			strcat(buffer, mensaje);
			fputs( buffer, fp);
			fclose ( fp );
			break;
		}
		else{
			strcat(mensaje, " ");
			strcat(mensaje, instruction_values.buffer[i]);
		}

	}

}
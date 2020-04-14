#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "structures.h"

void  output(int position){

	char message[3000];

	if (instruction_values.buffer[position+2] != NULL) {
		redirection_values.error_output= 1;
		failsRedirection();
		return;
	}

	for(int i = 1; i < position; i++) {
		
		strcat(message, instruction_values.buffer[i]);
		strcat(message, " " );
	}

	FILE *fp;
	fp = fopen ( instruction_values.buffer[position+1], "ab+" );  // Flag "ab+" = O_RDWR|O_CREAT|O_APPEND

	/*if( fp == NULL ) {  // I think this is innecessary
		exit (-1); 		// correct error type and print an apropiate message
	}*/

	fputs(message, fp);
	fclose (fp);
}

void input(){

	char file_content[3000];

	if (instruction_values.buffer[3] != NULL) {
		// print error, incorrect quantity of arguments, or something like that
		// we should make specific types of error messages, like we made in errorMenssage() function in execute.c
		redirection_values.error_input= 1;
		failsRedirection();
		return;
	}

	/*if (instruction_values.buffer[2] ){ // check if the filename doesn't exist in the actual directory 
										// (I don't remember how to check it, we have to complete it)
		//print error
		return;
	}*/

	FILE *fp;
	fp = fopen ( instruction_values.buffer[2], "r" );

	if( fp == NULL ) { 
		redirection_values.error_input= 2;
		failsRedirection();
		exit (-1); 		
	}

	fread(file_content, 1, 3000, fp);
	fclose(fp);

	printf("%s\n", file_content);
}

void failsRedirection(){
	
	if( redirection_values.error_input == 2 ){
		printf("bash: echo: archivo solicitado inexitente en directorio actual \n");
		return;
	}
	if ( (redirection_values.error_input == 1) || (redirection_values.error_output == 1) ){
		printf("bash: echo: demasiados argumentos\n");
		return;
	}

}
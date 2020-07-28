#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "structures.h"


void initializeRedirectionValues () {

	redirection_values.error_type = 0;
	redirection_values.is_redirection_error = false;
}

void  output(int position){		// Find a way to create files with multiple words in their filename


	char message[3000];

	if (instruction_values.buffer[position+2] != NULL) {

		redirection_values.is_redirection_error = true;
		redirection_values.error_type = 1;
		return;
	}

	for(int i = 1; i < position; i++) {
		
		strcat(message, instruction_values.buffer[i]);
		strcat(message, " " );
	}

	FILE *fp;
	fp = fopen ( instruction_values.buffer[position+1], "ab+" );  // Flag "ab+" = O_RDWR|O_CREAT|O_APPEND

	fputs(message, fp);
	fclose (fp);
}

void input(){ // Fix error with existing files and find a way to show files with multiples words in their filename

	char file_content[3000];

	if (instruction_values.buffer[3] != NULL) {
		
		redirection_values.is_redirection_error = true;
		redirection_values.error_type = 1;
		return;
	}

	FILE *fp;
	fp = fopen ( instruction_values.buffer[2], "r" );

	if( fp == NULL ) { 

		redirection_values.is_redirection_error = true;		
		redirection_values.error_type = 2;
		return;
	}

	fread(file_content, 1, 3000, fp);
	fclose(fp);

	printf("%s\n", file_content);
}
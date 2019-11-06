#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "instructions.h"

struct ExecuteValues {

	pid_t pid;
	int is_error;
	int choise;
	int error_type;

	int fd[2];

} execute_values;

void initializeExecuteValues() {

	execute_values.is_error = 0;
	execute_values.choise = 0;
	execute_values.error_type = 0;
}

void errorMenssage() {

	if ( execute_values.error_type == 1 ) {

		fprintf(stderr, "bash: cd: %s: No existe el archivo o el directorio\n", instruction_values.buffer[1]);
		return;
	}

	if ( execute_values.error_type == 2 ) {
			
		fprintf(stderr, "bash: cd: demasiados argumentos\n");
		return;
	}

	fprintf(stderr, "%s: orden no encontrada\n", instruction_values.buffer[0]);
}

void executeCd () {

	if ( instruction_values.buffer[2] != NULL ) {
		execute_values.is_error = -1;
		execute_values.error_type = 2;
		return;
	}

	execute_values.error_type = 1;

	if ( instruction_values.buffer[1] == NULL ) {
					
		printf("buffer1 vacio\n");
		execute_values.is_error = chdir( getenv ("HOME") );
	}
	else if ( 0 == strcmp(instruction_values.buffer[1], "..\n") )	{
		//chdir ();
		printf(" buffer1 ..\n" );
	}
	else {
		printf("buffer1 comandos         %s\n", instruction_values.direction);
		strcat ( instruction_values.direction, "/");
		strcat ( instruction_values.direction, instruction_values.buffer[1] );

		printf("direction         %s\n", instruction_values.direction);
		execute_values.is_error = execl("/bin/sh", "sh", "-c", instruction_values.direction, (char *) 0);
		
	}

	if (execute_values.is_error == 0)
		write ( execute_values.fd[1], "Correct", 7);
}

void execute () {

	initializeExecuteValues();

	char bufferAux [7] = {0};
	pipe(execute_values.fd);

	execute_values.pid = fork();
	
	execute_values.choise = inputClassification();


	//child process
	if (execute_values.pid == 0){

		close ( execute_values.fd[0]);

		switch ( execute_values.choise ) {

			case 1:
				printf("case 1:        \n");
				executeCd();
				break;
			case 2:
				printf("case 2:        \n" );
				execute_values.is_error = execl("/bin/sh", "sh", "-c", "clear", (char *) 0);
				break;
			case 3:
				printf("case 3:        \n" );
				execute_values.is_error = execvp ( instruction_values.buffer[0], instruction_values.buffer );
			case 4:
				break;
			case 5:
				printf("case 5:        \n");
				//chdir( instruction_values.direction);
				//execute_values.is_error = 
				break;
			case 6:
				printf("case 6:        \n" );
				execute_values.is_error = execl("/bin/sh", "sh", "-c", instruction_values.buffer[0], (char *) 0);
				break;
		}

		close(execute_values.fd[1]);
		
		if ( execute_values.is_error == -1)
			errorMenssage();

		exit(0);
	}
	//father process
	else {
		wait(0);
		close ( execute_values.fd[1]);

		read (execute_values.fd[0], bufferAux, 7);
		printf("PADRE\n");
		if ( execute_values.choise == 1 && strcmp(bufferAux, "Correct")==0) {

			if ( instruction_values.buffer[1] ==NULL ) {
				
				printf("buffer1 vacio (padre)\n");
				
				/*strcpy ( instruction_values.prompt, "");
				strcpy ( instruction_values.direction, "");
				strcat ( instruction_values.prompt, getenv("USER"));
				strcat ( instruction_values.direction, getenv("HOME"));
				//initializeInstructionValues();
				commandLinePrompt (instruction_values.prompt);*/
			}
			else if ( 0 == strcmp(instruction_values.buffer[1], "..\n") )	{
				//chdir ();
				printf(" buffer1 .. (padre)\n" );
			}
			else {
				printf("buffer1 comandos (padre)\n");
				strcat ( instruction_values.direction, "/");
				strcat ( instruction_values.direction, instruction_values.buffer[1] );
				strcat ( instruction_values.prompt, "/");
				strcat (instruction_values.prompt, instruction_values.buffer[1]);
			}

		}

		close(execute_values.fd[0]);
	}
	//strcat(prompt, bufferAux );
	//strcat(direction, bufferAux );
	//printf("prompt: %s\n", prompt);
		
}
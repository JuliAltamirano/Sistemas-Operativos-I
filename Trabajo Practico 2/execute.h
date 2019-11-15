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

void correctDirectionPath ( char direction[], bool one_arg) {

	int quantity = 0;
	char tmp [300] = {0};

	if (!one_arg){

		for (int i =1; instruction_values.buffer[i] != NULL; i++) {

			strcat(tmp, instruction_values.buffer[i]);
			strcat(tmp, " ");
		}
		quantity = strcspn(tmp, "\n");
		strncat(direction, tmp, quantity);
		return;
	}

	quantity = strcspn(instruction_values.buffer[1], "\n");
	strncat(direction, instruction_values.buffer[1], quantity);
}

void executeCd () {

	char direction_aux [300] = {0};
	char tmp[500] = {0};
	size_t home_length = strlen(getenv("HOME"));

	if ( instruction_values.buffer[2] != NULL ) {
		
		correctDirectionPath(direction_aux, false);

		execute_values.is_error = chdir (direction_aux);

		if ( execute_values.is_error == -1 ) {

			execute_values.error_type = 2;
			return;
		}

		strcat(tmp, instruction_values.direction);
		strcat(tmp, "/");
		strcat(tmp, direction_aux);

		initializeInstructionValues();
		commandLinePrompt();

		strcat(instruction_values.direction, tmp);
		strcat(instruction_values.prompt, instruction_values.direction);
		return;
	}

	execute_values.error_type = 1;

	if ( instruction_values.buffer[1] == NULL ) {

		initializeInstructionValues();
		commandLinePrompt();

		execute_values.is_error = chdir(getenv ("HOME"));
	}
	else if ( 0 == strcmp(instruction_values.buffer[1], "..\n") )	{
		
		execute_values.is_error = chdir ("..");

		if ( execute_values.is_error == -1 )
			return;

		initializeInstructionValues();
		commandLinePrompt();

		getcwd (tmp, sizeof(tmp));

		if (0 != strcmp(tmp, getenv("HOME"))) {

			if (strlen(tmp) > home_length) {
				
				for ( int i = 0; i < (sizeof(tmp) - home_length); i++ )
					tmp [i] = tmp[home_length + i];
			}

			strcat(instruction_values.direction, tmp);
			strcat(instruction_values.prompt, instruction_values.direction);
		}

	}
	else {

		correctDirectionPath(direction_aux, true);

		execute_values.is_error = chdir (direction_aux);

		if ( execute_values.is_error == -1 )
			return;
		
		strcat(tmp, instruction_values.direction);
		if (0 != strcmp(direction_aux, "home"))
			strcat(tmp, "/");
		strcat(tmp, direction_aux);

		initializeInstructionValues();
		commandLinePrompt();

		if (0 != strcmp(tmp, getenv("HOME"))) {

			strcat(instruction_values.direction, tmp);
			strcat(instruction_values.prompt, instruction_values.direction);
		}
	}
}

void execute () {

	initializeExecuteValues();

	execute_values.pid = fork();
	
	execute_values.choise = inputClassification();
	
	//child process
	if (execute_values.pid == 0){

		char tmp[100];

		switch ( execute_values.choise ) {

			case 1:
				break;
			case 2:
				execute_values.is_error = execl("/bin/sh", "sh", "-c", "clear", (char *) 0);
				break;
			case 3:
				execute_values.is_error = execvp ( instruction_values.buffer[0], instruction_values.buffer );
			case 4:
				break;
			case 5:
				execute_values.is_error = execl("/bin/sh", "sh", "-c", instruction_values.buffer[0], (char *) 0);
				break;
		}
		
		if ( execute_values.is_error == -1)
			errorMenssage();

		exit(0);
	}
	//father process
	else {

		wait (0);

		if ( execute_values.choise == 1) {

			executeCd();
		}

		if ( execute_values.is_error == -1)
			errorMenssage();
	}		
}
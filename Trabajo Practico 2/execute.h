#include <sys/types.h>
#include <sys/wait.h>

#include "instructions.h"

void initializeExecuteValues() {

	execute_values.choise = 0;
	execute_values.is_error = 0;
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

			changeDirectory();
		}

		if ( execute_values.is_error == -1)
			errorMenssage();
	}		
}
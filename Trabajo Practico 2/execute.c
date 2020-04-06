#include "structures.h"

void initializeExecuteValues () {

	execute_values.choise = 0;
	execute_values.is_error = 0;
	execute_values.error_type = 0;
	execute_values.background_ex = false;
}

void errorMenssage () {

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

		char execution_path[100] = "";
		char tmp[100] = "/usr/bin/";

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
				strcat( tmp, instruction_values.buffer[0]);

				if ( ( strstr(instruction_values.buffer[0], "&") != NULL ) && ( strspn(instruction_values.buffer[0], "&") == (strlen(instruction_values.buffer[0] - 2)) ) )
					strncpy( execution_path, tmp, (strlen(tmp) - 2));
				else 
					strncpy( execution_path, tmp, (strlen(tmp) - 1));
				
				execute_values.is_error = execl( execution_path, execution_path, NULL);
				break;
		}
		
		if ( execute_values.is_error == -1)
			errorMenssage();

		exit(0);
	}
	//father process
	else {

		if ( execute_values.choise != 5 ||
				!( strstr(instruction_values.buffer[0], "&") != NULL ) && ( strspn(instruction_values.buffer[0], "&") == (strlen(instruction_values.buffer[0] - 2)) ) )
			{
				wait (0);
			}
		else
			execute_values.background_ex = true;

		if ( execute_values.choise == 1) {

			changeDirectory();
		}

		if ( execute_values.is_error == -1)
			errorMenssage();
	}		
}
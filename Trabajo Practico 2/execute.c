#include "structures.h"

void initializeExecuteValues () {

	execute_values.choise = 0;
	execute_values.is_error = 0;
	execute_values.error_type = 0;
	execute_values.quit = false;
}

void errorMenssage () {

	if ( redirection_values.is_redirection_error ) {

		if ( redirection_values.error_type == 1 ) {

			printf("bash: echo: demasiados argumentos\n");
			return;
		}

		if ( redirection_values.error_type == 2 ) {

			printf("bash: echo: archivo solicitado inexitente en directorio actual\n");
			return;
		}
	}

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

void runPipe(char left[], char rigth[]) {
	char execution_path[100] = "/usr/bin/";
	int fd[2];
	pipe(fd);

	int pid = fork();
	//child process
	if (pid == 0) {
		strcat(execution_path, left);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execl(execution_path, execution_path, NULL);
	}
	else {
		strcat(execution_path, rigth);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execl(execution_path, execution_path, NULL);
	}
}

void execute () {

	initializeExecuteValues();
	initializeRedirectionValues();

	execute_values.pid = fork();
	
	execute_values.choise = inputClassification();
	
	//child process
	if (execute_values.pid == 0){

		char execution_path[100] = "";
		char tmp[100] = "/usr/bin/";
		bool is_i_o = false; // para echo 

		switch ( execute_values.choise ) {

			case 1:
				break;
			case 2:
				execute_values.is_error = execl("/bin/sh", "sh", "-c", "clear", (char *) 0);
				break;
			case 3:
				for(int i = 1; instruction_values.buffer[i] != NULL; i++) {
					if( (strcmp( ">" , instruction_values.buffer[i])) == 0 ){
						is_i_o = true;
						output(i);
						break;
					}
					else if( (strcmp( "<" , instruction_values.buffer[1])) == 0 ){
						input();
						is_i_o = true;
						break;		
					}
				}
				if( !is_i_o ){
					execute_values.is_error = execvp ( instruction_values.buffer[0], instruction_values.buffer );		
				}
			case 4:
				break;
			case 5:
				strcat( tmp, instruction_values.buffer[0]);
				bool flag_pipe = false;

				for(int i = 0; instruction_values.buffer[i] != NULL; i++) {
					if(strstr(instruction_values.buffer[i], "|") != NULL)
						flag_pipe = true;
				}

				if (flag_pipe) {
					char tmp_pipe [300] = {0};
					char arg_left [100] = {0};
					char arg_right [100] = {0};

					for (int i = 0; instruction_values.buffer[i] != NULL; i++) {
						strcat(tmp_pipe, instruction_values.buffer[i]);
						strcat(tmp_pipe, " ");
					}
					
					strcat(arg_left, strtok ( tmp_pipe, "|" ));
					strcat(arg_right, strtok ( NULL, "|" ));
					runPipe(arg_left, arg_right);
					break;
				}
				else if ( ( strstr(instruction_values.buffer[0], "&") != NULL ) && ( strspn(instruction_values.buffer[0], "&") == (strlen(instruction_values.buffer[0] - 2)) ) )
					strncpy( execution_path, tmp, (strlen(tmp) - 2));
				else 
					strncpy( execution_path, tmp, (strlen(tmp) - 1));
				
				execute_values.is_error = execl( execution_path, execution_path, NULL);
				break;
		}
		
		if ( execute_values.is_error == -1 || redirection_values.is_redirection_error )
			errorMenssage();

		exit(0);
	}
	//father process
	else {

		switch ( execute_values.choise )
		{
			case 1:
				changeDirectory();
			case 2:
			case 3:
				wait (0);
				break;
			case 4:
				execute_values.quit = true;
				wait (0);
				break;
			case 5:
				if ( strstr(instruction_values.buffer[0], "&") != NULL && ( strcspn(instruction_values.buffer[0], "&") == (strlen(instruction_values.buffer[0]) - 2) ) )
					break;
				
				wait (0);	//TODO: check
				break;
		}

		if ( execute_values.is_error == -1)
			errorMenssage();
	}		
}
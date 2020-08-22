#include "structures.h"

void initializeDirectoryValues () {

	for ( int i = 0; i < 500; i++ ) {

		directory_values.prompt[i] = 0;
		directory_values.directory[i] = 0;
	}
}

void commandLinePrompt () {

	char buffer[100] = {0};
	
	strcat (directory_values.prompt, getenv("USER"));
	strcat (directory_values.prompt, "@" );

	FILE *fp = fopen ( "/proc/sys/kernel/hostname", "r" );
	fgets ( buffer, 50, fp );
	fclose(fp);
	
	char bf[ strlen ( buffer ) - 1 ];
	strncpy ( bf, buffer , sizeof (bf) );

	strcat( directory_values.prompt, bf );
	strcat( directory_values.prompt, ":" );
}

void fixDirectionPath ( char directory[], bool one_arg ) {

	int quantity = 0;
	char tmp [300] = {0};

	if (!one_arg){

		for (int i =1; instruction_values.buffer[i] != NULL; i++) {

			strcat(tmp, instruction_values.buffer[i]);
			strcat(tmp, " ");
		}
		quantity = strcspn(tmp, "\n");
		strncat(directory, tmp, quantity);
		return;
	}

	quantity = strcspn(instruction_values.buffer[1], "\n");
	strncat(directory, instruction_values.buffer[1], quantity);
}

void changeDirectory () {

	char directory_aux [300] = {0};
	char tmp[500] = {0};
	size_t home_length = strlen(getenv("HOME"));
	char home[home_length];
	strcat(home, getenv("HOME"));

	if ( instruction_values.buffer[2] != NULL ) {
		
		fixDirectionPath(directory_aux, false);

		execute_values.is_error = chdir (directory_aux);

		if ( execute_values.is_error == -1 ) {

			execute_values.error_type = 2;
			return;
		}

		strcat(tmp, directory_values.directory);
		strcat(tmp, "/");
		strcat(tmp, directory_aux);

		initializeDirectoryValues();
		commandLinePrompt();

		strcat(directory_values.directory, tmp);

		if ( 0 == strncmp(directory_values.directory, home, home_length) )
			strcat(directory_values.prompt, "~");
		strcat(directory_values.prompt, directory_values.directory);
		return;
	}

	execute_values.error_type = 1;

	if ( instruction_values.buffer[1] == NULL ) {

		initializeDirectoryValues();
		commandLinePrompt();
		strcat(directory_values.prompt, "~");

		execute_values.is_error = chdir(home);
	}
	else if ( 0 == strcmp(instruction_values.buffer[1], "..\n") )	{
		
		execute_values.is_error = chdir ("..");

		if ( execute_values.is_error == -1 )
			return;

		initializeDirectoryValues();
		commandLinePrompt();

		getcwd (tmp, sizeof(tmp));

		if (0 != strcmp(tmp, home)) {

			if ( 0 == strncmp(tmp, home, home_length) ) {
				
				//verificar que se escribe en las posiciones restantes
				for ( int i = 0; i < (sizeof(tmp) - home_length); i++ )
					tmp [i] = tmp[home_length + i];
				strcat(directory_values.prompt, "~");
			}

			strcat(directory_values.directory, tmp);				
			strcat(directory_values.prompt, directory_values.directory);
		}
		else 
			strcat(directory_values.prompt, "~");
	}
	else {

		fixDirectionPath(directory_aux, true);

		execute_values.is_error = chdir (directory_aux);

		if ( execute_values.is_error == -1 )
			return;
		
		strcat(tmp, directory_values.directory);
		if (0 != strcmp(directory_aux, "home"))
			strcat(tmp, "/");
		strcat(tmp, directory_aux);

		initializeDirectoryValues();
		commandLinePrompt();

		if (0 != strcmp(tmp, home)) {

			strcat(directory_values.directory, tmp);

			getcwd (tmp, sizeof(tmp));
			if ( 0 == strncmp(tmp,home,home_length) )
				strcat(directory_values.prompt, "~");
			strcat(directory_values.prompt, directory_values.directory);
		}
		else
			strcat(directory_values.prompt, "~");
	}
}
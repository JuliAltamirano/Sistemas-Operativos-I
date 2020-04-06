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

void correctDirectionPath ( char directory[], bool one_arg ) {

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

	if ( instruction_values.buffer[2] != NULL ) {
		
		correctDirectionPath(directory_aux, false);

		execute_values.is_error = chdir (directory_aux);

		if ( execute_values.is_error == -1 ) {

			execute_values.error_type = 2;
			return;
		}

		strcat(tmp, directory_values.directory);
		strcat(tmp, "/");
		strcat(tmp, directory_aux);

		updatePrompt(false, tmp, false);

		return;
	}

	execute_values.error_type = 1;

	if ( instruction_values.buffer[1] == NULL ) {

		updatePrompt(false, tmp, false);

		execute_values.is_error = chdir(getenv ("HOME"));
	}
	else if ( 0 == strcmp(instruction_values.buffer[1], "..\n") )	{
		
		execute_values.is_error = chdir ("..");

		if ( execute_values.is_error == -1 )
			return;

		updatePrompt(true, tmp, false);
	}
	else {

		correctDirectionPath(directory_aux, true);

		execute_values.is_error = chdir (directory_aux);

		if ( execute_values.is_error == -1 )
			return;
		
		strcat(tmp, directory_values.directory);
		if (0 != strcmp(directory_aux, "home"))
			strcat(tmp, "/");
		strcat(tmp, directory_aux);

		updatePrompt(false, tmp, false);
	}
}

void updatePrompt(bool cd_backward, char tmp[500], bool background_ex){

	size_t home_length = strlen(getenv("HOME"));
	char aux[500] = {0};
	//char tmp[500] = tmp;
	getcwd (aux, sizeof(aux));

	initializeDirectoryValues();
	commandLinePrompt();	

	if (0 != strcmp(tmp, getenv("HOME")) && 0 != strcmp(aux, getenv("HOME"))) {

		if (cd_backward){
			if (strlen(aux) > home_length) {
						
				//verificar que se escribe en las posiciones restantes
				for ( int i = 0; i < (sizeof(aux) - home_length); i++ )
					tmp [i] = aux[home_length + i];
			}
			else{
				for ( int i = 0; i < sizeof(aux); i++ )
					tmp [i] = aux[i];
			}				
		}
		if (!background_ex)
			strcat(directory_values.directory, tmp);
		strcat(directory_values.prompt ,directory_values.directory);
	}		
}
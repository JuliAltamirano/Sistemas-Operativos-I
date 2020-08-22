#include "structures.h"

void fileCommand(char name_file[]);

int main(int argc, char **argv)
{
	system ("clear");
	
	initializeDirectoryValues();

	if ( argc > 2 )
		return  -1;

	if( argc > 1 ){

		fileCommand( argv[1] );		
		return 0;
	}
	
	chdir (HOME);

	commandLinePrompt();
	strcat(directory_values.prompt, "~");

	do {
		printf( "%s$ ", directory_values.prompt );

		char *line = NULL;
		size_t line_size = 0;

		getline ( &line, &line_size, stdin );

		saveInput ( line );

		execute();

	} while ( !execute_values.quit );

	return 0;
}

void fileCommand( char name_file[] ){

	FILE* fp;
	size_t bytes_read;
	char *instruction = NULL;
	size_t instruction_size = 0;

	fp = fopen( name_file, "r");

	chdir (HOME);

	while ( ( (bytes_read = getline( &instruction, &instruction_size, fp )) != -1 ) && !execute_values.quit ) {

		saveInput( instruction );	
		execute();
		sleep(1);
	}
	
	fclose(fp);
}
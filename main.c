#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "execute.h"

int main(int argc, char **argv)
{
	//system ("clear");

	initializeInstructionValues();

	if ( argc > 2 )
		return  -1;

	if( argc > 1 ){

		fileCommand( argv[1] );
	}
	else{

		commandLinePrompt();

		do {
			printf( "%s$ ", instruction_values.prompt );

			char *line = NULL;
			size_t line_size = 0;

			getline ( &line, &line_size, stdin );
			instruction_values.last_line = line;

			saveInput ( line );

			execute();

		} while ( strncmp( instruction_values.last_line, "quit\n", 5 ) != 0);

	}

	return 0;
}
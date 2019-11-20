#include "change_directory.h"


void saveInput ( char *input ) {

	char *word = "";
	instruction_values.buffer[0] = strtok ( input, " " );

	for ( int i=1; word != NULL; i++ ) {

		word = strtok ( NULL, " " );

		instruction_values.buffer[i] = word;
	}
}

int inputClassification (){

	if ( 0 == strcmp( instruction_values.buffer[0], "cd" ) ||  0 == strcmp( instruction_values.buffer[0], "cd\n" ) )
		return 1;
	else if ( 0 == strcmp( instruction_values.buffer[0], "clr\n" ) )
		return 2;
	else if ( 0 == strcmp( instruction_values.buffer[0], "echo" ) || 0 == strcmp( instruction_values.buffer[0], "echo\n" ) )
		return 3;
	else if ( 0 == strcmp( instruction_values.buffer[0], "quit\n" ) )
		return 4;
	else
		return 5;
}
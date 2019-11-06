#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct InstructionValues {

	char *buffer[30];
	char *last_line;
	char *direction;
	char *prompt;

} instruction_values;

void initializeInstructionValues () {

	instruction_values.prompt = getenv("USER");
	instruction_values.direction = getenv("HOME");
}

void commandLinePrompt (){

	char buffer[100];

	strcat( instruction_values.prompt, "@" );

	FILE *fp = fopen ( "/proc/sys/kernel/hostname", "r" );
	fgets ( buffer, 50, fp );
	fclose(fp);
	
	char bf[ strlen ( buffer ) - 1 ];
	strncpy ( bf, buffer , sizeof (bf) );

	strcat( instruction_values.prompt, bf );
	strcat( instruction_values.prompt, ":~" );
}

void saveInput ( char *input ) {

	char *word;
	instruction_values.buffer[0] = strtok ( input, " " );
	/*if ( !checkCorrectInput( buffer[0] ) )
		return;*/

	for ( int i=1; word != NULL; i++ ) {

		word = strtok ( NULL, " " );

		instruction_values.buffer[i] = word;
	}
}

void fileCommand( char* name_file ){

	FILE* fp;
	size_t bytes_read;
	char *instruction = NULL;
	size_t instruction_size = 0;

	fp= fopen( name_file, "r");

	while ( (bytes_read = getline( &instruction, &instruction_size, fp )) != -1 ) {

		saveInput( instruction );	
		//execute;		
	}
	
	fclose(fp);	
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
	else if ( 0 == strncmp( instruction_values.buffer[0], "./", 2 ) )
		return 5;
	else
		return 6;
}
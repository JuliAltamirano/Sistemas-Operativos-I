#include "execute.h"

void fileCommand( char name_file[] ){

	FILE* fp;
	size_t bytes_read;
	char *instruction = NULL;
	size_t instruction_size = 0;

	fp= fopen( name_file, "r");

	chdir ("/home/julieta");

	while ( (bytes_read = getline( &instruction, &instruction_size, fp )) != -1 ) {

		saveInput( instruction );	
		execute();
		sleep(1);
	}
	
	fclose(fp);	
}
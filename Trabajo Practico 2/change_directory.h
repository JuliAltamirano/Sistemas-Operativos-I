#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct DirectoryValues {

	char directory[500];
	char prompt[500];

} directory_values;

void initializeDirectoryValues () {

	for ( int i = 0; i < 500; i++ ) {

		directory_values.prompt[i] = 0;
		directory_values.directory[i] = 0;
	}
}


void commandLinePrompt (){

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

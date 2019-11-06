/*
------------------------------------
Autor      :Aichino Ignacio Daniel; Altamirano Julieta
Descripcion : Sistemas Operativos - TP1 - 2019
--------------------------
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <stdlib.h>
#include "WithoutOption.h"
#include "OptionS.h"
#include "OptionI.h"
#include "OptionPFT.h"



const char* program_name;

int main(int argc, char *argv[]) {
	
	size_t bytes_read = 0;
	FILE* fp = NULL;
		
	headline( fp, bytes_read );
	
	getCpuInfo( fp, bytes_read );
	getKernel( fp, bytes_read );
	getTime( fp, bytes_read );
	getFileSystems( fp, bytes_read );

	int next_option;

	const char* const short_options = "sI:p:f:t:";
	
	int interval;
	int duration;

	const struct option long_options[] = {
		{ "soption", 0, NULL, 's' },
		{ "Ioption", 1, NULL, 'I' },
		{ "poption", 1, NULL, 'p' },
		{ "foption", 1, NULL, 'f' },
		{ "toption", 1, NULL, 't' },
		{ NULL,	0, NULL, 0	} };

	program_name = argv[0];
	do {
		
		next_option = getopt_long (argc, argv, short_options, long_options, NULL);
		switch (next_option)
		{

			case 't':
				optionP (argv[2], fp, bytes_read);				
				optionF (argv[2], fp, bytes_read);
				optionT (argv[2], fp, bytes_read);
				break;

			case 'f':
				optionP (argv[2], fp, bytes_read);
				optionF (argv[2], fp, bytes_read);
				break;

			case 'p':
				optionP (argv[2], fp, bytes_read);
				break;

			case 'I':
				interval = atoi(argv[2]);
				duration = atoi(argv[3]);
				while ( duration > 0 ) {

					diskRequest( fp, bytes_read );
					memoryInformation(fp, bytes_read );
					loadAverage( fp, bytes_read);
					printf("[Pausa de %d segundos]\n", interval);
					sleep( interval );
					duration -= interval;
				}
								
			case 's':
				getCPUTime ( fp, bytes_read );
				getProcessStatus( fp, bytes_read );
				getQuantityOfProcesses ( fp, bytes_read );
				break;


			case '?':
				case -1:
				break;
			
			default:
				abort ();
		}
	}
	while (next_option != -1);

	return 0;
}

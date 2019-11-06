#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void getCPUTime ( FILE* fp, size_t bytes_read ) {

	char buffer[250];
	char* match;
	float user, system, idle;

	fp = fopen ("/proc/stat", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "cpu");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "cpu %f %*f %f %f", &user, &system, &idle ); //%* saltea el lugar
	printf("\nCantidad de tiempo de CPU utilizado \nUsuarios: %f \nSistema: %f \nProceso Idle: %f\n", user/100, system/100, idle/100);

}

void getProcessStatus ( FILE* fp, size_t bytes_read ) {

	char buffer[1000];
	char* match;
	int context;

	fp = fopen ("/proc/stat", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "ctxt");
	
	if (match == NULL)
		exit(0);
	
	
	sscanf (match, "ctxt %d", &context); 
	printf("Cambios de contexto: %d \n", context);
}

void getQuantityOfProcesses( FILE* fp, size_t bytes_read ){

	char buffer[1000];
	char* match;
	int process;

	fp = fopen ("/proc/stat", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "processes");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "processes %d", &process ); 
	printf("Cantidad de procesos creados desde el inicio del sistema: %d \n", process);
}
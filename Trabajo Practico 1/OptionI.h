#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void diskRequest(FILE* fp, size_t bytes_read) {

	char buffer[1000];
	char* match;
	int reads, writes;

	fp = fopen ("/proc/diskstats", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "sda");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "sda %d %*d %*d %*d %d", &reads, &writes); //%* saltea el dato
	printf("\nCantidad de peticiones al disco: %d\n", reads+writes);
}

void memoryInformation(FILE* fp, size_t bytes_read) {

	char buffer[250];
	char* match;
	int total, available;

	fp = fopen ("/proc/meminfo", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "MemTotal");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "MemTotal:  %d", &total);

	//
	match = strstr (buffer, "MemAvailable");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "MemAvailable:  %d", &available);

	printf("Cantidad de memoria: \nTotal: %dkB\nAvailable: %dkB\n", total, available);
}

void loadAverage(FILE* fp, size_t bytes_read) {
	char buffer[5];
	float average;

	fp = fopen ("/proc/loadavg", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	sscanf (buffer, "%f", &average);
	printf("Promedio de carga de 1 minuto: %.2f\n", average);
}
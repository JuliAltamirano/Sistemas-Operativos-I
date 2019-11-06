#include <string.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <stdlib.h>



void headline( FILE* fp, size_t bytes_read ) {

	char buffer[50];
	time_t t;
	struct tm *tm;
	char fechayhora[100];

	fp = fopen ( "/proc/sys/kernel/hostname", "r" );
	bytes_read = fread ( buffer, 1, sizeof(buffer), fp);
	fclose (fp);
	
	buffer[bytes_read - 1] = ' ';

	t=time(NULL);
	tm=localtime(&t);
	
	strftime(fechayhora, 100, "%d/%m/%Y  %H:%M:%S \n", tm);

	printf("Hostname:  %s                          %s\n\n", buffer, fechayhora);
}

void getCpuInfo ( FILE* fp, size_t bytes_read) {

	char buffer[10000];
	char* match;
	char cpu_model[100], cpu_type[50];
	
	fp = fopen ("/proc/cpuinfo", "r");
	bytes_read = fread (buffer, 1, sizeof (buffer), fp);
	fclose (fp);

	if (bytes_read == 0 || bytes_read == sizeof (buffer)) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	//
	match = strstr (buffer, "model");
	if (match == NULL)
		exit(0);
	

	sscanf (match, "model : %100[^\n]", cpu_type); //%100[^\n] lee 100 caracteres hasta el salto de linea
	printf("Cpu type: %s \n", cpu_type);

	//
	match = strstr (buffer, "model name");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "model name : %100[^\n]", cpu_model); //%100[^\n] lee 100 caracteres hasta el salto de linea
	printf("Cpu model: %s \n", cpu_model);
}

void getKernel( FILE* fp, size_t bytes_read ) {

	char buffer[400];
	
	fp = fopen ( "/proc/version", "r" );
	bytes_read = fread ( buffer, 1, sizeof(buffer), fp);
	fclose (fp);

	printf("\nKernel version: %s\n", buffer);
}

void getTime( FILE* fp, size_t bytes_read ) {

	char buffer[20];
	int t, sec, min, hour, day;

	fp = fopen ( "/proc/uptime", "r" );
	bytes_read = fread ( buffer, 1, sizeof(buffer), fp);
	fclose (fp);

	sscanf (buffer, "%d", &t);

	day = t/60/60/24;
	hour = t/60/60%24;
	min = t/60%60;
	sec = t%60;

	printf ("Cantidad de tiempo transcurrido desde que se inició el sistema operativo: %d dias  %d:%d:%d hs\n", day, hour, min, sec );
}

void getFileSystems( FILE* fp, size_t bytes_read ){

	char buffer[500];
	int cantidad = 0;
	
	fp = fopen ( "/proc/filesystems", "r" );
	bytes_read = fread ( buffer, 1, sizeof(buffer), fp);
	fclose (fp);

	buffer[bytes_read] = '\n';

	for (int i = 0; i < bytes_read; i++ ) {

		if ( buffer[i] == '\n' )
			cantidad ++;
	}

	printf("Cantidad de sistemas de archivo soportados por el kernel: %d\n", cantidad);
}
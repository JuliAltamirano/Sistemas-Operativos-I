#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

void optionP ( char pid[], FILE* pipe, size_t bytes_read ){

	char buffer[30000];
	char direction[40] = "ls -l /proc/";
	
	strcat(direction, pid);
	strcat(direction, "/fd");

	pipe = popen ( direction, "r");
	bytes_read = fread (buffer, 1, sizeof(buffer), pipe);
	pclose(pipe);


	if ( bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	printf("\nPROCESO %s\n", pid );
	printf("\nFile descriptors: \n %s\n", buffer);
}

void optionF ( char pid[], FILE* fp, size_t bytes_read ) {

	char buffer[1000];
	int soft, hard;
	char* match;
	char direction[40] = "/proc/";
	
	strcat(direction, pid);
	strcat(direction, "/limits");

	fp = fopen ( direction, "r");
	bytes_read = fread (buffer, 1, sizeof(buffer), fp);
	fclose(fp);


	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}


	match = strstr (buffer, "Max open files");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "Max open files %d %d", &soft, &hard);
	printf("\nLimites de archivos abiertos:	Soft: %d 	Hard:%d\n\n", soft, hard);
}

void optionT ( char pid[], FILE* pipe, size_t bytes_read ) {
 
	char buffer[10000];
	char direction[40] = "sudo cat /proc/";
	char stack[100];
 	char* match;
	

	strcat(direction, pid);	
	strcat(direction, "/stack");

	pipe = popen ( direction, "r");
	bytes_read = fread (buffer, 1, sizeof(buffer), pipe);
	pclose(pipe);


	if (bytes_read == 0 ) {

		printf("No se encontro la informacion deseada\n");
		exit(0);
	}

	match = strstr (buffer, "do_syscall_64");
	if (match == NULL)
		exit(0);
	
	sscanf (match, "do_syscall_64%100[^\n]", stack );
	printf("Nombre del simbolo: do_syscall_64%s \n", stack);
}

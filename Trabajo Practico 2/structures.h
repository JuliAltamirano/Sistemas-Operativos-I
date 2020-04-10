#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Variables' definition
struct DirectoryValues {

	char directory[500];
	char prompt[500];

} directory_values;

struct InstructionValues {

	char *buffer[30];
	char *last_line;

} instruction_values;

struct ExecuteValues {

	pid_t pid;
	int choise;
	int is_error;
	int error_type;

} execute_values;

// change_directory.c functions declaration
void initializeDirectoryValues ();
void commandLinePrompt ();
void correctDirectionPath ( char directory[], bool one_arg );
void changeDirectory ();

// instructions.c functions declaration
void saveInput ( char *input );
int inputClassification ();

// execute.c functions declaration
void initializeExecuteValues ();
void errorMenssage ();
void execute ();

// redirection.c funtions declaration
void output();
void input();
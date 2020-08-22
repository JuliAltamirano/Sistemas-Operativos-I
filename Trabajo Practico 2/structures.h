#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define HOME ((const char *)getenv("HOME"))
#define USER ((const char *)getenv("USER"))

// Variables' definition
struct DirectoryValues {

	char directory[500];
	char prompt[500];

} directory_values;

struct InstructionValues {

	char *buffer[30];

} instruction_values;

struct ExecuteValues {

	pid_t pid;
	int choise;
	int is_error;
	int error_type;
	bool quit;

} execute_values;

struct RedirectionValues {
	int error_type;
	bool is_redirection_error;
} redirection_values;

// change_directory.c functions declaration
void initializeDirectoryValues ();
void commandLinePrompt ();
void fixDirectionPath ( char directory[], bool one_arg );
void changeDirectory ();

// instructions.c functions declaration
void saveInput ( char *input );
int inputClassification ();

// execute.c functions declaration
void initializeExecuteValues ();
void errorMenssage ();
void execute ();

// redirection.c funtions declaration
void initializeRedirectionValues ();
void output(int position);
void input();
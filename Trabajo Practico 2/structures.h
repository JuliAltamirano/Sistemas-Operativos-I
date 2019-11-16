#include <stdlib.h>

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
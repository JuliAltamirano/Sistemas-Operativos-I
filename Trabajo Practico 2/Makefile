ejecutable: main.o instructions.o execute.o change_directory.o redirection.o
		gcc -Wall -pedantic -o ejecutable main.o instructions.o execute.o change_directory.o redirection.o 
main.o: main.c 
		gcc -Wall -pedantic -c main.c 
instructions.o: instructions.c
		gcc -Wall -pedantic -c instructions.c
execute.o: execute.c
		gcc -Wall -pedantic -c execute.c
change_directory.o: change_directory.c
		gcc -Wall -pedantic -c change_directory.c
redirection.o: redirection.c
		gcc -Wall -pedantic -c redirection.c
clean:
		rm -f ejecutable *.o
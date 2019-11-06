rdproc: main.o 
		gcc -Wall -pedantic -o rdproc main.o 
main.o: main.c WithoutOption.h OptionS.h OptionI.h OptionPFT.h
		gcc -Wall -pedantic -c main.c
clean:
		rm -f rdproc *.o

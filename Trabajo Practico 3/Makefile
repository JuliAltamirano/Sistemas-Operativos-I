obj-m += encrypt.o
obj-m += decrypt.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) main.c encrypt_decrypt.c encrypt_decrypt.h -o executable	
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm executable

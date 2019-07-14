obj-m += mysched.o

KBUILD_EXTRA_SYMBOLS += /proc/kallsyms
 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


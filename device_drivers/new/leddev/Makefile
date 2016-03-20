MODULE_NAME=leddev

obj-m := ${MODULE_NAME}.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNELDIR) M=$(PWD) modules
#make -C /lib/modules/$(uname -r)/build M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean 

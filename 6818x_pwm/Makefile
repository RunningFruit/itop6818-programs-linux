export ARCH=arm
obj-m += 6818x_pwm.o
#KDIR := /home/topeet/6818/android5.1/lollipop-5.1.1_r6/linux/kernel/kernel-3.4.39
KDIR := /home/topeet/6818/android5.1/lollipop-5.1.1_r6/kernel

PWD = $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o modules.order *.ko *mod.c Module.symvers


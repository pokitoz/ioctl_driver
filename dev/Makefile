MODULE = ioctl

ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m  := $(MODULE).o
$(MODULE)-y := ioctl_interface.o

ccflags-y := -std=gnu89 -g -Wall -Wno-unused-function -Wno-declaration-after-statement

else

# normal makefile
ifeq ($(KDIR),)

DEFAULT_KDIR := /lib/modules/$(shell uname -r)/build

ERR_TEXT=export KDIR=<linux_src_dir> is empty. Using /lib/modules/$(shell uname -r)/build
$(warning $(ERR_TEXT))

KDIR := $(DEFAULT_KDIR)

endif 

all:
	$(MAKE) clean
	$(MAKE) -C $(KDIR) M=$$PWD

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions

endif

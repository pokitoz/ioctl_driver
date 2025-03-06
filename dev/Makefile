MODULE = ioctl

ifneq ($(KERNELRELEASE),)

  # kbuild part of makefile
  obj-m  := $(MODULE).o
  $(MODULE)-y := ioctl_interface.o
  ccflags-y := -g -Wall -Wno-unused-function -Wno-declaration-after-statement

else

  ifeq ($(KDIR),)

    KDIR := /lib/modules/$(shell uname -r)/build
    $(warning KDIR is not set. Using $(KDIR))

  endif # if KDIR is not set

  all:
	$(MAKE) clean
	$(MAKE) -C $(KDIR) M=$$PWD

  clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions

endif # if KERNELRELEASE

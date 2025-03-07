MODULE = ioctl
CROSS_COMPILE ?=
ARCH ?= x86_64

# KDIR is the kernel source directory
#   for buildroot, it is buildroot/output/build/linux-xxxxxx

ifneq ($(KERNELRELEASE),)

  # kbuild part of makefile
  obj-m  := $(MODULE).o
  $(MODULE)-y := ioctl_interface.o
  ccflags-y := -g -Wall -Wextra

else

  ifeq ($(KDIR),)

    KDIR := /lib/modules/$(shell uname -r)/build
    $(warning KDIR is not set. Using $(KDIR))

  endif # if KDIR is not set

  all:
	$(MAKE) clean
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) M=$$PWD

  clean:
	$(RM) -rf *.o *~ core .depend .*.cmd *.ko *.mod.c *.mod \
			  modules.order Module.symvers
	$(RM) -rf .tmp_*

  .PHONY: all clean

endif # if KERNELRELEASE

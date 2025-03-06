# IOCTL Linux Driver

Simple example on how to create a IOCTL driver for Linux thanks
to [LDD3](https://lwn.net/Kernel/LDD3/). This can be used for simple
testing purposes:

* Access to a special register from kernel mode to get the result in
  user mode. For example Arm register from CP15 processor.
* Access to some memory mapped region
* ...


This repo contains the folders below:

- `dev/`: driver source code:

    * `ioctl_interface.c` is the source code of the driver. The function that
      should be modified to add more IOCTL
    * `ioctl_dev.h` is the header file
    * `ioctl.h` contains the list of IOCTL codes. This list is also included
      in the application
    * `Makefile` to build the driver. If the driver is cross-compiled, the
      variable `KDEV` should be adjusted


- `app/`: application source code:

    * `ioctl_app.c` shows an example to access the driver and get the returned
       value
    * `Makefile` to build the application


- `load_module.sh`: Load the module

    * Unload and load the module. This probably needs sudo permissions!


## Run

Use `make`, it will build the .ko module, the application and load the module.

## Debug

Look for printk output in: `/dev/kmsg` or `dmesg`

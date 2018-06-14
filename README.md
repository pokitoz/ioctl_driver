IOCTL Driver
============

Simple example on how to create a IOCTL driver for Linux.
This can be used for simple testing purposes:
* Access to a special register from kernel mode to get the result in user mode. For example Arm register from CP15 processor.
* Access to some memory mapped region
* ...

This repo contains the following folders:

dev/ : driver source code
-------------------------

* ioctl_interface.c is the source code of the driver. The function that should be modified to add more IOCTL
* ioctl_dev.h is the header file
* ioctl.h contains the list of IOCTL codes. This list is also included in the application
* Makefile to build the driver. If the driver is cross-compiled, the variable KDEV should be adjusted


app/ : application source code
------------------------------

* ioctl_app.c shows an example to access the driver and get the returned value
* Makefile to build the application


load_driver.sh
--------------

Load the driver _ioctl_. This probably needs sudo permissions!

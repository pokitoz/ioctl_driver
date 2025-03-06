all:
	$(MAKE) -C dev
	$(MAKE) -C app
	sudo ./load_module.sh
	sudo dmesg | grep ioctl_d_interface

clean:
	$(MAKE) -C dev clean
	$(MAKE) -C app clean

.PHONY: all clean

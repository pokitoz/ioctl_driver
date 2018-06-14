CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -std=c99 -O0 -g -Wconversion -Wextra

all: clean ioctl_app

ioctl_app: ioctl_app.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o ioctl_app

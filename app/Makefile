CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -g -Wconversion -Wextra -Werror
TARGET = ioctl_app

all: clean $(TARGET)

clean:
	rm -rf *.o $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all clean

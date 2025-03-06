#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>

#include "../dev/ioctl.h"

#define IOCTL_DRIVER_NAME "/dev/ioctl"

static int open_driver(const char* driver_name);
static void close_driver(const char* driver_name, int fd_driver);

static int open_driver(const char* driver_name)
{
    printf("* Open Driver\n");

    int fd_driver = open(driver_name, O_RDWR);
    if (fd_driver == -1)
    {
        printf("ERROR: could not open \"%s\".\n", driver_name);
        printf("    errno = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return fd_driver;
}

static void close_driver(const char* driver_name, int fd_driver)
{
    printf("* Close Driver\n");

    int result = close(fd_driver);
    if (result == -1)
    {
        printf("ERROR: could not close \"%s\".\n", driver_name);
        printf("    errno = %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    int fd_ioctl = open_driver(IOCTL_DRIVER_NAME);
    uint32_t value = 0;
    if (ioctl(fd_ioctl, IOCTL_BASE_GET_MUIR, &value) < 0)
    {
        perror("Error ioctl");
        exit(EXIT_FAILURE);
    }

    printf("Value is %u/0x%x\n", value, value);

    close_driver(IOCTL_DRIVER_NAME, fd_ioctl);
    return EXIT_SUCCESS;
}

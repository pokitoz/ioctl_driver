#ifndef __IOCTL_DEFINE_H__
#define __IOCTL_DEFINE_H__

// See https://github.com/torvalds/linux/blob/v6.14/Documentation/userspace-api/ioctl/ioctl-number.rst
//   for the list of ioctl number used as base.
// Helps to avoid conflicts by having different commands if we talk to the wrong device.
#define IOCTL_BASE 'W'
#define IOCTL_GET_VAL _IO(IOCTL_BASE, 1)

#endif // __IOCTL_DEFINE_H__

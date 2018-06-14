#ifndef __IOCTL_DEV_DEFINE_H__
#define __IOCTL_DEV_DEFINE_H__

typedef struct
{
	atomic_t available;
	struct semaphore sem;
	struct cdev cdev;
} ioctl_d_interface_dev;

int ioctl_d_interface_open(struct inode *inode, struct file *filp);
int ioctl_d_interface_release(struct inode *inode, struct file *filp);
long ioctl_d_interface_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#endif // __IOCTL_DEV_DEFINE_H__

#include <linux/cdev.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/moduleparam.h>
#include <linux/version.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/sched.h>

#include "ioctl_dev.h"
#include "ioctl.h"

/* store the major number extracted by dev_t */
static int ioctl_d_interface_major = 0;
static int ioctl_d_interface_minor = 0;
static ioctl_d_interface_dev ioctl_d_interface;

const char* C_IOCTL_DRIVER_NAME = "ioctl_d";

struct file_operations ioctl_d_fops = {
  .owner = THIS_MODULE,
  .read = NULL,
  .write = NULL,
  .open = ioctl_d_interface_open,
  .unlocked_ioctl = ioctl_d_interface_ioctl,
  .release = NULL
};

/**
 * @brief ioctl_d_interface_exit
 * @note __exit is an hint used to free memory if module is built as a driver
 */
static void __exit ioctl_d_interface_exit(void)
{
  cdev_del(&ioctl_d_interface.cdev);
  unregister_chrdev_region(
    MKDEV(ioctl_d_interface_major, ioctl_d_interface_minor),
    1);

  pr_info("ioctl_d_interface: module unloaded\n");
}

/**
 * @brief ioctl_d_interface_init
 * @return 0 on success, negative on failure
 * @note __init is used to free memory of the function after module is loaded
 */
static int __init ioctl_d_interface_init(void)
{
  dev_t devno = 0;
  int result = 0;

  memset(&ioctl_d_interface, 0, sizeof(ioctl_d_interface_dev));

  // register char device by getting major number dynamically (in devno)
  // see ldd3
  result = alloc_chrdev_region(&devno, ioctl_d_interface_minor, 1,
                               C_IOCTL_DRIVER_NAME);
  if (result < 0) {
    pr_warn("ioctl_d_interface: on major number %d\n",
            ioctl_d_interface_major);
    goto fail;
  }

  ioctl_d_interface_major = MAJOR(devno);
  ioctl_d_interface_minor = MINOR(devno);

  // Init cdev and add it to the system
  cdev_init(&(ioctl_d_interface.cdev), &ioctl_d_fops);
  ioctl_d_interface.cdev.owner = THIS_MODULE;
  ioctl_d_interface.cdev.ops = &ioctl_d_fops;
  result = cdev_add(&ioctl_d_interface.cdev, devno, 1);
  if (result < 0) {
    pr_warn( "ioctl_d_interface: error %d adding dev", result);
    goto fail;
  }

  pr_info("ioctl_d_interface: module loaded\n");
  return 0;

fail:
  ioctl_d_interface_exit();
  return result;
}

/* Public API */
int ioctl_d_interface_open(struct inode* inode, struct file* filp)
{
  ioctl_d_interface_dev* ioctl_d_interface;

  ioctl_d_interface = container_of(inode->i_cdev, ioctl_d_interface_dev, cdev);
  filp->private_data = ioctl_d_interface;
  return 0;
}

long ioctl_d_interface_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
{
  pr_info("<%s>: %u\n", module_name(THIS_MODULE), cmd);

  switch (cmd) {

    case IOCTL_GET_VAL:
      const uint32_t value = 0x12345678;
      if (copy_to_user((uint32_t*) arg, &value, sizeof(value))) {
        return -EFAULT;
      }
      break;

    default:
      break;
  }

  return 0;
}

module_init(ioctl_d_interface_init);
module_exit(ioctl_d_interface_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Depraz <florian.depraz@outlook.com>");
MODULE_DESCRIPTION("IOCTL Interface driver");
MODULE_VERSION("0.3");

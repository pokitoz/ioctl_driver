#!/bin/bash

device_name=ioctl
mode="444"

echo "Loading module $device_name"
# invoke insmod and use a pathname, as insmod doesn't look in . by default
/sbin/insmod "./dev/$device_name.ko" || exit 1

echo "Use lsmod to see all devices loaded"

# retrieve major number
major=$(cat /proc/devices | grep "$device_name")
major_number=($major)
echo "Removing stale nodes"
rm -f /dev/${device_name}
echo "Replacing the old nodes"
mknod /dev/${device_name} c ${major_number[0]} 0
major=$(cat /proc/devices | grep "$device_name")

echo "To remove a device, do \"/sbin/rmmod $device_name \" and \"rm -f /dev/${module}\""


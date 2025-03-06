#!/bin/bash -e

DEVICE_NAME=ioctl

lsmod | grep "$DEVICE_NAME" &> /dev/null &&
    /sbin/rmmod ${DEVICE_NAME} &&
    rm -f /dev/${DEVICE_NAME} &&
    echo "Module removed"

echo "Loading module $DEVICE_NAME"
# invoke insmod and use a pathname, as insmod doesn't look in . by default
/sbin/insmod "./dev/$DEVICE_NAME.ko" || exit 1
echo -e "Use lsmod to see modules loaded:\n  $(lsmod | grep ${DEVICE_NAME})"

# Retrieve major number
MODULE_ID=($(cat /proc/devices | grep "$DEVICE_NAME"))
echo "Create node with ID ${MODULE_ID[0]}"
mknod /dev/${DEVICE_NAME} c ${MODULE_ID[0]} 0
chmod 666 /dev/${DEVICE_NAME}

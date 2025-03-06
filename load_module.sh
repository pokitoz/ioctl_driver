#!/bin/sh -e

DEVICE_NAME=ioctl
PATH_TO_MODULE="./dev/$DEVICE_NAME.ko"

if [ ! -z $1 ]; then
    PATH_TO_MODULE=$1
fi

echo "Loading module at $PATH_TO_MODULE"

lsmod | grep "$DEVICE_NAME" &> /dev/null &&
    /sbin/rmmod ${DEVICE_NAME} &&
    rm -f /dev/${DEVICE_NAME} &&
    echo "Module removed"

echo "Loading module $DEVICE_NAME"
# invoke insmod and use a pathname, as insmod doesn't look in . by default
/sbin/insmod "${PATH_TO_MODULE}" || exit 1
echo -e "Use lsmod to see modules loaded:\n  $(lsmod | grep ${DEVICE_NAME})"

# Retrieve major number
MODULE_ID=($(cat /proc/devices | grep "$DEVICE_NAME"))
echo "Create node with ID ${MODULE_ID[0]}"
mknod /dev/${DEVICE_NAME} c ${MODULE_ID[0]} 0
chmod 666 /dev/${DEVICE_NAME}

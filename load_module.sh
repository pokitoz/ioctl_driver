#!/bin/sh -e
# Load module script. Will remove the old one if it exists

MODULE_NAME=ioctl
MODULE_PATH="./dev/$MODULE_NAME.ko"

lsmod | grep "$MODULE_NAME" &> /dev/null &&
    /sbin/rmmod ${MODULE_NAME} &&
    rm -f /dev/${MODULE_NAME} &&
    echo "Module removed"

if [ ! -z $1 ]; then
    MODULE_PATH=$1
fi

echo "Loading module ${MODULE_NAME} at ${MODULE_PATH}"
# invoke insmod and specify the path to module .ko file.
/sbin/insmod "${MODULE_PATH}" || exit 1
echo "Use lsmod to see modules loaded:\n  $(lsmod | grep ${MODULE_NAME})"

# Retrieve module id
MODULE_ID=$(cat /proc/devices | grep "${MODULE_NAME}" | cut -d' ' -f1)
echo "Create node with ID ${MODULE_ID}"
mknod /dev/${MODULE_NAME} c ${MODULE_ID} 0
chmod 666 /dev/${MODULE_NAME}

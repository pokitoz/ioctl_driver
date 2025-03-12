#!/bin/sh
# Load module script. Will remove the old one if it exists

MODULE_NAME=ioctl
MODULE_PATH="./dev/$MODULE_NAME.ko"

# Remove module if it exists
if [ ! -z "$(lsmod | grep ${MODULE_NAME})" ]; then
    /sbin/rmmod ${MODULE_NAME} &&
        rm -f /dev/${MODULE_NAME} &&
        echo "Module removed"
fi

if [ ! -z $1 ]; then
    MODULE_PATH=$1
fi


set -e
MODULE_INFO="$(modinfo ${MODULE_PATH})"
MODULE_ABSOLUTE_PATH="$(echo ${MODULE_INFO} | awk '/filename/{print $2}')"

# Module can load only against the kernel it was compiled for
echo "Loading module ${MODULE_NAME} at ${MODULE_PATH} at ${MODULE_ABSOLUTE_PATH}"

# invoke insmod and specify the path to module .ko file.
/sbin/insmod "${MODULE_PATH}" || exit 1
echo "Use lsmod to see modules loaded: '$(lsmod | grep ${MODULE_NAME})'"

# Retrieve module id
MODULE_ID=$(cat /proc/devices | grep "${MODULE_NAME}" | cut -d' ' -f1)
echo "Create node with ID ${MODULE_ID}"
mknod /dev/${MODULE_NAME} c ${MODULE_ID} 0
chmod 666 /dev/${MODULE_NAME}

DIR="/sys/module/${MODULE_NAME}/sections/"
TEXT_ADDR=$(cat "$DIR/.text")
BSS_ADDR=$(cat "$DIR/.bss")
DATA_ADDR=$(cat "$DIR/.data")
echo "Use this command in host gdb for debug:"
echo "  add-symbol-file $MODULE_ABSOLUTE_PATH $TEXT_ADDR -s .bss $BSS_ADDR -s .data $DATA_ADDR"

#!/bin/bash
export PATH=$PATH:arm-2007q3/bin/
echo $PATH
arm-none-linux-gnueabi-gcc plyta.c -o plyta -lpthread
gcc client.c -o client -lpthread
picocom -b 115200 /dev/ttyS0
ifconfig eth0 
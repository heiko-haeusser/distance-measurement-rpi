#!/bin/bash
# some custom magic
# stored at /usr/local/blinky.sh
# /etc/blinking/interval
# board definitions:
# Button 	GPIO26 
# Button_PU	GPIO13 
# LED 		GPIO23
# Ultrasonic 
# Trigger	GPIO18
# Echo		GPIO24
#sleep 5

echo "Task 6: kernel module blinky started..."

# init the hw (all pins)
sudo insmod /usr/local/task-6/distance-measurement-rpi.ko


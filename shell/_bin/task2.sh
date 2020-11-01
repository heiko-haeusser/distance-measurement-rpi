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

echo "Task 2: blinky started..."

# init the hw (all pins)
sudo bash /opt/hw_init.sh
# define the blinking interval in the file /etc/blinking/interval to adjust interval frequency from the outside
# this is forehold for future tasks
if ls /etc/ | grep --quiet blinking; then
	echo interval dir already exists > /dev/ttyS0
else
	echo create dir /etc/blinking/ > /dev/ttyS0
	sudo mkdir /etc/blinking/
fi
if ls /etc/blinking/ | grep --quiet interval; then
	echo interval file already exists > /dev/ttyS0
else
	echo create interval file and define standard frequency to 1Hz > /dev/ttyS0
	touch /etc/blinking/interval
	echo 1 > /etc/blinking/interval
fi

read -d $'\x04' interval < /etc/blinking/interval

COUNTER=0
while [  $COUNTER -lt 2 ]; do
	echo 1 > /sys/class/gpio/gpio23/value
	sleep $interval
    
	echo 0 > /sys/class/gpio/gpio23/value
	sleep $interval
	COUNTER=$((COUNTER+1))
done

# deinit the hw (all pins)
sudo bash /opt/hw_deInit.sh

echo "Task 2: blinky ended :)"

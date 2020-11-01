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

echo "start uninstall routine"

if [[ "$(whoami)" != root ]]; then
	echo "Only user root can run this script."
	exit -1
fi

if [[ $1 == -cpp ]]; then
	#install and build the cpp application for task 3
	echo "uninstalling C++ app(Task3)"

	cd cpp/bin/
	make clean
	rm -r /usr/local/task-3/
	
	cd ../../
	echo "CPP app uninstalled"

	#the part of task 4 is here
	sudo systemctl disable distance-measurement-rpi.service
	rm /etc/systemd/system/distance-measurement-rpi.service
	
	echo "service uninstalled"


else
	if [[ $1 == -bash ]]; then
		echo "uninstalling bash app (Task2)"

		# copy shell scripts for HW initialization to /opt/
		rm /opt/hw_init.sh

		rm /opt/hw_deInit.sh

		# copy shell script for task 2 to /usr/local

		rm /usr/local/task-2/task2.sh

		echo "Script uninstalled"
	else
		if [[ $1 == -km ]]; then
			echo "installing kernel module (Task6)"

			cd kmodule/
			make
			mkdir /usr/local/task-6/
			rm /usr/local/task-6/

			echo "kernel module uninstalled"

		else
			echo "please choose which app you want to install (-cpp, -km or -bash as argument)"
			exit -1
		fi
	fi

fi

rm /usr/local/task-5/cpu-and-ram-tempfs-log.sh

sudo systemctl disable cpu-and-ram-tempfs-log.timer

rm /etc/systemd/system/cpu-and-ram-tempfs-log.timer

rm /etc/systemd/system/cpu-and-ram-tempfs-log.service
echo "CPU and RAM logging is uninstalled"

echo "install routine finished"

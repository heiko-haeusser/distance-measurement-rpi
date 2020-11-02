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

function rmFile {
	#arg1 = input file
	#arg2 = output file
	#echo copy files $1 to $2  > /dev/ttyS0

	if test -f $1; then
		echo rm $1
		sudo rm $1
	else
		echo file $1 does not exist
	fi
}

function rmFolder {
	#arg1 = folder to create
	
	if [ -d "$1" ]; then
		echo remove dir $1
		sudo rm -r $1
	else
		echo dir $1 does not exist
	fi
}

if [[ $1 == -cpp ]]; then
	#install and build the cpp application for task 3
	echo "uninstalling C++ app(Task3)"

	cd cpp/bin/
	make clean
	rmFolder /usr/local/task-3/
	
	cd ../../
	echo "CPP app uninstalled"

	#the part of task 4 is here
	if test -f "/etc/systemd/system/distance-measurement-rpi.service"; then
		sudo systemctl disable distance-measurement-rpi.service
	fi

	rmFile /etc/systemd/system/distance-measurement-rpi.service
	
	echo "service uninstalled"


else
	if [[ $1 == -bash ]]; then
		echo "uninstalling bash app (Task2)"

		# copy shell scripts for HW initialization to /opt/
		rmFile /opt/hw_init.sh

		rmFile /opt/hw_deInit.sh

		# copy shell script for task 2 to /usr/local

		rmFile /usr/local/task-2/task2.sh

		echo "Script uninstalled"
	else
		if [[ $1 == -km ]]; then
			echo "uninstalling kernel module (Task6)"

			rmFolder /usr/local/task-6/

			echo "kernel module uninstalled"

		else
			if [[ $1 == -task5 ]]; then		
				# Task 5 mount tempfs at /media/sensor_logs/ and story every 5s CPU and RAM load
				rmFolder /usr/local/task-5/

				if test -f "/etc/systemd/system/cpu-and-ram-tempfs-log.timer"; then
					sudo systemctl disable cpu-and-ram-tempfs-log.timer
					sudo systemctl disable cpu-and-ram-tempfs-log.service
				fi
				rmFile /etc/systemd/system/cpu-and-ram-tempfs-log.timer

				rmFile /etc/systemd/system/cpu-and-ram-tempfs-log.service
				echo "CPU and RAM logging is uninstalled"

			else
				echo "please choose which app you want to install (-cpp, -km, -bash or -task5 as argument)"
				exit -1
			fi
		fi
	fi

fi



echo "install routine finished"

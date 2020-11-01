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

function copyFiles {
	#arg1 = input file
	#arg2 = output file
	#echo copy files $1 to $2  > /dev/ttyS0

	if test -f $1; then
		echo cp $1 $2
		cp $1 $2
	else
		echo ERROR: $1 not found
		exit -1
	fi
}

echo "start install routine"

if [[ "$(whoami)" != root ]]; then
	echo "Only user root can run this script."
	exit -1
fi

if [[ $1 == -cpp ]]; then
	#install and build the cpp application for task 3
	echo "installing C++ app(Task3)"

	cd cpp/bin/
	make
	mkdir /usr/local/task-3/
	copyFiles distance-measurement-rpi /usr/local/task-3/

	cd ../../

	copyFiles services/distance-measurement-rpi.service /etc/systemd/system/distance-measurement-rpi.service
	sudo systemctl enable distance-measurement-rpi.service

else
	if [[ $1 == -bash ]]; then
		echo "installing bash app (Task2)"

		# copy shell scripts for HW initialization to /opt/
		sudo chmod +x shell/_bin/hw_init.sh
		copyFiles shell/_bin/hw_init.sh /opt/hw_init.sh

		sudo chmod +x shell/_bin/hw_deInit.sh
		copyFiles shell/_bin/hw_deInit.sh /opt/hw_deInit.sh

		# copy shell script for task 2 to /usr/local

		sudo chmod +x shell/_bin/task2.sh
		copyFiles shell/_bin/task2.sh /usr/local/task-2/task2.sh

		echo "Script for hw init is now available at: /opt/hw_init.sh"
		echo "Script for hw deinit is now available at: /opt/hw_deInit.sh"
		echo "Script for task2 is now available at: /usr/local/task-2/task2.sh"
	else
		if [[ $1 == -km ]]; then
			echo "installing kernel module (Task6)"

			cd kmodule/
			make
			mkdir /usr/local/task-6/
			copyFiles distance-measurement-rpi.ko /usr/local/task-6/

			echo "Script for task2 is now available at: /usr/local/task-6/distance-measurement-rpi.ko"

		else
			echo "please choose which app you want to install (-cpp or -bash as argument)"
			exit -1
		fi
	fi

fi

# Task 5 mount tempfs at /media/sensor_logs/ and story every 5s CPU and RAM load
sudo chmod +x log/cpu-and-ram-tempfs-log.sh
copyFiles log/cpu-and-ram-tempfs-log.sh /usr/local/task-5/cpu-and-ram-tempfs-log.sh

copyFiles log/cpu-and-ram-tempfs-log.timer /etc/systemd/system/cpu-and-ram-tempfs-log.timer
sudo systemctl enable cpu-and-ram-tempfs-log.timer

copyFiles log/cpu-and-ram-tempfs-log.service /etc/systemd/system/cpu-and-ram-tempfs-log.service
echo "CPU and RAM logging is now installed and active on reboot. (available at /media/sensor_logs/ram_and_cpu_load.txt)"

echo "install routine finished"

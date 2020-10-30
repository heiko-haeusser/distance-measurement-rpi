#!/bin/bash
# some custom magic
# board definitions:
# Button 	GPIO26 
# LED 		GPIO23
# Ultrasonic 
# Trigger	GPIO18
# Echo		GPIO24
#sleep 2

echo "############# hw deinit started #############" > /dev/ttyS0
 
# ****** uninitialize the GPIO parametrized at $1 ****** 
function deInitGPIO {
    # check if the gpio is already present in sys class, if not export it
    # echo "ls /sys/class/gpio | grep -i gpio$1" > /dev/ttyS0
    # ls /sys/class/gpio | grep -i gpio$1 > /dev/ttyS0

    if ls /sys/class/gpio | grep --quiet gpio$1; then
        echo GPIO$1 is now unexported > /dev/ttyS0
        echo $1 > /sys/class/gpio/unexport
    else
        echo GPIO$1 not available > /dev/ttyS0
    fi
}



# ****** initialize the GPIO13 to be an output (PU for Button), set to high ****** 
deInitGPIO 13

# ****** initialize the GPIO26 to be an input (Button) ****** 
deInitGPIO 26

# ****** initialize the GPIO23 to be an output (LED), set to high to have feedback that init finished successfully ****** 
deInitGPIO 23

# ****** initialize the GPIO18 to be an output (Trigger for ultrasonic sensor), set to low ****** 
deInitGPIO 18

# ****** initialize the GPIO24 to be an input (Echo from ultrasonic sensor), set to high ****** 
deInitGPIO 24

echo "############# hw deinit finished #############" > /dev/ttyS0

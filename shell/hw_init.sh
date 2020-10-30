#!/bin/bash
# some custom magic
# board definitions:
# Button 	GPIO26 
# LED 		GPIO23
# Ultrasonic 
# Trigger	GPIO18
# Echo		GPIO24
#sleep 2

echo "############# hw init V0.1 started #############" > /dev/ttyS0

# ****** initialize the GPIO parametrized at $1 to be an input ****** 
function initGPI {    

    initGPIO $1
    # check if the gpi is already configured as input, if not initialize it
    # echo "grep i /sys/class/gpio/gpio$1/direction" > /dev/ttyS0
    # grep i /sys/class/gpio/gpio$1/direction > /dev/ttyS0

    if grep --quiet i /sys/class/gpio/gpio$1/direction; then
        echo GPIO$1 aready configured as input > /dev/ttyS0
    else
        echo configure GPIO$1 as GPI > /dev/ttyS0
        echo "in" > /sys/class/gpio/gpio$1/direction
    fi
} 

# ****** initialize the GPIO parametrized at $1 to be an output ****** 
function initGPO {    

    initGPIO $1
    # check if the gpi is already configured as input, if not initialize it
    # echo "grep out /sys/class/gpio/gpio$1/direction" > /dev/ttyS0
    # grep out /sys/class/gpio/gpio$1/direction > /dev/ttyS0

    if grep --quiet out /sys/class/gpio/gpio$1/direction; then
        echo GPIO$1 aready configured as output > /dev/ttyS0
    else
        echo configure GPIO$1 as GPO > /dev/ttyS0
        echo "out" > /sys/class/gpio/gpio$1/direction
    fi
} 

# ****** initialize the GPIO parametrized at $1 to be an GPIO ****** 
function initGPIO {
    # check if the gpio is already present in sys class, if not export it
    # echo "ls /sys/class/gpio | grep -i gpio$1" > /dev/ttyS0
    # ls /sys/class/gpio | grep -i gpio$1 > /dev/ttyS0

    if ls /sys/class/gpio | grep --quiet gpio$1; then
        echo GPIO$1 already exists > /dev/ttyS0
    else
        echo create GPIO$1 > /dev/ttyS0
        echo $1 > /sys/class/gpio/export
    fi
}



# ****** initialize the GPIO13 to be an output (PU for Button), set to high ****** 
initGPO 13
echo 1 > /sys/class/gpio/gpio13/value

# ****** initialize the GPIO26 to be an input (Button) ****** 
initGPI 26

# ****** initialize the GPIO23 to be an output (LED), set to high to have feedback that init finished successfully ****** 
initGPO 23
echo 1 > /sys/class/gpio/gpio23/value

# ****** initialize the GPIO18 to be an output (Trigger for ultrasonic sensor), set to low ****** 
initGPO 18
echo 0 > /sys/class/gpio/gpio18/value

# ****** initialize the GPIO24 to be an input (Echo from ultrasonic sensor), set to high ****** 
initGPI 24

echo "############# hw init ended #############" > /dev/ttyS0

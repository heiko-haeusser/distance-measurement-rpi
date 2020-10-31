//============================================================================
// Name        : parking-sensor.cpp
// Author      : Heiko Haeusser
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <chrono>
#include <thread>
#include "Gpio_Manager.h"
#include "Custom_Gpi.h"
#include "UltrasonicSensor.h"
#include "PDC.h"

//using namespace std;
using namespace Custom_Gpio;
using namespace Parking_System;


int main() {
	if (geteuid() == 0) {
		std::cout << "running as: root, continue... \n";
	} else {
		std::cout << "running as: user, abort...\n";
		std::cout << "Only user root can run this program\n";
		return (-1);
	}

	sleep(1);

	std::cout << "!!! CPP Application to perform distance measurement !!!\n";
	
	Gpio_Manager gpioMgr;
	Ultrasonic_Sensor us(gpioMgr);
	us.setBlinkInterval(1000);

	gpioMgr.initGpios();
	gpioMgr.setBtnPullup(true);

	PDC myPDC(gpioMgr, us);

	std::thread t1(&PDC::toggleLED, &myPDC); // start flashing the LED in a separate thread
	std::thread t2(&Ultrasonic_Sensor::performContinousMeasurement, &us);  // start reading the distance in another thread

	t1.join();
	t2.join();
	
	gpioMgr.deinitGpios();
	return 0;

}

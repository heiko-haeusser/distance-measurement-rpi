/*
 * PDC.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#include "PDC.h"
#include <iostream>

namespace Parking_System {

PDC::PDC(Gpio_Manager& gpioMgr_, Ultrasonic_Sensor& us_) {
	// TODO Auto-generated constructor stub
	this->gpioMgr = &gpioMgr_;
	this->us = &us_;
}

PDC::~PDC() {
	// TODO Auto-generated destructor stub
}
//
//PDC::PDC(const PDC &other) {
//	// TODO Auto-generated constructor stub
//
//}

void PDC::toggleLED(void) {
	int blinkInterval = 500;
	std::unique_lock<std::mutex> myLock(mu1);
	myLock.unlock();
	while (true) {

		myLock.lock();
		gpioMgr->setLED(true);
		myLock.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(blinkInterval));	//usleep(500000); //give some time to check if the led works

		myLock.lock();
		gpioMgr->setLED(false);
		myLock.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(blinkInterval));	//usleep(500000); //give some time to check if the led works
		if (gpioMgr->readBtnState() == true) {
            myLock.lock();
			std::cout << "button pressed, exit PDC: " << blinkInterval;
            myLock.unlock();
			break;
		}
		blinkInterval = us->getBlinkInterval();

	}
}

} /* namespace Parking_System */

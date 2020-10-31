/*
 * UltrasonicSensor.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#include "UltrasonicSensor.h"
#include <unistd.h>
#include <iostream>
#include <thread>

namespace Parking_System {

using namespace Parking_System;

Ultrasonic_Sensor::Ultrasonic_Sensor() {
	// TODO Auto-generated constructor stub

}

Ultrasonic_Sensor::Ultrasonic_Sensor(Gpio_Manager& gpioMgr) {
	this->gpioMgr = &gpioMgr;
	blinkInterval = 500;
	// TODO Auto-generated constructor stub

}

Ultrasonic_Sensor::~Ultrasonic_Sensor() {
	// TODO Auto-generated destructor stub
}

// Ultrasonic_Sensor::Ultrasonic_Sensor(const Ultrasonic_Sensor &other) {
// 	// TODO Auto-generated constructor stub

// }

// Ultrasonic_Sensor::Ultrasonic_Sensor(Ultrasonic_Sensor &&other) {
// 	// TODO Auto-generated constructor stub

// }

Ultrasonic_Sensor& Ultrasonic_Sensor::operator=(const Ultrasonic_Sensor &other) {
	// TODO Auto-generated method stub
	return *this;
}

// Ultrasonic_Sensor& Ultrasonic_Sensor::operator=(Ultrasonic_Sensor &&other) {
// 	// TODO Auto-generated method stub

// }

void Ultrasonic_Sensor::initiateTrigger(void) {

	gpioMgr->setTrigger(true);
	auto start = std::chrono::system_clock::now();

	std::this_thread::sleep_for(std::chrono::microseconds(15));	//usleep(500000); //give some time to check if the led works

	auto end = std::chrono::system_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	gpioMgr->setTrigger(false);
	//std::cout << "delay trigger: " << elapsed << '\n';

//	int delay = (stopEchoCapture.tv_sec - startEchoCapture.tv_sec)* 1e-9;
//
//	delay += (stopEchoCapture.tv_nsec - startEchoCapture.tv_nsec);
//	delay = delay/1000;
	//std::cout << "delay trigger: " << delay << "\n";
}

int Ultrasonic_Sensor::captureEcho(void) {
	while (gpioMgr->readEchoState() == false) {}
	auto start = std::chrono::system_clock::now();
	int timeout = 38000; //38ms with 1us delay between capture
	while (gpioMgr->readEchoState() == true) {
		std::this_thread::sleep_for(std::chrono::microseconds(1));	//usleep(500000); //give some time to check if the led works

		if (timeout-- <= 0) {
			std::cout << "Timeout on measurement - no obstacle detected";
			return (-1);
		}
	}
	auto end = std::chrono::system_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

//	std::cout << "delay: " << elapsed << "\t\t";
	duration = elapsed;
	return elapsed;
}

double Ultrasonic_Sensor::calculateDistance() {
	distanceCm = (duration*1e-6 * 34300) / 2;
	distanceM = distanceCm /100.0;
	return distanceCm;
}


void Ultrasonic_Sensor::performMeasurement(void) {
	initiateTrigger();
	captureEcho();
	calculateDistance();
}

void Ultrasonic_Sensor::performContinousMeasurement(void) {
	std::unique_lock<std::mutex> myLock(mu2);
	myLock.unlock();

	while (gpioMgr->readBtnState() == false) {
		this->performMeasurement();
		myLock.lock();
		std::cout << "Status: " << this->checkDistance(this->getDistanceCm()) << "\t\tdistance[cm]: " << this->getDistanceCm() << "\t\t" << "distance[m]: " << this->getDistanceM() << "\n";
		myLock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));	//usleep(500000); //give some time to check if the led works
	}
}


std::string Ultrasonic_Sensor::checkDistance(int distance) {
	if (distance < 30) {
		setBlinkInterval(70);
		return "STOP";
	} else if (distance <= 100) {
		setBlinkInterval(250);
		return "WARNING";
	} else if (distance > 100) {
		setBlinkInterval(500);
		return "OK";
	}
	setBlinkInterval(70);

	return "ERROR";
}

int Ultrasonic_Sensor::getDistanceCm() const {
	return distanceCm;
}

void Ultrasonic_Sensor::setDistanceCm(int distanceCm) {
	this->distanceCm = distanceCm;
}

double Ultrasonic_Sensor::getDistanceM() const {
	return distanceM;
}

void Ultrasonic_Sensor::setDistanceM(double distanceM) {
	this->distanceM = distanceM;
}

int Ultrasonic_Sensor::getDuration() const {
	return duration;
}

void Ultrasonic_Sensor::setDuration(int duration) {
	this->duration = duration;
}

const Gpio_Manager& Ultrasonic_Sensor::getGpioMgr() const {
	return *gpioMgr;
}

void Ultrasonic_Sensor::setGpioMgr(Gpio_Manager &gpioMgr) {
	this->gpioMgr = &gpioMgr;
}

int Ultrasonic_Sensor::getBlinkInterval() {
	std::lock_guard<std::mutex> myLockGuard(mu1);
	return this->blinkInterval;
}

void Ultrasonic_Sensor::setBlinkInterval(int blinkInterval) {
	std::lock_guard<std::mutex> myLockGuard(mu1);
	// std::cout << "set blink interval: " << blinkInterval << "\n" ;
	this->blinkInterval = blinkInterval;
}
} /* namespace Parking_System */

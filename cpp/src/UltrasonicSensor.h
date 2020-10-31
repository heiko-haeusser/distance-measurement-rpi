/*
 * UltrasonicSensor.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

#include "Gpio_Manager.h"
#include <sys/time.h>
#include <unistd.h>
#include <string>
#include <mutex>

#include <thread>
#include <mutex>

namespace Parking_System {

using namespace Parking_System;

class Ultrasonic_Sensor {
private:
	Gpio_Manager* gpioMgr;
	struct timespec startEchoCapture;
    struct timespec stopEchoCapture;
	int duration;
	int distanceCm;
	double distanceM;
	int blinkInterval;
	std::mutex mu1; // which will guard interval value
	std::mutex mu2; // which will guard interval value
public:
	Ultrasonic_Sensor();
	Ultrasonic_Sensor(Gpio_Manager& gpioMgr);
	virtual ~Ultrasonic_Sensor();
	// Ultrasonic_Sensor(const Ultrasonic_Sensor &other);
	// Ultrasonic_Sensor(Ultrasonic_Sensor &&other);
	Ultrasonic_Sensor& operator=(const Ultrasonic_Sensor &other);
	// Ultrasonic_Sensor& operator=(Ultrasonic_Sensor &&other);

	void initiateTrigger(void);
	int captureEcho(void);
	double calculateDistance(void);
	void performMeasurement(void);
	void performContinousMeasurement(void);
	std::string checkDistance(int distance);
	int getDistanceCm() const;
	void setDistanceCm(int distanceCm);
	double getDistanceM() const;
	void setDistanceM(double distanceM);
	int getDuration() const;
	void setDuration(int duration);
	const Gpio_Manager& getGpioMgr() const;
	void setGpioMgr(Gpio_Manager &gpioMgr);
	int getBlinkInterval();
	void setBlinkInterval(int blinkInterval);
};

} /* namespace Parking_System */

#endif /* ULTRASONICSENSOR_H_ */

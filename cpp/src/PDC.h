/*
 * PDC.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef PDC_H_
#define PDC_H_
#include "UltrasonicSensor.h"
#include <mutex>

namespace Parking_System {

class PDC {
private:
	int distance=0;
	Ultrasonic_Sensor* us;
	Gpio_Manager* gpioMgr;
	std::mutex mu1; // which will guard interval value

public:
	PDC(Gpio_Manager& gpioMgr, Ultrasonic_Sensor& us);
	virtual ~PDC();

	void toggleLED(void);

};

} /* namespace Parking_System */

#endif /* PDC_H_ */

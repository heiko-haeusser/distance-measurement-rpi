/*
 * PDC.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef PDC_H_
#define PDC_H_
#include "UltrasonicSensor.h"

namespace Parking_System {

class PDC {
private:
	int distance=0;
	Ultrasonic_Sensor sensor;
public:
	PDC();
	virtual ~PDC();
	// PDC(const PDC &other);
	// PDC(PDC &&other);
	// PDC& operator=(const PDC &other);
	// PDC& operator=(PDC &&other);
};

} /* namespace Parking_System */

#endif /* PDC_H_ */

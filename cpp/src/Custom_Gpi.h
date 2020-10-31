/*
 * Custom_Gpi.h
 *
 *  Created on: 30 Oct 2020
 *      Author: X1_AV
 */

#ifndef Custom_Gpi_H_
#define Custom_Gpi_H_

#include "Custom_Gpio.h"

namespace Custom_Gpio {

class Custom_Gpi: public Custom_Gpio::Custom_Gpio {
private:
	int gpio_value = gpio_val_low;

public:
	Custom_Gpi();
	Custom_Gpi(int _gpio_number, std::string _gpio_direction); //user defined constructor

	virtual ~Custom_Gpi();
	Custom_Gpi(const Custom_Gpi &other);
	// Custom_Gpi(Custom_Gpi &&other);
	// Custom_Gpi& operator=(const Custom_Gpi &other);
	// Custom_Gpi& operator=(Custom_Gpi &&other);

	int setupGpio(void);
	int getGpioValue();
};

} /* namespace Custom_Gpio */

#endif /* Custom_Gpi_H_ */

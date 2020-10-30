/*
 * Custom_Gpo.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef Custom_Gpo_H_
#define Custom_Gpo_H_

#include "Custom_Gpio.h"

namespace Gpio_Setup {

class Custom_Gpo: public Gpio_Setup::Custom_Gpio {
private:
	int gpio_value = gpio_val_low;

public:
	Custom_Gpo();
	Custom_Gpo(int _gpio_number, std::string _gpio_direction, int _gpio_value); //user defined constructor

	virtual ~Custom_Gpo();
	Custom_Gpo(const Custom_Gpo &other);
	Custom_Gpo(Custom_Gpo &&other);
	Custom_Gpo& operator=(const Custom_Gpo &other);
	Custom_Gpo& operator=(Custom_Gpo &&other);

	int setupGpio(void);
	int setGpioValue(int value);
};

} /* namespace Custom_Gpio */

#endif /* Custom_Gpo_H_ */

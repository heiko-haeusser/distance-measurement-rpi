/*
 * CustomGpio.h
 *
 *  Created on: 30 Oct 2020
 *      Author: X1_AV
 */

#ifndef CUSTOM_GPIO_H_
#define CUSTOM_GPIO_H_

#include <string>
namespace Gpio_Setup {

static std::string gpio_dir_input="in";
static std::string gpio_dir_output="out";
static int gpio_val_low=0;
static int gpio_val_high=1;
class Custom_Gpio {
protected:
	int gpio_number = 0;
	std::string gpio_direction = gpio_dir_input;
public:
	Custom_Gpio(); //constructor
	Custom_Gpio(int _gpio_number, std::string _gpio_direction); //user defined constructor
	virtual ~Custom_Gpio(); //distructor
	Custom_Gpio(const Custom_Gpio &other); //copy constructor
	Custom_Gpio(Custom_Gpio &&other); //move constructor
	Custom_Gpio& operator=(const Custom_Gpio &other);
	Custom_Gpio& operator=(Custom_Gpio &&other);

	virtual int setupGpio(void);
	int exportGpio(void);
	int setGpioDir(void);
	int unexportGpio(void);
};

} /* namespace Gpio_Setup */

#endif /* CUSTOM_GPIO_H_ */

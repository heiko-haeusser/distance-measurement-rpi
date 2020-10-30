/*
 * Custom_Gpo.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#include "Custom_Gpo.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Gpio_Setup {

Custom_Gpo::Custom_Gpo() {
	// TODO Auto-generated constructor stub

}

Custom_Gpo::Custom_Gpo(int _gpio_number, std::string _gpio_direction, int _gpio_value) :
		Custom_Gpio(_gpio_number, _gpio_direction), gpio_value(_gpio_value) {

	// TODO Auto-generated constructor stub
}

Custom_Gpo::~Custom_Gpo() {
	// TODO Auto-generated destructor stub
}

Custom_Gpo::Custom_Gpo(const Custom_Gpo &other) {
	// TODO Auto-generated constructor stub

}

Custom_Gpo::Custom_Gpo(Custom_Gpo &&other) {
	// TODO Auto-generated constructor stub

}

Custom_Gpo& Custom_Gpo::operator=(const Custom_Gpo &other) {
	// TODO Auto-generated method stub
	Custom_Gpo copy_instance = Custom_Gpo(other);
	return copy_instance;
}

Custom_Gpo& Custom_Gpo::operator=(Custom_Gpo &&other) {
	// TODO Auto-generated method stub
	Custom_Gpo copy_instance = std::move(other);
	other.gpio_direction = gpio_dir_output; //reset to default
	other.gpio_number = 0; //reset to default
	return copy_instance;
}

int Custom_Gpo::setupGpio(void) {
	if (exportGpio()==0) {
		if (setGpioDir()==0) {
			if (setGpioValue(gpio_value)==0) {
				std::cout << "GPIO init successful\n";
				return 0;

			}
		}
	}
	std::cout << "GPIO init failed\n";

	return (-1);
}

int Custom_Gpo::setGpioValue(int value) {
	gpio_value = value;
	std::fstream gpioValueFile;
	std::stringstream filename;

	filename << "/sys/class/gpio/gpio" << gpio_number << "/value";

	gpioValueFile.open(filename.str(), std::fstream::out);
	//ofstream exportgpio(export_str.c_str());
	if (gpioValueFile.is_open() > 0) {
		gpioValueFile << gpio_value;

		gpioValueFile.close();
		std::cout << "GPIO value set successful\n";

	} else {
		std::cout << "trigger: GPIO value set failed: " << filename.str() << "\n";
		return (-1);
	}

	return (0);
}

} /* namespace Custom_Gpio */

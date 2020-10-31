/*
 * CustomGpio.cpp
 *
 *  Created on: 30 Oct 2020
 *      Author: X1_AV
 */

#include "Custom_Gpio.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <exception>
#include <cassert>
#include <initializer_list>
#include <utility>
#include <vector>
#include <algorithm>

namespace Custom_Gpio {

Custom_Gpio::Custom_Gpio() {
	// TODO Auto-generated constructor stub
	gpio_number = 0;
	gpio_direction = gpio_dir_input;
}

Custom_Gpio::Custom_Gpio(int _gpio_number, std::string _gpio_direction) :
		gpio_number(_gpio_number), gpio_direction(_gpio_direction) {

}

Custom_Gpio::~Custom_Gpio() {
	// TODO Auto-generated destructor stub
}

// Custom_Gpio::Custom_Gpio(const Custom_Gpio &other) :
// 		gpio_number(other.gpio_number), gpio_direction(other.gpio_direction) { // copy constructor
// 	// TODO Auto-generated constructor stub

// }

// Custom_Gpio::Custom_Gpio(Custom_Gpio &&other) { // move constructor
// 	// TODO Auto-generated constructor stub
// 	this->gpio_number = std::move(other.gpio_number);
// 	this->gpio_direction = std::move(other.gpio_direction);
// }

// Custom_Gpio& Custom_Gpio::operator=(const Custom_Gpio &other) { // copy assignment
// 	// TODO Auto-generated method stub
// 	Custom_Gpio copy_instance = Custom_Gpio(other);
// 	return copy_instance;
// }

// Custom_Gpio& Custom_Gpio::operator=(Custom_Gpio &&other) { //move assignment
// 	// TODO Auto-generated method stub
// 	Custom_Gpio copy_instance = std::move(other);
// 	other.gpio_direction = gpio_dir_input; //reset to default
// 	other.gpio_number = 0; //reset to default
// 	return copy_instance;
// }

int Custom_Gpio::setupGpio(void) {
	std::cout << "this should never be called";
	return (-1);
}

int Custom_Gpio::exportGpio(void) {
	std::fstream gpioExpFile;
	gpioExpFile.open("/sys/class/gpio/export", std::fstream::out);
	//ofstream exportgpio(export_str.c_str());
	if (gpioExpFile.is_open() > 0) {
		gpioExpFile << gpio_number;
		gpioExpFile.close();
		// std::cout << "GPIO export successful\n";
	} else {
		std::cout << "GPIO export failed\n";
		return (-1);
	}
	return (0);
}
//	std::string
//expGPIO =
int Custom_Gpio::unexportGpio(void) {
	std::fstream gpioExpFile;
		gpioExpFile.open("/sys/class/gpio/unexport", std::fstream::out);
		//ofstream exportgpio(export_str.c_str());
		if (gpioExpFile.is_open() > 0) {
			gpioExpFile << gpio_number;
			gpioExpFile.close();
			// std::cout << "GPIO unexport successful: GPIO" << gpio_number <<"\n";
		} else {
			std::cout << "GPIO unexport failed: GPIO" << gpio_number <<"\n";
			return (-1);
		}
		return (0);
	//sys/class/gpio/unexport
}

int Custom_Gpio::setGpioDir(void) {
	std::fstream gpioDirFile;
	std::stringstream gpioDirFilestream;

	std::stringstream filename;
	filename << "/sys/class/gpio/gpio" << gpio_number << "/direction";
	gpioDirFile.open(filename.str(), std::fstream::out);
	if (gpioDirFile.is_open() > 0) {
		gpioDirFilestream << gpio_direction;
		gpioDirFile << gpioDirFilestream.str();
		gpioDirFile.close();
		// std::cout << "GPIO dir set successful\n";

	} else {
		std::cout << "GPIO dir set failed: " << filename.str() << "\n";
		return (-1);
	}
	return (0);
}
}

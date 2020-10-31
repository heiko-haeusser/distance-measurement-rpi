/*
 * Custom_Gpi.cpp
 *
 *  Created on: 30 Oct 2020
 *      Author: X1_AV
 */

#include "Custom_Gpi.h"

#include <iostream>
#include <fstream>
#include <sstream>
//#include <memory>
//#include <exception>
//#include <cassert>
//#include <initializer_list>
//#include <utility>
#include <algorithm>

namespace Custom_Gpio {

Custom_Gpi::Custom_Gpi() {
	// TODO Auto-generated constructor stub

}

Custom_Gpi::Custom_Gpi(int _gpio_number, std::string _gpio_direction) :
		Custom_Gpio(_gpio_number, _gpio_direction) {

	// TODO Auto-generated constructor stub
}

Custom_Gpi::~Custom_Gpi() {
	// TODO Auto-generated destructor stub
}

// Custom_Gpi::Custom_Gpi(const Custom_Gpi &other) {
// 	// TODO Auto-generated constructor stub

// }

// Custom_Gpi::Custom_Gpi(Custom_Gpi &&other) {
// 	// TODO Auto-generated constructor stub

// }

// Custom_Gpi& Custom_Gpi::operator=(const Custom_Gpi &other) {
// 	// TODO Auto-generated method stub
// 	Custom_Gpi copy_instance = Custom_Gpi(other);
// 	return copy_instance;
// }

// Custom_Gpi& Custom_Gpi::operator=(Custom_Gpi &&other) {
// 	// TODO Auto-generated method stub
// 	Custom_Gpi copy_instance = std::move(other);
// 	other.gpio_direction = gpio_dir_input; //reset to default
// 	other.gpio_number = 0; //reset to default
// 	return copy_instance;
// }


int Custom_Gpi::getGpioValue() {
	std::fstream gpioValueFile;
	std::stringstream gpioValueFilestream;

	std::stringstream filename;
	filename << "/sys/class/gpio/gpio" << gpio_number << "/value";
	gpioValueFile.open(filename.str(), std::fstream::in);

	char binData = 0;
	//ofstream exportgpio(export_str.c_str());
	if (gpioValueFile.is_open() > 0) {

		gpioValueFile.clear();
		gpioValueFile.seekg(0, std::ios::beg);
		gpioValueFile.read(&binData, 1);
		// gpioValueFile >> gpioValueFilestream;
		

		int state = (int)binData;
		// gpioValueFilestream >> state;
		//std::cout << "GPIO " << gpio_number << "  read " << state << "\n";
		// std::cout << filename.str() << " GPIO " << gpio_number << "  read " << binData << " "<< state <<"\n";

		gpioValueFile.close();

		if (state == '0') {
			gpio_value = gpio_val_low;
		} else if (state == '1') {
			gpio_value = gpio_val_high;
			// std::cout << filename.str() << " GPIO " << gpio_number << "  read " << binData << "\n";
		} else if (state == 0) {
			std::cout << "wrong gpio value read " << state << "\n";
			return (-1);
		}

		// std::cout << "GPIO value read successful\n";

	} else {
		std::cout << "Custom_Gpi: GPIO value read failed. GPIO: " << gpio_number << "\n";
		return (-1);
	}


	return gpio_value;
}

int Custom_Gpi::setupGpio() {
	if (exportGpio()==0) {
		if (setGpioDir()==0) {
			// std::cout << "GPIO init successful\n";
			return 0;
		}
	}
	std::cout << "GPIO init failed\n";

	return (-1);

}


} /* namespace Custom_Gpio */

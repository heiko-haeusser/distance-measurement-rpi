//============================================================================
// Name        : parking-sensor.cpp
// Author      : Heiko Haeusser
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>
#include <iostream>
#include <vector>
#include "Gpio_Manager.h"
#include "Custom_Gpi.h"

//using namespace std;
using namespace Gpio_Setup;
using namespace Parking_System;

int main() {
	if(geteuid()==0){
		std::cout << "running as: root, continue... \n";
	} else {
		std::cout << "running as: user, abort...\n";
		std::cout << "Only user root can run this program\n";
		return (-1);
	}

	// Custom_Gpo test(23,"out",1);
	// test.setupGpio();
	std::cout << "!!! CPP Application to perform distance measurement !!!\n";
	std::vector<int> vItems;
	// vItems.push_back(2);
	// vItems.push_back(3);
	// std::cout << vItems.at(vItems.size()-1);
	
	Gpio_Manager gpioMgr;

	gpioMgr.initGpios();
	gpioMgr.deinitGpios();
	return 0;

}

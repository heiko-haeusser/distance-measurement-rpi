/*
 * Gpio_Manager.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#include "Gpio_Manager.h"

namespace Parking_System {

	
// static int gpio_btn = 26;
// static int gpio_puBtn = 13;
// static int gpio_LED = 23;
// static int gpio_us_trig = 18;
// static int gpio_us_echo = 24;


Gpio_Manager::Gpio_Manager() : 
	button(Custom_Gpio::Custom_Gpi(gpio_btn, Custom_Gpio::gpio_dir_input)), \
	puBtn(Custom_Gpio::Custom_Gpo(gpio_puBtn, Custom_Gpio::gpio_dir_output, Custom_Gpio::gpio_val_low)), \
	led(Custom_Gpio::Custom_Gpo(gpio_LED, Custom_Gpio::gpio_dir_output, Custom_Gpio::gpio_val_low)),  \
	us_trig(Custom_Gpio::Custom_Gpo(gpio_us_trig, Custom_Gpio::gpio_dir_output, Custom_Gpio::gpio_val_low)), \
	us_echo(Custom_Gpio::Custom_Gpi(gpio_us_echo, Custom_Gpio::gpio_dir_input)) {
	
	// gpioList.push_back(button);
	// gpioList.push_back(puBtn);
	// gpioList.push_back(led);
	// gpioList.push_back(us_trig);
	// gpioList.push_back(us_echo);
}

Gpio_Manager::~Gpio_Manager() {
	// TODO Auto-generated destructor stub
}

Gpio_Manager::Gpio_Manager(const Gpio_Manager &other) {
	// TODO Auto-generated constructor stub

}

// Gpio_Manager::Gpio_Manager(Gpio_Manager &&other) {
// 	// TODO Auto-generated constructor stub

// }

Gpio_Manager& Gpio_Manager::operator=(const Gpio_Manager &other) {
	// TODO Auto-generated method stub
	return *this;
}

//Gpio_Manager& Gpio_Manager::operator=(Gpio_Manager &&other) {
//	// TODO Auto-generated method stub
//
//}


void Gpio_Manager::initGpios(void) {
	puBtn.setupGpio();
	button.setupGpio();
	led.setupGpio();
	us_trig.setupGpio();
	us_echo.setupGpio();
}

void Gpio_Manager::deinitGpios(void) {
	puBtn.unexportGpio();
	button.unexportGpio();
	led.unexportGpio();
	us_trig.unexportGpio();
	us_echo.unexportGpio();
}

void Gpio_Manager::setLED(bool val) {
	if(val)
	{
		led.setGpioValue(Custom_Gpio::gpio_val_high);
	} else
	{
		led.setGpioValue(Custom_Gpio::gpio_val_low);
	}
}

void Gpio_Manager::setTrigger(bool val) {
	if(val)
	{
		us_trig.setGpioValue(Custom_Gpio::gpio_val_high);
	} else
	{
		us_trig.setGpioValue(Custom_Gpio::gpio_val_low);
	}
}

void Gpio_Manager::setBtnPullup(bool val) {
	if(val)
	{
		puBtn.setGpioValue(Custom_Gpio::gpio_val_high);
	} else
	{
		puBtn.setGpioValue(Custom_Gpio::gpio_val_low);
	}
}

bool Gpio_Manager::readBtnState(void) {
	std::lock_guard<std::mutex> myLockGuard(mu1);
	if(button.getGpioValue()==Custom_Gpio::gpio_val_high)
		return true;
	
	return false;
}

bool Gpio_Manager::readEchoState(void) {
	if(us_echo.getGpioValue()==Custom_Gpio::gpio_val_high)
		return true;
	
	return false;
}

} /* namespace CR */

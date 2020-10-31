/*
 * Gpio_Manager.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef GPIOMANAGER_H_
#define GPIOMANAGER_H_

#include <vector>
#include <thread>
#include <mutex>
#include "Custom_Gpo.h"
#include "Custom_Gpi.h"

namespace Parking_System {

//using namespace std;
// using namespace Gpio_Setup;

static int gpio_btn=26;
static int gpio_puBtn=13;
static int gpio_LED=23;
static int gpio_us_trig=18;
static int gpio_us_echo=24;

//# Button 	GPIO26
//# Button_PU	GPIO13
//# LED 		GPIO23
//# Ultrasonic
//# Trigger	GPIO18
//# Echo		GPIO24
class Gpio_Manager {
private:
	Custom_Gpio::Custom_Gpi button;
	Custom_Gpio::Custom_Gpo test;
	Custom_Gpio::Custom_Gpo puBtn;
	Custom_Gpio::Custom_Gpo led;
	Custom_Gpio::Custom_Gpo us_trig;
	Custom_Gpio::Custom_Gpi us_echo;
	std::vector<Custom_Gpio::Custom_Gpio>gpioList;
	std::mutex mu1; // which will guard interval value
public:
	Gpio_Manager();
	virtual ~Gpio_Manager();
	Gpio_Manager(const Gpio_Manager &other);
	// Gpio_Manager(Gpio_Manager &&other);
	Gpio_Manager& operator=(const Gpio_Manager &other); //CHECKME: is this really necessary?
//	Gpio_Manager& operator=(Gpio_Manager &&other); //no need for that?

	void initGpios(void);
	void deinitGpios(void);

	void setLED(bool val);
	void setTrigger(bool val);
	void setBtnPullup(bool val);
	bool readBtnState(void);
	bool readEchoState(void);
};

} /* namespace CR */

#endif /* GPIOMANAGER_H_ */

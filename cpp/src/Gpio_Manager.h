/*
 * Gpio_Manager.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef GPIOMANAGER_H_
#define GPIOMANAGER_H_

#include "Custom_Gpo.h"
#include "Custom_Gpi.h"
#include <vector>

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
	Gpio_Setup::Custom_Gpi button;
	Gpio_Setup::Custom_Gpo test;
	Gpio_Setup::Custom_Gpo puBtn;
	Gpio_Setup::Custom_Gpo led;
	Gpio_Setup::Custom_Gpo us_trig;
	Gpio_Setup::Custom_Gpi us_echo;
	std::vector<Gpio_Setup::Custom_Gpio>gpioList;
public:
	Gpio_Manager();
	virtual ~Gpio_Manager();
	Gpio_Manager(const Gpio_Manager &other);
	Gpio_Manager(Gpio_Manager &&other);
//	Gpio_Manager& operator=(const Gpio_Manager &other); //no need for that?
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

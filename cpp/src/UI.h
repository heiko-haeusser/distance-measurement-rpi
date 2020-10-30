/*
 * UI.h
 *
 *  Created on: 29 Oct 2020
 *      Author: X1_AV
 */

#ifndef UI_H_
#define UI_H_

namespace Parking_System {

class UI {
public:
	UI();
	virtual ~UI();
	UI(const UI &other);
	UI(UI &&other);
	UI& operator=(const UI &other);
	UI& operator=(UI &&other);
};

} /* namespace Parking_System */

#endif /* UI_H_ */

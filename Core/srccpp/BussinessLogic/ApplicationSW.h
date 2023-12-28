/*
 * LpdcLogic.h
 *
 *  Created on: 04-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_BUSSINESSLOGIC_APPLICATIONSW_H_
#define SRCCPP_BUSSINESSLOGIC_APPLICATIONSW_H_


#include "main.h"

class Loadmeasure {
public:
	Loadmeasure();
	virtual ~Loadmeasure();
	void run();
	GPIO_PinState readStartbutton;
	GPIO_PinState readEndbutton;


private:
	uint32_t calculationCarbonWeight();
	uint32_t calculationSilicaWeight();
	uint32_t calculationManganeaseWeight();
	uint32_t calculationCopperWeight();
	uint32_t calculationTinWeight();
	uint32_t calculationZincWeight();
	void inputBasedTrigger();
};

#endif /* SRCCPP_BUSSINESSLOGIC_APPLICATIONSW_H_ */

/*
 * Faulthandling.h
 *
 *  Created on: Jan 17, 2024
 *      Author: MKS
 */

#ifndef SRCCPP_FAULTHANDLING_FAULTHANDLING_H_
#define SRCCPP_FAULTHANDLING_FAULTHANDLING_H_
#include "main.h"
class Faulthandling {
public:
	Faulthandling();
	virtual ~Faulthandling();
	void run();
private:
	void communicationBinFault();
	uint8_t bin1_comm_count,bin2_comm_count,bin3_comm_count,bin4_comm_count,bin5_comm_count,bin6_comm_count;
};

#endif /* SRCCPP_FAULTHANDLING_FAULTHANDLING_H_ */

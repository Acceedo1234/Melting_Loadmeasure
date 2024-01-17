/*
 * Faulthandling.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: MKS
 */

#include <FaultHandling/Faulthandling.h>
#include "baselib.h"

#define Bin1Pos 0
#define Bin2Pos 1
#define Bin3Pos 2
#define Bin4Pos 3
#define Bin5Pos 4
#define Bin6Pos 5

#define FaultTolerance 10

extern uint8_t statusBincom;
uint8_t statusBincom_Fault;

Faulthandling::Faulthandling() {
	// TODO Auto-generated constructor stub

}

Faulthandling::~Faulthandling() {
	// TODO Auto-generated destructor stub
}

void Faulthandling::run(){
	communicationBinFault();
}

void Faulthandling::communicationBinFault(){
	if(Readbit(statusBincom,Bin1Pos))
	{
		statusBincom = clearbit(statusBincom,Bin1Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin1Pos);
		bin1_comm_count = 0;
	}
	else
	{
		if(++bin1_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin1Pos);
			bin1_comm_count = FaultTolerance;
		}
	}
	if(Readbit(statusBincom,Bin2Pos))
	{
		statusBincom = clearbit(statusBincom,Bin2Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin2Pos);
		bin2_comm_count = 0;
	}
	else
	{
		if(++bin2_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin2Pos);
			bin2_comm_count = FaultTolerance;
		}
	}
	if(Readbit(statusBincom,Bin3Pos))
	{
		statusBincom = clearbit(statusBincom,Bin3Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin3Pos);
		bin3_comm_count = 0;
	}
	else
	{
		if(++bin3_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin3Pos);
			bin3_comm_count = FaultTolerance;
		}
	}
	if(Readbit(statusBincom,Bin4Pos))
	{
		statusBincom = clearbit(statusBincom,Bin4Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin4Pos);
		bin4_comm_count = 0;
	}
	else
	{
		if(++bin4_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin4Pos);
			bin4_comm_count = FaultTolerance;
		}
	}
	if(Readbit(statusBincom,Bin5Pos))
	{
		statusBincom = clearbit(statusBincom,Bin5Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin5Pos);
		bin5_comm_count = 0;
	}
	else
	{
		if(++bin5_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin5Pos);
			bin5_comm_count = FaultTolerance;
		}
	}
	if(Readbit(statusBincom,Bin6Pos))
	{
		statusBincom = clearbit(statusBincom,Bin6Pos);
		statusBincom_Fault = clearbit(statusBincom_Fault,Bin6Pos);
		bin6_comm_count = 0;
	}
	else
	{
		if(++bin6_comm_count >= FaultTolerance)
		{
			statusBincom_Fault= setbitAC(statusBincom_Fault,Bin6Pos);
			bin6_comm_count = FaultTolerance;
		}
	}
}


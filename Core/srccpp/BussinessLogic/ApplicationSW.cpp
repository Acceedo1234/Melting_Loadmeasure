
/*
 * LpdcLogic.cpp
 *
 *  Created on: 04-Feb-2023
 *      Author: MKS
 */
extern "C"{
#include "Struct_Input_output.h"
}
#include <BussinessLogic/ApplicationSW.h>
#include "main.h"


GPIO_PinState GPIO_PinStateMac;
GPIO_PinState GPIO_PinStateRej;

uint8_t MAC_A_Prod_Input1_StartTimer;
uint16_t MAC_A_Prod_Input1_CountBase;
uint16_t MAC_Gen_Prod_Input1_Production,Production_Zeit;
uint16_t MAC_Gen_Rej_Input_Production,Rejection_Zeit;
uint16_t Manual_RejectionCount;
uint8_t CurrentShift_K1;
uint8_t IsCurrentShiftUpdated;
uint8_t updateSetData;

/*Data shared btw server & client*/
//Client -server
uint8_t status_to_server;
uint16_t ProcessId_Value;
//server - client
extern uint8_t skipIdTCP;
extern uint8_t statusTCP;
extern uint16_t seq1_count_inc,seq2_count_inc;
extern uint16_t furnace;


uint16_t Seq1temperature;
uint16_t Seq2temperature;
uint8_t Seq1durationHr,Seq1durationMin,Seq2durationHr,Seq2durationMin;
uint16_t temperature_reference;
uint8_t start_process_control_timer;
uint8_t stop_timer_count;
uint8_t process_complete;
uint16_t seq1_duration_total,seq2_duration_total;
uint8_t updateTargetWightInMem;

uint8_t debouncestart,debounceend;
uint8_t calculateDeltaWeight;
uint8_t negValue[10];
uint32_t carbonTargetWghtMem,silicaTargetWghtMem,manganeaseTargetWghtMem,copperTargetWghtMem,tinTargetWghtMem,zincTargetWghtMem;
uint32_t Carbon_calculated_Weight,Silica_calculated_Weight,manganease_calculated_Weight,Copper_calculated_Weight,Tin_calculated_Weight,Zinc_calculated_Weight;
extern uint16_t rxReqCarbon,rxReqSilica,rxReqMn,rxReqCu,rxReqSn,rxReqZn;
extern uint32_t carbonActWght,SilicaActWght,ManganeaseActWght,copperActWght,tinActWght,zincActWeight;
Loadmeasure::Loadmeasure() {
	// TODO Auto-generated constructor stub

}

Loadmeasure::~Loadmeasure() {
	// TODO Auto-generated destructor stub
}

void Loadmeasure::run()
{
	inputBasedTrigger();
	Carbon_calculated_Weight = calculationCarbonWeight();
	Silica_calculated_Weight = calculationSilicaWeight();
	manganease_calculated_Weight = calculationManganeaseWeight();
	Copper_calculated_Weight = calculationCopperWeight();
	Tin_calculated_Weight = calculationTinWeight();
	Zinc_calculated_Weight = calculationZincWeight();
}

void Loadmeasure::inputBasedTrigger(){
	readStartbutton = HAL_GPIO_ReadPin(GPIOC,InputMachine1_Pin);
	readEndbutton   = HAL_GPIO_ReadPin(GPIOC,InputMachine2_Pin);

	if((readStartbutton == GPIO_PIN_RESET)&&(debouncestart==1))
	{
		debouncestart=0;
		if(calculateDeltaWeight != 1){
			calculateDeltaWeight=1;
			carbonTargetWghtMem     = carbonActWght      - rxReqCarbon;
			silicaTargetWghtMem     = SilicaActWght      - rxReqSilica;
			manganeaseTargetWghtMem = ManganeaseActWght  - rxReqMn;
			copperTargetWghtMem     = copperActWght      - rxReqCu;
			tinTargetWghtMem        = tinActWght         - rxReqSn;
			zincTargetWghtMem       = zincActWeight      - rxReqZn;
			updateTargetWightInMem = 1;
		}
	}
	else if(readStartbutton == GPIO_PIN_SET){
		debouncestart=1;
	}

	if((readEndbutton == GPIO_PIN_RESET)&&(debounceend==1))
	{
		debounceend=0;
		calculateDeltaWeight=0;
	}
	else if(readEndbutton == GPIO_PIN_SET){
		debounceend=1;
	}
}

uint32_t Loadmeasure::calculationCarbonWeight(){
	uint32_t  carbonProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(carbonActWght==0){
			carbonProcessedWght = 0;
		}
		else{
			if(carbonActWght >= carbonTargetWghtMem){
				carbonProcessedWght = carbonActWght - carbonTargetWghtMem;
				negValue[0]=0;
			}
			else{
				carbonProcessedWght = carbonTargetWghtMem - carbonActWght;
				negValue[0]=1;
			}
		}
	}
	else{
		carbonProcessedWght = carbonActWght;
	}
	return carbonProcessedWght;
}

uint32_t Loadmeasure::calculationSilicaWeight(){
	uint32_t  SilicaProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(SilicaActWght==0)
		{
			SilicaProcessedWght=0;
		}
		else{
			if(SilicaActWght >= silicaTargetWghtMem){
				SilicaProcessedWght = SilicaActWght - silicaTargetWghtMem;
				negValue[1]=0;
			}
			else{
					SilicaProcessedWght = silicaTargetWghtMem - SilicaActWght;
					negValue[1]=1;
			}
		}
	}
	else{
		SilicaProcessedWght = SilicaActWght;
	}
	return SilicaProcessedWght;
}

uint32_t Loadmeasure::calculationManganeaseWeight(){
	uint32_t  ManganeaseProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(ManganeaseActWght ==0){
			ManganeaseProcessedWght = 0;
		}
		else{
			if(carbonActWght >= carbonTargetWghtMem){
				ManganeaseProcessedWght = ManganeaseActWght - manganeaseTargetWghtMem;
				negValue[2]=0;
			}
			else{
					ManganeaseProcessedWght = manganeaseTargetWghtMem - ManganeaseActWght;
					negValue[2]=1;
			}
		}
	}
	else{
		ManganeaseProcessedWght = ManganeaseActWght;
	}
	return ManganeaseProcessedWght;
}

uint32_t Loadmeasure::calculationCopperWeight(){
	uint32_t  copperProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(copperActWght==0){
			copperProcessedWght=0;
		}
		else{
			if(carbonActWght >= carbonTargetWghtMem){
				copperProcessedWght = copperActWght - copperTargetWghtMem;
				negValue[3]=0;
			}
			else{
					copperProcessedWght = copperTargetWghtMem - copperActWght;
					negValue[3]=1;
			}
		}
	}
	else{
		copperProcessedWght = copperActWght;
	}
	return copperProcessedWght;
}

uint32_t Loadmeasure::calculationTinWeight(){
	uint32_t  tinProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(tinActWght==0){
			tinProcessedWght=0;
		}
		else{
			  if(tinActWght >= tinTargetWghtMem){
				tinProcessedWght = tinActWght - tinTargetWghtMem;
				negValue[4]=0;
			}
			else{
					tinProcessedWght = tinTargetWghtMem - tinActWght;
					negValue[4]=1;
			}
			 tinProcessedWght = tinActWght - tinTargetWghtMem;
		}
	}
	else{
		tinProcessedWght = tinActWght;
	}
	return tinProcessedWght;
}

uint32_t Loadmeasure::calculationZincWeight(){
	uint32_t  zincProcessedWght;
	if(calculateDeltaWeight==1)
	{
		if(zincActWeight==0){
			zincProcessedWght = 0;
		}
		else{
			if(zincActWeight >= zincTargetWghtMem){
				zincProcessedWght = zincActWeight - zincTargetWghtMem;
				negValue[5]=0;
			}
			else{
				 zincProcessedWght = zincTargetWghtMem - zincActWeight;
				 negValue[5]=1;
			}
		}
	}
	else{
		zincProcessedWght = zincActWeight;
	}
	return zincProcessedWght;
}


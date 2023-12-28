/*
 * UARTTxRxHandle.c
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */
#include <aco_generic_enumeration.h>
#include"main.h"

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;
uint8_t rxTempBuff[5];
extern uint8_t u8rxbuf[255];
uint8_t checkbuff[200];
uint8_t refinc;

uint32_t carbonActWght,SilicaActWght,ManganeaseActWght,copperActWght,tinActWght,zincActWeight;


extern uint8_t Rxseqdecoder;
extern void ESPRxDecoder(unsigned char Rxwifi_data,unsigned char Rxseqdecoder);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &hlpuart1)
	{
		ESPRxDecoder(rxTempBuff[0],Rxseqdecoder);

		HAL_UART_Receive_IT(&hlpuart1,rxTempBuff,1);
	}

	if(huart == &huart1)
	{
		if((u8rxbuf[0] == CARBON)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			carbonActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
		if((u8rxbuf[0] == SILICA)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			SilicaActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
		if((u8rxbuf[0] == MANGANEASE)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			ManganeaseActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
		if((u8rxbuf[0] == COPPER)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			copperActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
		if((u8rxbuf[0] == TIN)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			tinActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
		if((u8rxbuf[0] == ZINC)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			zincActWeight = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
		}
	}
}




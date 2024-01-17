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
extern uint8_t u8rxbuf[24];
uint8_t checkbuff[200];
uint8_t refinc;
uint8_t Rx_Dwin_Data_Buff[50];
uint8_t Rx_Dwin_Buff[3];
uint8_t Rx_Dwin_Data_Buff_Point;
uint8_t Rx_Dwin_Complete;
uint8_t No_Of_Dwin_Bytes;

uint32_t carbonActWght,SilicaActWght,ManganeaseActWght,copperActWght,tinActWght,zincActWeight;
uint8_t statusBincom;


extern uint8_t Rxseqdecoder;
extern uint8_t Rx_Dwin_Point;
extern void ESPRxDecoder(unsigned char Rxwifi_data,unsigned char Rxseqdecoder);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &hlpuart1)
	{
		if((Rx_Dwin_Buff[0] ==0x83)&&(Rx_Dwin_Point==0))
			{
				Rx_Dwin_Point=1;
			}
			else if(Rx_Dwin_Point==1)
			{
				if(Rx_Dwin_Buff[0] == 0x30){
					Rx_Dwin_Point=2;
				}
				else{
					Rx_Dwin_Point=0;
				}
			}
			else if((Rx_Dwin_Buff[0] == 0x00)&&(Rx_Dwin_Point==2))
			{
				Rx_Dwin_Point=3;
			}
			else if(Rx_Dwin_Point==3)
			{
				Rx_Dwin_Point=4;
				No_Of_Dwin_Bytes = Rx_Dwin_Buff[0]*2;
				Rx_Dwin_Data_Buff_Point = 0;
			}
			else if(Rx_Dwin_Point==4)
			{
				//Rx_Dwin_Point=4;
				Rx_Dwin_Data_Buff[Rx_Dwin_Data_Buff_Point]= Rx_Dwin_Buff[0];
				No_Of_Dwin_Bytes = No_Of_Dwin_Bytes-1;
				Rx_Dwin_Data_Buff_Point = Rx_Dwin_Data_Buff_Point+1;
				if(No_Of_Dwin_Bytes==0){
					Rx_Dwin_Complete = 1;
					Rx_Dwin_Point=0;
				}
			}
			HAL_UART_Receive_IT(&hlpuart1,Rx_Dwin_Buff,1);
		}

	if(huart == &huart1)
	{
		if((u8rxbuf[0] == CARBON)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			carbonActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<0));
		}
		if((u8rxbuf[0] == SILICA)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			SilicaActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<1));
		}
		if((u8rxbuf[0] == MANGANEASE)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			ManganeaseActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<2));
		}
		if((u8rxbuf[0] == COPPER)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			copperActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<3));
		}
		if((u8rxbuf[0] == TIN)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			tinActWght = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<4));
		}
		if((u8rxbuf[0] == ZINC)&&(u8rxbuf[1] == 0x04)&&(u8rxbuf[2] == 0x04)){
			zincActWeight = (u8rxbuf[3]<<24 | u8rxbuf[4]<<16 | u8rxbuf[5]<<8 | u8rxbuf[6]);
			statusBincom = (statusBincom|(1<<5));
		}
	}
}




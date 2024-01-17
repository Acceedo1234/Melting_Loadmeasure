/*
 * Modbusrtu.cpp
 *
 *  Created on: 07-Jan-2023
 *      Author: MKS
 */

#include <aco_generic_enumeration.h>
#include "Modbusrtu.h"
#include "Modbus_types.h"

#define READINPUTREG 0x04
#define STARTADDRESS 0x03
#define NOOFDATA     0x02

/*DWIN hmi uart data*/

constexpr uint8_t START_BYTE_1=0x5A;
constexpr uint8_t START_BYTE_2=0xA5;
constexpr uint8_t multipleWriteRequestH = 0x0B;
constexpr uint8_t multipleWriteRequestL = 0x82;
constexpr uint8_t multipleReadRequestH = 0x04;
constexpr uint8_t multipleReadRequestL = 0x83;

extern uint16_t temperatureSetOL,temperaturehighSetOL,temperatureLowSetOL;
extern uint16_t temperature_reference;
extern uint8_t httpc_isConnected;
extern uint8_t Rx_Dwin_Complete;

uint8_t TxSeqComplete;
uint8_t test;
uint8_t Rx_Dwin_Point;

uint8_t Ip_config_Ip[4],Ip_Config_Subnet[4],Ip_config_gateway[4],Ip_config_DNS[4],Ip_config_Server[4];
uint8_t Update_Dwin_Set_Data;
uint16_t Ip_config_Server_Port;
uint8_t No_Of_Furnace;
uint16_t Ip_config_Server_Port_K1;
uint8_t No_Of_Meter_K1;
uint8_t No_Of_Meter;
extern uint8_t Rx_Dwin_Data_Buff[50];
Modbusrtu::Modbusrtu() {
	// TODO Auto-generated constructor stub

}

Modbusrtu::~Modbusrtu() {
	// TODO Auto-generated destructor stub
}

uint8_t Modbusrtu::getReadInputReg() const
{
	return READINPUTREG;
}

uint16_t Modbusrtu::getStartAddress() const
{
	return STARTADDRESS;
}

uint16_t Modbusrtu::getNoOfData() const
{
	return NOOFDATA;
}

void Modbusrtu::ModbusReadTransaction(void)
{
	switch(Cntid)
	{
	case CARBON:
		u8ModbusRegister[0] = CARBON;
		u8ModbusRegister[1] = getReadInputReg();
		u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
		u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
		u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);

		Cntid=2;
	break;
	case SILICA:
		u8ModbusRegister[0] = SILICA;
		u8ModbusRegister[1] = getReadInputReg();
		u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
		u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
		u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
		Cntid=3;
	break;
	case MANGANEASE:
		u8ModbusRegister[0] = MANGANEASE;
		u8ModbusRegister[1] = getReadInputReg();
		u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
		u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
		u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
		Cntid=4;
	break;
	case COPPER:
		u8ModbusRegister[0] = COPPER;
		u8ModbusRegister[1] = getReadInputReg();
		u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
		u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
		u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
		u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
		u16CRC 				= ASCChecksum(u8ModbusRegister,6);
		u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
		u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
		Cntid=5;
	break;
	case TIN:
			u8ModbusRegister[0] = TIN;
			u8ModbusRegister[1] = getReadInputReg();
			u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
			u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
			u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=6;
	break;
	case ZINC:
			u8ModbusRegister[0] = ZINC;
			u8ModbusRegister[1] = getReadInputReg();
			u8ModbusRegister[2] = static_cast<uint8_t>((getStartAddress()& 0xff00)>>8);
			u8ModbusRegister[3] = static_cast<uint8_t>(getStartAddress() & 0x00ff);
			u8ModbusRegister[4] = static_cast<uint8_t>((getNoOfData() & 0xff00)>>8);
			u8ModbusRegister[5] = static_cast<uint8_t>(getNoOfData() & 0x00ff);
			u16CRC 				= ASCChecksum(u8ModbusRegister,6);
			u8ModbusRegister[6] = static_cast<uint8_t>(u16CRC & 0x00ff);
			u8ModbusRegister[7] = static_cast<uint8_t>((u16CRC & 0xff00)>>8);
			Cntid=1;
	break;
	default:
		Cntid=1;
		mTemperatureSensorId=1;
	break;
	}
	//out_read_rxint_set.Noofbytesrx = (_u16ReadQty*2)+5;
	HAL_UART_Transmit_IT(&huart1,u8ModbusRegister,sizeof(u8ModbusRegister));

}
//Hardware callback
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart1,u8rxbuf,9);
}

uint16_t Modbusrtu::ASCChecksum(uint8_t *ASCSrc, uint8_t NoOfBytes)
{
	uint8_t i, CheckSumBytes;
	uint8_t CRCRegLow = 0xff;
	uint8_t CRCRegHigh = 0xff;
	uint8_t CRCIndex;

	CheckSumBytes = NoOfBytes;
   	for(i=0;i < CheckSumBytes;i++)
   	{
	    CRCIndex = CRCRegLow ^ *ASCSrc++; 				//TransmittingData[i];
		CRCRegLow = CRCRegHigh ^ CRCArrayHigh[CRCIndex];
		CRCRegHigh = CRCArrayLow[CRCIndex];

	}
	return (CRCRegHigh << 8 | CRCRegLow );
}

void Modbusrtu::dwinFrame(void)
{
	test = test+1;
	switch(Cntid_dwin)
	{
	case 0:
		u8ModbusRegisterdwin[0] = START_BYTE_1;
		u8ModbusRegisterdwin[1] = START_BYTE_2;
		u8ModbusRegisterdwin[2] = multipleWriteRequestH;
		u8ModbusRegisterdwin[3] = multipleWriteRequestL;
		u8ModbusRegisterdwin[4] = 0x20;
		u8ModbusRegisterdwin[5] = 0x00;
		u8ModbusRegisterdwin[6] = 0x00;
		u8ModbusRegisterdwin[7] = test;
		u8ModbusRegisterdwin[8] = 0;
		u8ModbusRegisterdwin[9] = httpc_isConnected;
		u8ModbusRegisterdwin[10] = 0;
		u8ModbusRegisterdwin[11] = 1;
		noOfDataDwin=12;
		Cntid_dwin=1;
	break;
	case 1:
		u8ModbusRegisterdwin[0] = START_BYTE_1;
		u8ModbusRegisterdwin[1] = START_BYTE_2;
		u8ModbusRegisterdwin[2] = multipleWriteRequestH;
		u8ModbusRegisterdwin[3] = multipleWriteRequestL;
		u8ModbusRegisterdwin[4] = 0x20;
		u8ModbusRegisterdwin[5] = 0x00;
		u8ModbusRegisterdwin[6] = 0x00;
		u8ModbusRegisterdwin[7] = test;
		u8ModbusRegisterdwin[8] = 0;
		u8ModbusRegisterdwin[9] = httpc_isConnected;
		u8ModbusRegisterdwin[10] = 0;
		u8ModbusRegisterdwin[11] = 1;
		noOfDataDwin=12;
		Cntid_dwin=2;
	break;
	case 2:
		u8ModbusRegisterdwin[0] = START_BYTE_1;
		u8ModbusRegisterdwin[1] = START_BYTE_2;
		u8ModbusRegisterdwin[2] = multipleReadRequestH;
		u8ModbusRegisterdwin[3] = multipleReadRequestL;
		u8ModbusRegisterdwin[4] = 0x30;
		u8ModbusRegisterdwin[5] = 0x00;
		u8ModbusRegisterdwin[6] = 0x16;
		//HAL_UART_Receive_IT(&hlpuart1,testarray,25);
		Rx_Dwin_Point=0;
		noOfDataDwin=7;
		Cntid_dwin=0;
	break;
	default:
		Cntid_dwin=0;
	break;
	}
	//out_read_rxint_set.Noofbytesrx = (_u16ReadQty*2)+5;
	HAL_UART_Transmit_IT(&hlpuart1,u8ModbusRegisterdwin,noOfDataDwin);

}

void Modbusrtu::dwinDecoder(void)
{
	if(Rx_Dwin_Complete == 0){return;}
	Rx_Dwin_Complete=0;

	if(Rx_Dwin_Data_Buff[43] !=0 )
	{
		for(d=0,x=1;d<=3;d++,x=x+2)
		{
			if(Ip_config_Ip[d]!=Rx_Dwin_Data_Buff[x])
			{
				Update_Dwin_Set_Data =1;
			}
		}
		Ip_config_Ip[0] = Rx_Dwin_Data_Buff[1];
		Ip_config_Ip[1] = Rx_Dwin_Data_Buff[3];
		Ip_config_Ip[2] = Rx_Dwin_Data_Buff[5];
		Ip_config_Ip[3] = Rx_Dwin_Data_Buff[7];
		for(d=0,x=9;d<=3;d++,x=x+2)
		{
			if(Ip_Config_Subnet[d]!=Rx_Dwin_Data_Buff[x])
			{
				Update_Dwin_Set_Data =1;
			}
		}
		Ip_Config_Subnet[0] = Rx_Dwin_Data_Buff[9];
		Ip_Config_Subnet[1] = Rx_Dwin_Data_Buff[11];
		Ip_Config_Subnet[2] = Rx_Dwin_Data_Buff[13];
		Ip_Config_Subnet[3] = Rx_Dwin_Data_Buff[15];
		for(d=0,x=17;d<=3;d++,x=x+2)
		{
			if(Ip_config_gateway[d]!=Rx_Dwin_Data_Buff[x])
			{
				Update_Dwin_Set_Data =1;
			}
		}
		Ip_config_gateway[0] = Rx_Dwin_Data_Buff[17];
		Ip_config_gateway[1] = Rx_Dwin_Data_Buff[19];
		Ip_config_gateway[2] = Rx_Dwin_Data_Buff[21];
		Ip_config_gateway[3] = Rx_Dwin_Data_Buff[23];
		for(d=0,x=25;d<=3;d++,x=x+2)
		{
			if(Ip_config_DNS[d]!=Rx_Dwin_Data_Buff[x])
			{
				Update_Dwin_Set_Data =1;
			}
		}
		Ip_config_DNS[0] = Rx_Dwin_Data_Buff[25];
		Ip_config_DNS[1] = Rx_Dwin_Data_Buff[27];
		Ip_config_DNS[2] = Rx_Dwin_Data_Buff[29];
		Ip_config_DNS[3] = Rx_Dwin_Data_Buff[31];
		for(d=0,x=33;d<=3;d++,x=x+2)
		{
			if(Ip_config_Server[d]!=Rx_Dwin_Data_Buff[x])
			{
				Update_Dwin_Set_Data =1;
			}
		}
		Ip_config_Server[0] = Rx_Dwin_Data_Buff[33];
		Ip_config_Server[1] = Rx_Dwin_Data_Buff[35];
		Ip_config_Server[2] = Rx_Dwin_Data_Buff[37];
		Ip_config_Server[3] = Rx_Dwin_Data_Buff[39];
		Ip_config_Server_Port_K1 = ((Rx_Dwin_Data_Buff[40]<<8)|(Rx_Dwin_Data_Buff[41]));
		if(Ip_config_Server_Port != Ip_config_Server_Port_K1)
		{
			Ip_config_Server_Port = Ip_config_Server_Port_K1;
			Update_Dwin_Set_Data =1;
		}
		No_Of_Meter_K1 		= Rx_Dwin_Data_Buff[43];
		if(No_Of_Meter != No_Of_Meter_K1)
		{
			No_Of_Meter 		= No_Of_Meter_K1;
			Update_Dwin_Set_Data =1;
		}
	}
}

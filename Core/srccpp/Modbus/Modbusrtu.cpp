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

extern uint16_t temperatureSetOL,temperaturehighSetOL,temperatureLowSetOL;
extern uint16_t temperature_reference;



uint8_t TxSeqComplete;
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
		Cntid=0;
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

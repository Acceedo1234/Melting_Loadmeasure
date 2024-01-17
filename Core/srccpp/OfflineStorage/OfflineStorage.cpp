/*
 * OfflineStorage.cpp
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */
#include "main.h"
#include "OfflineStorage.h"
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAXNOOFBLOCK 32

extern "C" {
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
void W25qxx_EraseSector(uint32_t SectorAddr);
bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize);
void W25qxx_EraseBlock(uint32_t BlockAddr);
void W25qxx_EraseChip(void);
}

uint8_t ProductionSet_uintFormat[100]={0};
char ProductionSet_charFormat[100]={'\0'};
uint16_t SectorPos;

/*Data need to saved in flash*/

extern uint16_t rxReqCarbon,rxReqSilica,rxReqMn,rxReqCu,rxReqSn,rxReqZn;
extern uint32_t carbonTargetWghtMem,silicaTargetWghtMem,manganeaseTargetWghtMem,copperTargetWghtMem,tinTargetWghtMem,zincTargetWghtMem;

/*check for change in data*/
uint16_t rxReqCarbon_K1,rxReqSilica_K1,rxReqMn_K1,rxReqCu_K1,rxReqSn_K1,rxReqZn_K1;
extern uint8_t Ip_config_Ip[4],Ip_Config_Subnet[4],Ip_config_gateway[4],Ip_config_DNS[4],Ip_config_Server[4];
extern uint8_t Update_Dwin_Set_Data;
extern uint16_t Ip_config_Server_Port;


OfflineStorage::OfflineStorage() {
	// TODO Auto-generated constructor stub

}

OfflineStorage::~OfflineStorage() {
	// TODO Auto-generated destructor stub
}

void OfflineStorage::run()
{
	m_writesetdata();
	m_writecalculationdata();
}

void OfflineStorage::m_writesetdata(){
	if((rxReqCarbon != rxReqCarbon_K1)||(rxReqSilica_K1 != rxReqSilica)||(rxReqCu_K1 != rxReqCu)
		||(rxReqSn_K1!= rxReqSn)||(rxReqZn_K1 != rxReqZn)||(rxReqMn_K1 != rxReqMn))
	{
		m_writeFlashBuf[0] = static_cast<uint8_t>(rxReqCarbon & 0x00ff);
		m_writeFlashBuf[1] = static_cast<uint8_t>((rxReqCarbon & 0xff00)>>8);
		m_writeFlashBuf[2] = (uint8_t)rxReqSilica&0x00ff;
		m_writeFlashBuf[3] = (uint8_t)(rxReqSilica>>8)&0x00ff;
		m_writeFlashBuf[4] = static_cast<uint8_t>(rxReqMn & 0xff);
		m_writeFlashBuf[5] = static_cast<uint8_t>(rxReqMn>>8) & 0xff;
		m_writeFlashBuf[6] = static_cast<uint8_t>(rxReqCu & 0xff);
		m_writeFlashBuf[7] = static_cast<uint8_t>(rxReqCu>>8) & 0xff;
		m_writeFlashBuf[8] = static_cast<uint8_t>(rxReqSn & 0xff);
		m_writeFlashBuf[9] = static_cast<uint8_t>(rxReqSn>>8) & 0xff;
		m_writeFlashBuf[10] = static_cast<uint8_t>(rxReqZn & 0xff);
		m_writeFlashBuf[11] = static_cast<uint8_t>(rxReqZn>>8) & 0xff;
		rxReqCarbon_K1=rxReqCarbon;
		rxReqSilica_K1 = rxReqSilica;
		rxReqMn_K1 = rxReqMn;
		rxReqCu_K1 = rxReqCu;
		rxReqSn_K1 = rxReqSn;
		rxReqZn_K1 = rxReqZn;
		W25qxx_EraseSector(1);
		W25qxx_WriteSector(m_writeFlashBuf,1,10,12);
	}

}

void OfflineStorage::m_writecalculationdata(){
	if(Update_Dwin_Set_Data)
		{
			Update_Dwin_Set_Data=0;
			W25qxx_EraseSector(100);
			m_writeDwinBuf[0] = Ip_config_Ip[0];
			m_writeDwinBuf[1] = Ip_config_Ip[1];
			m_writeDwinBuf[2] = Ip_config_Ip[2];
			m_writeDwinBuf[3] = Ip_config_Ip[3];

			m_writeDwinBuf[4] = Ip_Config_Subnet[0];
			m_writeDwinBuf[5] = Ip_Config_Subnet[1];
			m_writeDwinBuf[6] = Ip_Config_Subnet[2];
			m_writeDwinBuf[7] = Ip_Config_Subnet[3];

			m_writeDwinBuf[8] = Ip_config_gateway[0];
			m_writeDwinBuf[9] = Ip_config_gateway[1];
			m_writeDwinBuf[10] = Ip_config_gateway[2];
			m_writeDwinBuf[11] = Ip_config_gateway[3];

			m_writeDwinBuf[12] = Ip_config_DNS[0];
			m_writeDwinBuf[13] = Ip_config_DNS[1];
			m_writeDwinBuf[14] = Ip_config_DNS[2];
			m_writeDwinBuf[15] = Ip_config_DNS[3];

			m_writeDwinBuf[16] = Ip_config_Server[0];
			m_writeDwinBuf[17] = Ip_config_Server[1];
			m_writeDwinBuf[18] = Ip_config_Server[2];
			m_writeDwinBuf[19] = Ip_config_Server[3];

			m_writeDwinBuf[20] = (unsigned char)(Ip_config_Server_Port>>8)&0x00ff;
			m_writeDwinBuf[21] = (unsigned char)(Ip_config_Server_Port)&0x00ff;
			W25qxx_WriteSector(m_writeDwinBuf,100,0,22);
		}
}

void OfflineStorage::m_readIPdata(){
	W25qxx_ReadSector(m_readFlashBuf,100,0,22);

	 Ip_config_Ip[0] = m_readFlashBuf[0];
	 Ip_config_Ip[1] = m_readFlashBuf[1];
	 Ip_config_Ip[2] = m_readFlashBuf[2];
	 Ip_config_Ip[3] = m_readFlashBuf[3];

	 Ip_Config_Subnet[0]= m_readFlashBuf[4];
	 Ip_Config_Subnet[1]= m_readFlashBuf[5];
	 Ip_Config_Subnet[2]= m_readFlashBuf[6];
	 Ip_Config_Subnet[3]= m_readFlashBuf[7];

	 Ip_config_gateway[0] = m_readFlashBuf[8];
	 Ip_config_gateway[1] = m_readFlashBuf[9];
	 Ip_config_gateway[2] = m_readFlashBuf[10];
	 Ip_config_gateway[3] = m_readFlashBuf[11];

	 Ip_config_DNS[0] = m_readFlashBuf[12];
	 Ip_config_DNS[1] = m_readFlashBuf[13];
	 Ip_config_DNS[2] = m_readFlashBuf[14];
	 Ip_config_DNS[3] = m_readFlashBuf[15];

	 Ip_config_Server[0] = m_readFlashBuf[16];
	 Ip_config_Server[1] = m_readFlashBuf[17];
	 Ip_config_Server[2] = m_readFlashBuf[18];
	 Ip_config_Server[3] = m_readFlashBuf[19];

	 Ip_config_Server_Port = ((m_readFlashBuf[20]<<8)|(m_readFlashBuf[21]));
}


void OfflineStorage::m_readsetdata(){
	W25qxx_ReadSector(m_readFlashBuf,1,10,12);
	rxReqCarbon = (m_readFlashBuf[1]<<8 | m_readFlashBuf[0]);
	rxReqSilica = (m_readFlashBuf[3]<<8 | m_readFlashBuf[2]);
	rxReqMn = (m_readFlashBuf[5]<<8 | m_readFlashBuf[4]);
	rxReqCu = (m_readFlashBuf[7]<<8 | m_readFlashBuf[6]);
	rxReqSn = (m_readFlashBuf[9]<<8 | m_readFlashBuf[8]);
	rxReqZn = (m_readFlashBuf[11]<<8 | m_readFlashBuf[10]);

	rxReqCarbon_K1=rxReqCarbon;
	rxReqSilica_K1 = rxReqSilica;
	rxReqMn_K1 = rxReqMn;
	rxReqCu_K1 = rxReqCu;
	rxReqSn_K1 = rxReqSn;
	rxReqZn_K1 = rxReqZn;
}

void OfflineStorage::ReadOfflinedataInit()
{
	m_readIPdata();
	m_readsetdata();
}

void OfflineStorage::ECUProductionInit(void)
{

}


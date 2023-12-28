/*
 * OfflineStorage.h
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_
#define SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_

class OfflineStorage {
public:
	OfflineStorage();
	virtual ~OfflineStorage();
	void run();
	void ReadOfflinedataInit();
	void ECUProductionInit(void);
private:
	uint8_t m_writeFlashBuf[20];
	uint8_t m_readFlashBuf[20];

	void m_writecalculationdata();
	void m_readcalculationdata();
	void m_writesetdata(void);
	void m_readsetdata(void);
	void m_writeCountinc();
	void m_readCountinc();


};

#endif /* SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_ */

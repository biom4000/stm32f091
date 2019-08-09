/*
 * flash.h
 *
 *  Created on: 2019¦~7¤ë25¤é
 *      Author: Andywa
 */
#include "sys.h"

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#define appStartAddress	0x08003000
#define eepStartAddress 0x0800D000
#define bootloaderVersionAddress	0x08002FFE

//pageSize 1=2048byte
#define bootFlashSize	(12*1024)
#define bootFlashPage	(bootFlashSize/FLASH_PAGE_SIZE)
#define appFlashSize 	(40*1024)
#define appFlashPage	(appFlashSize/FLASH_PAGE_SIZE)
#define eepFlashSize 	(12*1024)
#define eepFlashPage	(eepFlashSize/FLASH_PAGE_SIZE)

HAL_StatusTypeDef Flash_If_Read(uint8_t* buff, uint32_t dest_addr, uint32_t Len);
HAL_StatusTypeDef Flash_If_Write(uint8_t *src, uint32_t dest_addr, uint32_t Len);
HAL_StatusTypeDef Flash_If_Erase(uint32_t Add, uint8_t pageSize);

#endif /* INC_FLASH_H_ */

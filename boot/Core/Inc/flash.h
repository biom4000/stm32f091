/*
 * flash.h
 *
 *  Created on: 2019¦~7¤ë25¤é
 *      Author: Andywa
 */
#include "sys.h"

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#define appStartAddress	0x08003C00
#define eepStartAddress 0x0800DC00
#define bootloaderVersionAddress	0x08003BFE

//pageSize 1=1024byte
#define bootFlashPage	10
#define bootFlashSize	(bootFlashPage*1024)
#define appFlashPage	40
#define appFlashSize 	(appFlashPage*1024)
#define eepFlashPage	15
#define eepFlashSize 	(eepFlashPage*1024)

HAL_StatusTypeDef Flash_If_Read(uint8_t* buff, uint32_t dest_addr, uint32_t Len);
HAL_StatusTypeDef Flash_If_Write(uint8_t *src, uint32_t dest_addr, uint32_t Len);
HAL_StatusTypeDef Flash_If_Erase(uint32_t Add, uint8_t pageSize);

#endif /* INC_FLASH_H_ */

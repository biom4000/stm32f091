/*
 * flash.h
 *
 *  Created on: 2019¦~7¤ë25¤é
 *      Author: Andywa
 */
#include "sys.h"

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

void Flash_If_Read(uint8_t* buff, uint32_t dest_addr, uint32_t Len);
void Flash_If_Write(uint8_t *src, uint32_t dest_addr, uint32_t Len);
void Flash_If_Erase(uint32_t Add, uint8_t pageSize);

#endif /* INC_FLASH_H_ */

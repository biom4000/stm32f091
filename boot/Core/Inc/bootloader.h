/*
 * bootloader.h
 *
 *  Created on: 2019¦~8¤ë8¤é
 *      Author: Andywa
 */
#include "sys.h"
#include "flash.h"

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#define bootModeNone 		0x00
#define bootModeErase 		0x01
#define bootModeGetVersion 	0x02
#define bootModeRead 		0x03
#define bootModeWrite	 	0x04

void bootMode(void);

#endif /* INC_BOOTLOADER_H_ */

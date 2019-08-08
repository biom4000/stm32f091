/*
 * app.h
 *
 *  Created on: 2019�~7��23��
 *      Author: Andywa
 */
#include "flash.h"
#include "sys.h"
#include "bootloader.h"
#include <string.h>

#ifndef INC_MAINSTART_H_
#define INC_MAINSTART_H_

void bootMain(void);
void jumpToApp(void);

#endif /* INC_MAINSTART_H_ */

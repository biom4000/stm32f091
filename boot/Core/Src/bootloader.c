/*
 * bootloader.c
 *
 *  Created on: 2019¦~8¤ë8¤é
 *      Author: Andywa
 */
#include "bootloader.h"

void bootMode(void)
{
	char buf[50];
	uint8_t version[2];
	uint8_t cmd=bootModeNone;
	uint16_t length=0;
	//HAL_StatusTypeDef sta;

//	Flash_If_Read(version,0x0800DC01,2);
//	length = snprintf(buf, sizeof(buf),"bootloader version %03d.%03d\r\n", version[0],version[1]);
	length = snprintf(buf, sizeof(buf),"erase=0x01,version=0x02,read=0x03,write=0x04\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
	HAL_UART_Receive_IT(&huart1,&cmd,1);

	while(1){
		if(cmd != bootModeNone){
			break;
		}
		HAL_Delay(500);
	}
	switch (cmd) {
		case bootModeErase:
			length = snprintf(buf, sizeof(buf),"erase\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);

			Flash_If_Erase(appStartAddress,appFlashSize/1024);
			break;
		case bootModeGetVersion:
			length = snprintf(buf, sizeof(buf),"version\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
			break;
		case bootModeRead:
			length = snprintf(buf, sizeof(buf),"read\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
			break;
		case bootModeWrite:
			length = snprintf(buf, sizeof(buf),"write\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
			break;
		default:
			break;
	}

//	else{
//				length = snprintf(buf, sizeof(buf),"upgrade fail!!\r\n");
//				HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
//				break;
//			}
}

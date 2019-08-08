/*
 * bootloader.c
 *
 *  Created on: 2019¦~8¤ë8¤é
 *      Author: Andywa
 */
#include "bootloader.h"

HAL_StatusTypeDef bootMode(void)
{
	char buf[50];
	uint8_t cmd;
	uint16_t length=0;
	HAL_StatusTypeDef sta;
	//HAL_StatusTypeDef sta;

//	Flash_If_Read(version,0x0800DC01,2);
	//length += snprintf(buf+length, sizeof(buf)-length,"%0d.%0d", readOneByteFlash(0x800DC01),readOneByteFlash(0x800DC02));

//	length = snprintf(buf, sizeof(buf),"bootloader version %03d.%03d\r\n", version[0],version[1]);
	length = snprintf(buf, sizeof(buf),"erase=0x01,version=0x02,read=0x03,write=0x04\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);
	cmd=bootModeNone;
	HAL_UART_Receive_IT(&huart1,&cmd,1);

	while(1){
		if(cmd != bootModeNone){
			break;
		}
		HAL_Delay(500);
	}
	switch (cmd) {
		case bootModeErase:
			sta = eraseFlashApp();
			break;
		case bootModeGetVersion:
			sta = getBootloaderVersion();
			break;
		case bootModeRead:
			sta = readFlashapp();
			break;
		case bootModeWrite:
			length = snprintf(buf, sizeof(buf),"write\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);
			break;
		default:
			break;
	}
	sta=HAL_OK;
	return sta;
}

HAL_StatusTypeDef writeFlashapp(void)
{
	uint32_t length=0;
	char buf[50];
	uint8_t flashData[appFlashSize];
	uint8_t i;
	HAL_StatusTypeDef sta;

	length = snprintf(buf, sizeof(buf),"read\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);
	memset(flashData, 0xFF, sizeof(flashData));
	HAL_UART_Receive_IT(&huart1,flashData,sizeof(flashData));

	while(1){
		if(flashData[0] != 0xFF){
			break;
		}
		HAL_Delay(500);
	}
	sta = HAL_OK;
	return sta;
}

HAL_StatusTypeDef readFlashapp(void)
{
	uint32_t length=0;
	char buf[500000];
	uint8_t flashData[appFlashSize];
	uint8_t i;
	HAL_StatusTypeDef sta;

	length = snprintf(buf, sizeof(buf),"read\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);

	sta = Flash_If_Read(flashData,appStartAddress,sizeof(flashData));
	for(i=0; i<sizeof(flashData); i++){
		length += snprintf(buf+length, sizeof(buf)-length,"0x%02X\r\n",flashData[i]);
	}

	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);

	return sta;
}

HAL_StatusTypeDef getBootloaderVersion(void)
{
	uint16_t length=0;
	char buf[50];
	uint8_t vboot[2];
	HAL_StatusTypeDef sta;

	length = snprintf(buf, sizeof(buf),"version\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);

	sta = Flash_If_Read(vboot,bootloaderVersionAddress,2);
	length = snprintf(buf, sizeof(buf),"%03d,%03d\r\n",vboot[0],vboot[1]);
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);

	return sta;
}

HAL_StatusTypeDef eraseFlashApp(void)
{
	uint16_t length=0;
	char buf[50];
	HAL_StatusTypeDef sta;

	length = snprintf(buf, sizeof(buf),"erase\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,timeOutBus);
	sta = Flash_If_Erase(appStartAddress,appFlashPage);

	return sta;
}

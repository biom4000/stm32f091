#include "mainStart.h"

typedef void (*pFunction)(void);

void sMain(void)
{
	//HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuff, sizeof(rxBuff));
	uint8_t buf;

	Flash_If_Read(&buf,0x0800DC00,1);

	if(buf == 0xA0){
		bootMode();
	}else{
		JumpToApp();
	}

	while(1){
		HAL_Delay(500);
	}

}


void boot_GetVersion(void)
{
	char buf[100]="";
	uint16_t length=0;
	uint8_t s;

	//s=readOneByteFlash(0x8003001);

	//length += snprintf(buf+length, sizeof(buf)-length,"%0d.%0d", readOneByteFlash(0x800DC01),readOneByteFlash(0x800DC02));

	length = snprintf(buf, sizeof(buf),"%0d.%0d", s,s);

	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
}

void bootMode(void)
{
	char buf[50];
	uint8_t version[2];
	uint8_t cmd;
	uint16_t length=0;
	HAL_StatusTypeDef sta;

	Flash_If_Read(version,0x0800DC01,2);
	length = snprintf(buf, sizeof(buf),"bootloader version %03d.%03d\r\n", version[0],version[1]);
	length += snprintf(buf+length, sizeof(buf)-length,"start upgrade? Y/N\r\n");
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
	HAL_UART_Receive_IT(&huart1,&cmd,1);


	if(sta == HAL_OK){
		if(cmd == "Y"){
			length = snprintf(buf, sizeof(buf),"waitting upgrade...\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
		}else{
			length = snprintf(buf, sizeof(buf),"close upgrade!!\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
		}
	}else{
		length = snprintf(buf, sizeof(buf),"upgrade fail!!\r\n");
		HAL_UART_Transmit(&huart1,(uint8_t *)buf,length,100);
	}
}


void JumpToApp(void)
{
	pFunction appEntry;
	uint32_t appStack;
	uint32_t APPLICATION_ADDRESS=0x8003C00;

	appStack = (uint32_t) *((__IO uint32_t*)APPLICATION_ADDRESS);
	appEntry = (pFunction) *(__IO uint32_t*)(APPLICATION_ADDRESS +4);
	//memcpy((void*)0x20000000, (void*)APPLICATION_ADDRESS, 0xBC); //47*4
	//__HAL_SYSCFG_REMAPMEMORY_SRAM();
	__set_MSP(appStack);
	appEntry();
}

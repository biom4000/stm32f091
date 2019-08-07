#include "mainStart.h"

typedef void (*pFunction)(void);

void sMain(void)
{
	//HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuff, sizeof(rxBuff));
	uint8_t buf;

	Flash_If_Read(&buf,eepStartAddress,1);

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




void JumpToApp(void)
{
	pFunction appEntry;
	uint32_t appStack;
	//uint32_t APPLICATION_ADDRESS=0x8003C00;

	appStack = (uint32_t) *((__IO uint32_t*)appStartAddress);
	appEntry = (pFunction) *(__IO uint32_t*)(appStartAddress +4);
	//memcpy((void*)0x20000000, (void*)APPLICATION_ADDRESS, 0xBC); //47*4
	//__HAL_SYSCFG_REMAPMEMORY_SRAM();
	__set_MSP(appStack);
	appEntry();
}

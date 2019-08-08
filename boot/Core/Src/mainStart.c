#include "mainStart.h"

typedef void (*pFunction)(void);

void bootMain(void)
{
	//HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuff, sizeof(rxBuff));
	uint8_t buf;

	Flash_If_Read(&buf,eepStartAddress,1);

	if(buf == bootEnter){
		bootMode();
	}else{
		jumpToApp();
	}

	while(1){
		HAL_Delay(500);
	}

}

void jumpToApp(void)
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

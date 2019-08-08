/*
 * flash.c
 *
 *  Created on: 2019¦~7¤ë25¤é
 *      Author: Andywa
 */
#include "flash.h"


HAL_StatusTypeDef Flash_If_Read(uint8_t* buff, uint32_t dest_addr, uint32_t Len)
{
    uint32_t i;

    if( dest_addr >= eepStartAddress){
		for(i = 0; i < Len; i++){
				buff[i] = *(__IO uint8_t*)(dest_addr + i);
		}
		return HAL_OK;
    }else{
    	return HAL_ERROR;
    }
}

HAL_StatusTypeDef Flash_If_Write(uint8_t *src, uint32_t dest_addr, uint32_t Len)
{
  uint32_t i = 0;

  for(i = 0; i < Len; i++)
  {
	  if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, (uint32_t)(dest_addr+i*2), *(uint64_t*)(src)) != HAL_OK){
		  return HAL_ERROR;
	  }
  }
  return HAL_OK;
}

HAL_StatusTypeDef Flash_If_Erase(uint32_t Add, uint8_t pageSize)
{
  uint32_t PageError = 0;
  FLASH_EraseInitTypeDef eraseinitstruct;
  HAL_StatusTypeDef sta;

  /* Clear OPTVERR bit set on virgin samples */
  //__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

   /* Get the number of sector to erase from 1st sector*/
  eraseinitstruct.TypeErase = FLASH_TYPEERASE_PAGES;
  eraseinitstruct.PageAddress = Add;
  eraseinitstruct.NbPages = pageSize;
  sta = HAL_FLASHEx_Erase(&eraseinitstruct, &PageError);

  return sta;
}

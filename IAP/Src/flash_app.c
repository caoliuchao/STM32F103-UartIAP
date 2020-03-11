/**
  ******************************************************************************
  * @file    STM32F1xx_IAP/src/flash_app.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "flash_app.h"
#include <stdbool.h>

/** @addtogroup STM32F1xx_IAP
  * @{
  */
 
/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
bool FLASH_APP_Erase(uint32_t StartSector)
{
    uint32_t flashaddress;
  
    FLASH_Unlock();  //解除STM32的FALSH写保护
    
    flashaddress = StartSector;
  
    while (flashaddress <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS)
    {
        if (FLASH_ErasePage(flashaddress) == FLASH_COMPLETE)
        {
            flashaddress += FLASH_PAGE_SIZE;
        }
        else
        {
            /* Error occurred while page erase */
            return (false);
        }
    }
    
    FLASH_Lock(); //使能STM32的FALSH写保护
    
    return (true);
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)   
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_APP_Write(uint32_t FlashAddress, uint32_t* Data ,uint16_t DataLength)
{
    uint32_t i = 0;
    
    /* Unlock the Program memory */
    FLASH_Unlock();

    /* Clear all FLASH flags */  
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_BSY);   
 
    for (i = 0; (i < DataLength) && (FlashAddress <= (USER_FLASH_END_ADDRESS-4)); i++)
    {
        /* the operation will be done by word */ 
        if (FLASH_ProgramWord(FlashAddress, *(uint32_t*)(Data+i)) == FLASH_COMPLETE)
        {
            /* Check the written value */
            if (*((uint32_t*)FlashAddress) != *(uint32_t*)(Data+i))
            {
                /* Flash content doesn't match SRAM content */
                return(2);
            }
            
            /* Increment FLASH destination address */
            FlashAddress += 4;
        }
        else
        {
            /* Error occurred while writing data in Flash memory */
           return (1);
        }
    }
    
    /* Unlock the Program memory */
    FLASH_Lock(); 
    
    return (0);
}
/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

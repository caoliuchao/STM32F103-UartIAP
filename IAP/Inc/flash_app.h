/**
  ******************************************************************************
  * @file    STM32F1xx_IAP/inc/flash_if.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-May-2012
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_APP_H
#define __FLASH_APP_H

#ifdef __cplusplus
extern "C"
#endif

/* Includes ------------------------------------------------------------------*/
#include "STM32f10x.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define     USER_FLASH_LAST_PAGE_ADDRESS   0x0807F800   //最后一页FALSH的起始地址
#define     USER_FLASH_START_PAGE_ADDRESS  0x08010000   //APP程序开始页的起始地址
#define     USER_FLASH_END_ADDRESS         0x0807FFFF   //单片机的FLASH大小
#define     FLASH_PAGE_SIZE                0x800        //每页的FLASH大小

/* define the address from where user application will be loaded,
   the application address should be a start sector address */
#define     APPLICATION_ADDRESS           (uint32_t)USER_FLASH_START_PAGE_ADDRESS 

/* define the user application size */
#define     APPLICATION_FLASH_SIZE        (USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS + 1)

/* Get the number of Sector from where the user program will be loaded */
#define     APPLICATION_PAGE_NUMBER       (uint32_t)(APPLICATION_FLASH_SIZE >> 12)

/* define the user application size */
#define    USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - APPLICATION_ADDRESS + 1)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
bool     FLASH_APP_Erase(uint32_t StartSector);
uint32_t FLASH_APP_Write(uint32_t FlashAddress, uint32_t* Data, uint16_t DataLength);

#ifdef __cplusplus
extern "C"
#endif

#endif  /* __FLASH_APP_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


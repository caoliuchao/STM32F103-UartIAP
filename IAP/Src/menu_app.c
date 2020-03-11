/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/menu_app.c 
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
#include "menu_app.h"
#include "uart_app.h"
#include "ymodem.h"

/** @addtogroup STM32F0xx_IAP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction   Jump_To_Application;
uint32_t    JumpAddress;
uint32_t    FlashProtection = 0;
uint8_t     tab_1024[1024] = { 0 };
uint8_t     FileName[FILE_NAME_LENGTH];


/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(void)
{
    uint8_t Number[10] = {0};
    int32_t Size = 0;
    
    SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
    Size = Ymodem_Receive(&tab_1024[0]);
    if (Size > 0)
    {
        SerialPutString("\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
        SerialPutString(FileName);
        Int2Str(Number, Size);
        SerialPutString("\n\r Size: ");
        SerialPutString(Number);
        SerialPutString(" Bytes\r\n");
        SerialPutString("-------------------\n");
    }
    else if (Size == -1)
    {
        SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
    }
    else if (Size == -2)
    {
        SerialPutString("\n\n\rVerification failed!\n\r");
    }
    else if (Size == -3)
    {
        SerialPutString("\r\n\nAborted by user.\n\r");
    }
    else
    {
        SerialPutString("\n\rFailed to receive the file!\n\r");
    }
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(void)
{
    uint8_t status = 0 ; 
    
    SerialPutString("\n\n\rSelect Receive File\n\r");
    
    if (Serial_GetKey() == CRC16)
    {
        /* Transmit the flash image through ymodem protocol */
        status = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", USER_FLASH_SIZE);
    
        if (status != 0) 
        {
            SerialPutString("\n\rError Occurred while Transmitting File\n\r");
        }
        else
        {
            SerialPutString("\n\rFile uploaded successfully \n\r");
        }
    }
}

/***********************************************************************
*   函数名: Jump_to_APP
*   功  能: IAP跳转到APP函数
*   输  入:   
*           无 
*   输  出:   
*           无
***********************************************************************/
void Jump_To_App(void)
{
    uint32_t index = 0; 
    
    NVIC->ICER[0] = 0xFFFFFFFF; 
    NVIC->ICER[1] = 0x000007FF; 
    NVIC->ICPR[0] = 0xFFFFFFFF; 
    NVIC->ICPR[1] = 0x000007FF; 
    
    for(index = 0; index < 0x0B; index++) 
    { 
        NVIC->IP[index] = 0x00000000; 
    } 
    
    __set_PRIMASK(1); //IAP关中断 APP如果没用UCOS系统，APP初始化后要开中断 用UCOS后，在起动任务后会开中断
    
    /* Jump to user application */
    JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
    
    /* Jump to application */
    Jump_To_Application();
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

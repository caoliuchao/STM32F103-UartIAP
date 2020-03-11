/**************************************************************************
 * @文件  : main.c
 * @作者  : caochao
 * @日期  : 10-1-2018
 * @摘要  : 这个C文件时实现了系统的初始化和ucosII的启动
 *
 * 修改人 :
 *  日期  :
 *
 * 修改人 :
 *  日期  :
 **************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "rcc.h"
#include "menu_app.h"
#include "uart_app.h"

/**************************************************************************
* 函数名:  main
* 功  能:  程序的主函数
* 输  入:   
*         无 
* 输  出:   
*         有
**************************************************************************/
int main(void)
{
    uint8_t dataBuf[32] = {0};
    
    RCC_Configuration();         //初始化系统时钟
    IAP_UART_Init();             //初始化IAP所需的uart
    
	while(1)
	{
        SerialPutString("\r\n======================================================================");
        SerialPutString("\r\n=              (C) COPYRIGHT 2012 STMicroelectronics                 =");
        SerialPutString("\r\n=                                                                    =");
        SerialPutString("\r\n=  STM32F0xx In-Application Programming Application  (Version 1.0.0) =");
        SerialPutString("\r\n=                                                                    =");
        SerialPutString("\r\n=                                   By MCD Application Team          =");
        SerialPutString("\r\n======================================================================");
        SerialPutString("\r\n\r\n");
        
        SerialPutString("input string \"update\" or \"UPDATE\" for update IAP.\r\n");
        SerialPutString("input othre string for not update IAP.\r\n");
        
        Serial_GetInputString (dataBuf);
        if (strstr((const char *)dataBuf,"update") != NULL ||
            strstr((const char *)dataBuf,"UPDATE") != NULL)
        {
            SerialPutString("\r\n================== Main Menu ============================\r\n\n");
            SerialPutString("  Download Image To the STM32F10x Internal Flash ------- 1\r\n\n");
            SerialPutString("  Upload Image From the STM32F10x Internal Flash ------- 2\r\n\n");
            SerialPutString("  Execute The New Program ------------------------------ 3\r\n\n");
            
            SerialPutString("==========================================================\r\n\n");
    
            /* Download user application in the Flash */
            SerialDownload();
            
            Jump_To_App();
        }
        else
        {
            Jump_To_App();
        }
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {
		printf("Wrong parameters value: file %s on line %d\r\n", file, line);
    }
}
#endif

/**
  * @}
  */

/***********************************文件结束***************************************/



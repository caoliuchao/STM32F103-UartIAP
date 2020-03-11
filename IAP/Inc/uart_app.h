/**********************************************************************
* @文件  : usart.h
* @作者  : caochao
* @日期  : 10-1-2018
* @摘要  : 这个h文件时定义usart的printf函数的声明
* 修改人 :
*  日期  :
*
* 修改人 :
*  日期  :
***********************************************************************/
/* 定义防止递归的包容 */
#ifndef _UART_APP_H
#define _UART_APP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include <stdio.h>
	
/*-------------------------USART的相关宏定义----------------------------*/
#define  USART1_PORT         USART1
#define  USART1_PERIPH       RCC_APB2Periph_USART1
#define  USART1_BaudRate     57600

#define  USART1_TX_PORT      GPIOA
#define  USART1_TX_PIN       GPIO_Pin_9
#define  USART1_TX_PERIPH    RCC_APB2Periph_GPIOA

#define  USART1_RX_PORT      GPIOA
#define  USART1_RX_PIN       GPIO_Pin_10
#define  USART1_RX_PERIPH    RCC_APB2Periph_GPIOA     

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Constants used by Serial Command Line Mode */
#define CMD_STRING_SIZE       128
/* Exported macro ------------------------------------------------------------*/

/* Common routines */
#define IS_AF(c)             ((c >= 'A') && (c <= 'F'))
#define IS_af(c)             ((c >= 'a') && (c <= 'f'))
#define IS_09(c)             ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)        IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)        IS_09(c)
#define CONVERTDEC(c)        (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)        (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#define SerialPutString(x)   Serial_PutString((uint8_t*)(x))
/*--------------------------函数的声明----------------------------------*/ 
void        IAP_UART_Init(void);
uint8_t     Serial_GetKey(void);
void        Serial_PutChar(uint8_t ch);
uint32_t    SerialKeyPressed(uint8_t *key);
void        Serial_PutString(uint8_t *str);	 
void        Int2Str(uint8_t* str,int32_t intnum);
uint32_t    Str2Int(uint8_t *inputstr,int32_t *intnum);
void        Serial_GetInputString (uint8_t * buffP);

#ifdef __cplusplus
}
#endif

#endif /* _USART_H */
/*************************************文本结束**************************/


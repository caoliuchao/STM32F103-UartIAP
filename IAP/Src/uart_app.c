/**
  ******************************************************************************
  * @file    STM32F0xx_IAP/uart_app.c 
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
#include "uart_app.h"
#include "stm32f10x.h"

/**
  * @brief  Initialize the IAP.
  * @param  None
  * @retval None
  */
void IAP_UART_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(USART1_TX_PERIPH,ENABLE);   //打开GPIO的时钟
    RCC_APB2PeriphClockCmd(USART1_RX_PERIPH,ENABLE);   //打开GPIO的时钟
    RCC_APB2PeriphClockCmd(USART1_PERIPH,ENABLE);      //打开usart1时钟    
    
    GPIO_InitStructure.GPIO_Pin	= USART1_TX_PIN;         //USART的TX为复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
	GPIO_Init(USART1_TX_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin	= USART1_RX_PIN ;         //USART的RX为复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USART1_RX_PORT,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = USART1_BaudRate ;          //波特率设置
	USART_InitStructure.USART_WordLength  = USART_WordLength_8b;     //发送数据为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           //停止位为1
	USART_InitStructure.USART_Parity = USART_Parity_No;              //不进行奇偶位检测
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流
    USART_InitStructure.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;  //允许usart接受和发送数据
    
    USART_Init(USART1_PORT,&USART_InitStructure); //初始化usart 
	
	USART_Cmd(USART1_PORT,ENABLE);  //启动usart  
}

/**
  * @brief  Test to see if a key has been pressed on the HyperTerminal
  * @param  key: The key pressed
  * @retval 1: Correct
  *         0: Error
  */
uint32_t SerialKeyPressed(uint8_t *key)
{
    if ( USART_GetFlagStatus(USART1_PORT, USART_FLAG_RXNE) != RESET)
    {
        *key = USART_ReceiveData(USART1_PORT);
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  Get a key from the HyperTerminal
  * @param  None
  * @retval The Key Pressed
  */
uint8_t Serial_GetKey(void)
{
    uint8_t key = 0;

    /* Waiting for user input */
    while (USART_GetFlagStatus(USART1_PORT, USART_FLAG_RXNE) == RESET)
    {
        ;
    }
    
    key = USART_ReceiveData(USART1_PORT);
    
    return key;
}

/**
  * @brief  Print a character on the HyperTerminal
  * @param  c: The character to be printed
  * @retval None
  */
void Serial_PutChar(uint8_t ch)
{ 
    while (USART_GetFlagStatus(USART1_PORT,USART_FLAG_TC) == RESET)
    {
        ;
    }
    
    USART_SendData(USART1_PORT,ch);
}

/**
  * @brief  Print a string on the HyperTerminal
  * @param  s: The string to be printed
  * @retval None
  */
void Serial_PutString(uint8_t *str)
{
    while (*str != '\0')
    {
        while (USART_GetFlagStatus(USART1_PORT,USART_FLAG_TC) == RESET)
        {
            ;
        }
        
        USART_SendData(USART1_PORT,(uint8_t)*str);
    
        str++;
    }
}

/**
  * @brief  Get Input string from the HyperTerminal
  * @param  buffP: The input string
  * @retval None
  */
void Serial_GetInputString (uint8_t * buffP)
{
    uint32_t bytes_read = 0;
    uint8_t c = 0;
    
    do
    {
        c = Serial_GetKey();
        if (c == '\n')
        {
            buffP[bytes_read++] = c;
            Serial_PutChar(c);
            
            break;
        }
        
        if (c == '\b') /* Backspace */
        {
            if (bytes_read > 0)
            {
                Serial_PutString("\b \b");
                bytes_read --;
            }
            continue;
        }
        
        if (bytes_read >= CMD_STRING_SIZE )
        {
            Serial_PutString("Command string size overflow\r\n");
            bytes_read = 0;
            continue;
        }
        
        if (c >= 0x20 && c <= 0x7E)
        {
            buffP[bytes_read++] = c;
            Serial_PutChar(c);
        }
    }while (1);
    
    Serial_PutString("\r\n");
    buffP[bytes_read] = '\0';
}

/** @addtogroup STM32F0xx_IAP
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Convert an Integer to a string
  * @param  str: The string
  * @param  intnum: The intger to be converted
  * @retval None
  */
void Int2Str(uint8_t* str, int32_t intnum)
{
    uint32_t i, Div = 1000000000, j = 0, Status = 0;
    
    for (i = 0; i < 10; i++)
    {
        str[j++] = (intnum / Div) + 48;
    
        intnum = intnum % Div;
        Div /= 10;
        if ((str[j-1] == '0') & (Status == 0))
        {
            j = 0;
        }
        else
        {
            Status++;
        }
    }
}

/**
  * @brief  Convert a string to an integer
  * @param  inputstr: The string to be converted
  * @param  intnum: The intger value
  * @retval 1: Correct
  *         0: Error
  */
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
    uint32_t i = 0, res = 0;
    uint32_t val = 0;
    
    if (inputstr[0] == '0' && (inputstr[1] == 'x' || inputstr[1] == 'X'))
    {
        if (inputstr[2] == '\0')
        {
            return 0;
        }
        for (i = 2; i < 11; i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                /* return 1; */
                res = 1;
                break;
            }
            if (ISVALIDHEX(inputstr[i]))
            {
                val = (val << 4) + CONVERTHEX(inputstr[i]);
            }
            else
            {
                /* return 0, Invalid input */
                res = 0;
                break;
            }
        }
        /* over 8 digit hex --invalid */
        if (i >= 11)
        {
            res = 0;
        }
    }
    else /* max 10-digit decimal input */
    {
        for (i = 0;i < 11;i++)
        {
            if (inputstr[i] == '\0')
            {
                *intnum = val;
                /* return 1 */
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0))
            {
                val = val << 10;
                *intnum = val;
                res = 1;
                break;
            }
            else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0))
            {
                val = val << 20;
                *intnum = val;
                res = 1;
                break;
            }
            else if (ISVALIDDEC(inputstr[i]))
            {
                val = val * 10 + CONVERTDEC(inputstr[i]);
            }
            else
            {
                /* return 0, Invalid input */
                res = 0;
                break;
            }
        }
        /* Over 10 digit decimal --invalid */
        if (i >= 11)
        {
            res = 0;
        }
    }
    
    return res;
}


/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

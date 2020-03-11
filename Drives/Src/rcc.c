/**************************************************************************
* @�ļ�  : rcc.c
* @����  : caochao
* @����  : 10-1-2018
* @ժҪ  : ���C�ļ�������ϵͳʱ�ӵ����õ�ʵ��
* �޸��� :
*  ����  :
*
* �޸��� :
*  ����  :
************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "rcc.h"

/*************************************************************************
*   ������:   RCC_Configuration
*   ��  ��:   ����STM32ϵͳʱ��
*   ��  ��:  
*             ��
*   ��  ��:  
*             ��
*
************************************************************************/
void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;
	
	RCC_DeInit();                           //RCC�Ĵ�����ʼ��                  
	RCC_HSEConfig(RCC_HSE_ON);             //���ⲿ���پ���     
	HSEStartUpStatus = RCC_WaitForHSEStartUp();   //�ȴ��ⲿ���پ�������  
    
	if (HSEStartUpStatus == SUCCESS)        //�ж��ⲿ���پ����Ƿ�����ɹ�
	{
		RCC_HCLKConfig( RCC_SYSCLK_Div1);      //����AHBʱ�ӣ�HCLK��   
		RCC_PCLK1Config(RCC_HCLK_Div2);        //���õ���AHBʱ�ӣ�PCLK1��   
		RCC_PCLK2Config(RCC_HCLK_Div1);        //���ø���AHBʱ�ӣ�PCLK2��    
		
		FLASH_SetLatency(FLASH_Latency_2);                         
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);      
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);   //����PLLʱ��Դ����Ƶϵ��
		RCC_PLLCmd(ENABLE);                                   //ʹ��PLLʱ��
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
			;                       //���ָ����RCC��־λ�������,PLL����
		} 
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);    //����ϵͳʱ�ӣ�SYSCLK��
		while (RCC_GetSYSCLKSource() != 0x08)
		{
			;                       //��������ϵͳʱ�ӵ�ʱ��Դ,0x08��PLL��Ϊϵͳʱ�� 
		}			
	}
}

/********************************�ļ�����*************************************/


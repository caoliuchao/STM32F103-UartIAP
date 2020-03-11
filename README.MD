

**如果你的串口与本工程不太一样，需要根据自己的STM32芯片串口进行修改。你只需要要修改uart.h即可。**

```C
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
```

**你还需要修改IAP_UART_Init(void)这个函数，按照你的STM32芯片修改。**

```
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
```

**STM32芯片FLASH的信息对于APP更新很重要，你需要按照你的STM32修改flah_app.h文件中的四个宏定义。**

```c
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define     USER_FLASH_LAST_PAGE_ADDRESS   0x0807F800   //最后一页FALSH的起始地址
#define     USER_FLASH_START_PAGE_ADDRESS  0x08010000   //APP程序开始页的起始地址
#define     USER_FLASH_END_ADDRESS         0x0807FFFF   //单片机的FLASH大小
#define     FLASH_PAGE_SIZE                0x800        //每页的FLASH大小
```


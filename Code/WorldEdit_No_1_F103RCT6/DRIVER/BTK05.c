/************************************************************************************
*  Copyright (c), 2019, LXG.
*
* FileName		:BTK05.c
* Author		:firestaradmin
* Version		:1.0
* Date			:2019.
* Description	:蓝牙键盘模块的功能
* History		:

2019.12.13		：测试AT指令发送并返回OK  弄了半天的串口发送，因为蓝牙模块的串口接受一个字符后需要延时一会，不然反应不过来。
*
*
*************************************************************************************/
#include "main.h"
#include "BTK05.h"

unsigned char BTK05_ATKeyDataPack[12] = {
							BTK05_CMD_BYTE1	,
							BTK05_CMD_BYTE2	,
							BTK05_CMD_BYTE3	,
							BTK05_CMD_BYTE4	,
							0x00 ,
							BTK05_CMD_BYTE6	,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 		};

unsigned char ATReturnSuccessedFlag = 0;//AT返回成功标志位
unsigned char RxBuffer[50] ;
unsigned char RxBuffer_Tail = 0;
unsigned char RxBuffer_OK[10] ;//接收AT指令返回的OK
unsigned char RxBuffer_OK_Tail = 0;

unsigned char BTK05_ConsumerPack[8] = 	{	//Consumer键值数据包  音量加减之类的功能键
								0x08,
								0x00,
								0xA1,
								0x03,
								0x00,
								0x00,
								0x00,
								0x00,
	
										};							
							
enum BTK05_StatusTypedef BTK05_Status = BTK_SLEEP;					


void BTK05_UART_SendChar(unsigned char txChar);

void BTK05_Init()
{
	BTK05_UART_Init();
	BTK05_WAKEUP_Init();
	BTK05_ATMode_Init();
	BTK05_LowEnerageMode();//进入省电模式
}


//return 1  AT设置成功
//return 0  AT设置失败
unsigned char BTK05_UART_SendATCmd(unsigned char* ATBuffer)
{
	unsigned char timeOutTemp = 0;
	while(*ATBuffer != '\0')
	{
		BTK05_UART_SendChar(*ATBuffer++);
		DelayUs(500);
	}
	BTK05_UART_SendChar(0x0D);
	DelayUs(500);
	BTK05_UART_SendChar(0x0A);
	DelayUs(500);
	while(!ATReturnSuccessedFlag)//等待串口
	{
		DelayMs(1);
		timeOutTemp++;
		if(timeOutTemp == 200)return 0;//AT设置失败  TimeOut
	}
	
	if(RxBuffer_OK[0] == 'O' && RxBuffer_OK[1] == 'K')
	{
		ATReturnSuccessedFlag = 0;
		RxBuffer_OK_Tail = 0;
		return 1;//AT设置成功
	}
	ATReturnSuccessedFlag = 0;
	RxBuffer_OK_Tail = 0;
	return 0;//AT设置失败
}

void BTK05_UART_SendKeyData(unsigned char* KeyDataBuffer, unsigned char byte_lenth)
{
	unsigned char i;
	for(i = 0; i < byte_lenth; i++)
	{
		BTK05_UART_SendChar(*(KeyDataBuffer+i));
	}
}

void BTK05_UART_SendChar(unsigned char txChar)
{

	USART_SendData(BTK05_UART, txChar);	
	while(USART_GetFlagStatus(BTK05_UART, USART_FLAG_TC) == RESET);
	USART_ClearFlag(BTK05_UART,USART_FLAG_TC);

	
}


void BTK05_UART_SendString(unsigned char* txBuffer)
{
	//unsigned char txCharTemp;
	while(*txBuffer++ != '\0')
	{
		BTK05_UART_SendChar(*txBuffer);
	}
}


void BTK05_PairMode()//进入匹配模式
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_ENPairMode);
		DelayMs(500);
		BTK05_KEYMode();
	}
}

void BTK05_LowEnerageMode()//进入省电模式
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_SLEEPMODE);
		DelayMs(500);
		BTK05_KEYMode();
	}
}
void BTK05_RESET()//复位
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_RESET);
		DelayMs(500);
		BTK05_KEYMode();
	}
}

void BTK05_DeleteConnectInfo()//删除 已经连接的主机信息
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_DeletePaired);
		DelayMs(500);
		BTK05_KEYMode();
	}
}


//唤醒BTK05
void BTK05_Wake()
{
	GPIO_SetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	BTK05_Status = BTK_WAKE;
	DelayMs(20);
	
}
//休眠BTK05
void BTK05_Sleep()
{
	GPIO_ResetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	BTK05_Status = BTK_SLEEP;
	DelayMs(20);
	
}

//进入AT指令模式
unsigned char BTK05_ATMode()
{

	GPIO_SetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	DelayMs(400);
	GPIO_ResetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	return BTK05_UART_SendATCmd((unsigned char*)"AT");
}


//退出AT指令模式
unsigned char BTK05_KEYMode()
{
	 return BTK05_UART_SendATCmd((unsigned char*)"AT+EXIT");
}
















//BTK05_UART串口中断服务程序
void USART1_IRQHandler(void)                    
{
	unsigned char temp;
    if(USART_GetITStatus(BTK05_UART, USART_IT_RXNE) != RESET)  //接收中断
    {
		temp = USART_ReceiveData(BTK05_UART);
		RxBuffer_OK[RxBuffer_OK_Tail++] = temp;
		
		if(temp == '\n')
		{
			ATReturnSuccessedFlag = 1;
		}		
    } 

	
}





//********************************************************************************************************
//========================================初始化=======================================================

//休眠引脚初始化
void BTK05_WAKEUP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTK05_WAKEUP_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	GPIO_Init(BTK05_WAKEUP_GPIOPort, &GPIO_InitStructure); 
	
	GPIO_SetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	
}
//AT模式引脚初始化
//平时低电平，高电平脉冲进入命令模式，可以通过 AT 指令配置参数。
void BTK05_ATMode_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTK05_ATMode_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	GPIO_Init(BTK05_WAKEUP_GPIOPort, &GPIO_InitStructure); 
	
	GPIO_ResetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	
}



void BTK05_UART_Init()
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(BTK05_URAT_Clock, ENABLE);
	USART_DeInit(BTK05_UART);

	//USART1端口配置
	//UASART_TX   PA9
	GPIO_InitStructure.GPIO_Pin = BTK05_URAT_TX_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
	GPIO_Init(BTK05_URAT_GPIOPort, &GPIO_InitStructure); //初始化PA9
	//USART1_RX      PA10
	GPIO_InitStructure.GPIO_Pin = BTK05_URAT_RX_GPIOPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(BTK05_URAT_GPIOPort, &GPIO_InitStructure);  //初始化PA10

	//USART1 初始化设置
	USART_InitStructure.USART_BaudRate = BTK05_URAT_BaudRate;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式     
	USART_Init(BTK05_UART, &USART_InitStructure); //初始化串口1

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = BTK05_UART_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;        //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);    //根据指定的参数初始化VIC寄存器


	USART_ClearITPendingBit(BTK05_UART,USART_IT_TC);
	USART_ClearITPendingBit(BTK05_UART,USART_IT_TXE);//清除发送中断标志位
	USART_ITConfig(BTK05_UART, USART_IT_RXNE, ENABLE);//开启相关中断
	//USART_ITConfig(BTK05_UART, USART_IT_TXE, ENABLE);
	USART_ClearFlag(BTK05_UART,USART_FLAG_TC);
	
	USART_Cmd(BTK05_UART, ENABLE);  //使能BTK05_UART串口
}


//********************************************************************************************************






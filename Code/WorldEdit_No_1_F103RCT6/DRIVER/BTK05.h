#ifndef __BTK05_H_
#define __BTK05_H_

//串口默认参数： 波特率 9600， 8 位数据位， 1 位停止位， 无校验， 无流控。
#define BTK05_URAT_Clock		RCC_APB2Periph_USART1
#define BTK05_UART				USART1
#define BTK05_URAT_GPIOPort		GPIOA
#define BTK05_URAT_RX_GPIOPin	GPIO_Pin_10
#define BTK05_URAT_TX_GPIOPin	GPIO_Pin_9
#define BTK05_URAT_BaudRate		9600
#define BTK05_UART_IRQn			USART1_IRQn


#define BTK05_ATMode_GPIOPort	GPIOA
#define BTK05_ATMode_GPIOPin	GPIO_Pin_6
#define BTK05_WAKEUP_GPIOPort	GPIOA
#define BTK05_WAKEUP_GPIOPin	GPIO_Pin_7
//*********************************************************************************************
//键盘数据包格式  12个字节
#define BTK05_CMD_BYTE1	0x0C
#define BTK05_CMD_BYTE2	0x00
#define BTK05_CMD_BYTE3	0xA1
#define BTK05_CMD_BYTE4	0x01
#define BTK05_CMD_BYTE6	0x00
extern unsigned char BTK05_ATKeyDataPack[12];
//BYTE5  变动值（ALT、SHIFT、CTRL、GUI 按键状态指示）
//BYTE5 说明:
//Bit  	Key
//0  	LEFT CTRL
//1  	LEFT SHIFT
//2  	LEFT ALT
//3  	LEFT GUI
//4  	RIGHT CTRL
//5  	RIGHT SHIFT
//6  	RIGHT ALT
//7  	RIGHT GUI

extern unsigned char BTK05_ConsumerPack[8];

enum BTK05_StatusTypedef
{
	BTK_SLEEP = 0,
	BTK_WAKE = 1,
	
};

extern enum BTK05_StatusTypedef BTK05_Status;
//*********************************************************************************************
//AT指令	
//所有指令都必须在命令模式下才可以发送， 否则不会有任何响应。 所有 AT 指令都以回车换行符结
//束， 就是\r\n (0x0D 0x0A)， 返回的应答也以回车换行符结束。

//-----------------------------------
//模块在连接状态或者不可发现状态，通过这个指令，让模块进入允许匹配状态，这个指令不会删除之前
//的匹配信息，可用于多主机的匹配。
#define BTK05_AT_ENPairMode			"AT+PAIR"	//进入匹配模式
//-----------------------------------
//模块会记忆已经匹配的主机，通过这个指令，清除匹配信息，这样模块就可以接受新的主机进行匹配。
#define BTK05_AT_DeletePaired		"AT+UNPLUG"	//删除已经匹配的信息
//-----------------------------------
#define BTK05_AT_SLEEPMODE  		"AT+SLEEPMODE=1"//0 不休眠，串口随时可以接收数据		1 串口是否休眠，受到 PIO11 的控制。
//-----------------------------------
#define BTK05_AT_RESET				"AT+RESET"

//return 1  AT设置成功
//return 0  AT设置失败
unsigned char BTK05_UART_SendATCmd(unsigned char* ATBuffer);


//发送键盘数据包
void BTK05_UART_SendKeyData(unsigned char* KeyDataBuffer, unsigned char byte_lenth);


//-----------------------------------
//1． 外部处理器置PIO11 高电平。
//2． 置 PIO11 高电平后至少延时 10ms 后，外部处理器开始发送 UART 数据。
//3． 外部处理器无发送数据时 延时 10ms，置 PIO11 低电平，以进入省电模式
void BTK05_Wake(void);
void BTK05_Sleep(void);
unsigned char BTK05_ATMode(void);//进入AT指令模式
unsigned char BTK05_KEYMode(void);//退出AT指令模式
void BTK05_PairMode(void);//进入匹配模式
void BTK05_RESET(void);//复位
void BTK05_DeleteConnectInfo(void);//删除 已经连接的主机信息
void BTK05_LowEnerageMode(void);//进入省电模式


void BTK05_WAKEUP_Init(void);//WAKEIO 口 初始化 
void BTK05_ATMode_Init(void);//AT IO 口 初始化 
void BTK05_Init(void);//BTK——05初始化 
void BTK05_UART_Init(void);//串口初始化
//串口1中断服务程序
void USART1_IRQHandler(void)  ;



#endif



#ifndef __LED_H_
#define __LED_H_
#include "main.h"
#define LED_LOGO_GPIOClock		RCC_APB2Periph_GPIOB
#define LED_LOGO_GPIOPort		GPIOB
#define LED_LOGO_GPIOPin		GPIO_Pin_0

#define LED_HTK_I2C				I2C1
#define LED_HTK_PIN_GPIOPort	GPIOB
#define LED_HTK_SDA_GPIOPin		GPIO_Pin_7
#define LED_HTK_SCL_GPIOPin		GPIO_Pin_6

 



//HTK地址：0x1110 0000   ;1 1 1 0 A2 A1 A0 R/W B
//读 	0x1110 0001 B
//写 	0x1110 0000 B
//当 A2~A0  浮空时， A2~A0  都被设为 “0” 
#define LED_HTK_Address_Base	0xE0
#define LED_HTK_Address_Wirte	LED_HTK_Address_Base | 0x00
#define LED_HTK_Address_Read	LED_HTK_Address_Base | 0x01


#define LED_HTK_CMD_START			0x21//开启芯片时钟
#define LED_HTK_CMD_SLEEP			0x20//关闭芯片时钟


//低四位立即数，A0~A3，被传送至地址指针用于定义 16 个显示RAM 地址之一
//若显示数据寄存器地址 An 的范围是 0x00H~ 0x0FH，当到达存储器地址 0x0FH 时，地址指针返回0x00H。
#define LED_HTK_CMD_SetRamAddr		0x00   //设置ram地址指针为0x00

#define LED_HTK_CMD_DisplayOff		0x80	
#define LED_HTK_CMD_DisplayOn		0x81
#define LED_HTK_CMD_SetROWOut	 	0xA0 //设置位ROW 输出模式
#define LED_HTK_CMD_SetPWM100		0xEF //设置输出占空比为100


// 16×8 位静态 RAM 用于存储 LED 显示数据
//COM  	ROW0-7  ROW8-15
//COM0 	00H 	01H
//COM1 	02H 	03H
//COM2 	04H 	05H
//COM3 	06H 	07H
//COM4 	08H 	09H
//COM5 	0AH 	0BH
//COM6 	0CH 	0DH
//COM7 	0EH 	0FH

//电路上用了6个COM和16个ROW   用12个字节表示
//6行16列  12个字节
extern unsigned char LED_Ram[6][2];
extern unsigned char LED_BreathEfectFlag;
extern unsigned char LED_Brightness;
extern unsigned char LED_FlashSwitchFlag;
extern unsigned char LED_Status ;
//extern unsigned char LED_FlashSwitchFlag;

//0:关闭闪烁   1：闪烁2Hz  2：1Hz  3：0.5Hz
typedef enum 
{
	LED_FLASH_OFF = 0,
	LED_FLASH_2Hz = 1,
	LED_FLASH_1Hz = 2,
	LED_FLASH_HalfHz = 3
	
}LED_FlashPreqTypedef;




void LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color);
void LED_RamClearWith(unsigned char ledSwitch);

void LED_FreashRam(void);//将模拟显存数组写入HT16K33芯片
void LED_SetFlash(void);//闪烁开关
void LED_SetBreathEfect(void);//呼吸灯开关
void LED_Off(void);//关灯
void LED_Mode1(void);//全亮
void LED_Mode2(void);//亮WASD 上下左右
void LED_Mode3(void);//


void LED_BreathProcess(void);//呼吸灯处理函数
void LED_AllLightOn(void);//test
void LED_GoToSleep(void);//关闭时钟
void LED_WakeUp(void);//开启时钟
void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)	;//显示设置
void LED_SetBrightness(unsigned char brightness);//设置占空比 调节亮度


void LED_HT16K33_Init(void);//初始化芯片
void LED_LOGO_GPIO_Init(void);
//void I2C_WriteByte(uint8_t addr,uint8_t data);
void LED_I2C_Configuration(void);



//********************************************************************************************************
//IIC	
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define READ_SDA   GPIO_ReadInputDataBit(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)  //输入SDA 
#define IIC_SCL_H	GPIO_SetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SCL_GPIOPin)
#define IIC_SDA_H	GPIO_SetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)
#define IIC_SCL_L	GPIO_ResetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SCL_GPIOPin)
#define IIC_SDA_L	GPIO_ResetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)
void I2C_WriteByte(uint8_t addr,uint8_t data);
void LED_I2C_Configuration(void);       //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
 






#endif



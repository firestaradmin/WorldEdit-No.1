#include "main.h"
#include "LED.h"
#define delay_ms DelayMs
#define delay_us DelayUs

unsigned char LED_Ram[6][2] = {0};
unsigned char LED_Brightness = 8;
unsigned char LED_FlashSwitchFlag = 0;
unsigned char LED_BreathEfectFlag = 0;
unsigned char LED_Delt_Flag = 0;
unsigned char LED_Status = 0;

void LED_GoToSleep()
{
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SLEEP);//关闭芯片时钟
	//LED_Status = 0;
}

void LED_WakeUp()
{
	//LED_Status = 1;
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_START);//开启芯片时钟
}


void LED_RamClearWith(unsigned char ledSwitch)
{
	unsigned char i,j,temp;
	if(ledSwitch == 1)temp = 0xff;
	else	temp = 0x00;
	
	for(i = 0; i < 6; i++)//把12字节RAM显存写入芯片
	{
		for(j = 0; j < 2; j++)
		{
			LED_Ram[i][j] = temp; 						   
		}	
	}
}
	
/*********************************************
Function	:LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color);
Description:画点函数
Input	: 	unsigned char x, 	行 0-5
			unsigned char y, 	列 0-15
			unsigned char color	= 0：熄灭  ，1：点亮
Return	: void
Author	: firestaradmin
**********************************************/
//unsigned char LED_Ram[6][2] = {0};
void LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char lieByte = y / 8;
	unsigned char temp = LED_Ram[x][lieByte];
	if(color)
	{
		temp = temp | (0x01 << (y % 8));
		LED_Ram[x][lieByte] |= temp;
	}
	else
	{
		temp = temp & ~(0x01 << (y % 8));
		LED_Ram[x][lieByte] &= temp;
	}
	
	
}

//def: 0x80
//1 0 0 0 X B1 B0 D
//{D}
//只写
//定义显示开启 / 关闭状态
//● {0}：显示关闭
//● {1}：显示开启
//80H
//{B1,B0}
//只写
//定义闪烁频率
//● {0,0} = 闪烁关闭
//● {0,1} = 2Hz
//● {1,0} = 1Hz
//● {1,1} = 0.5Hz
/*********************************************
Function	:void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)
Description:
Input	: 	unsigned char displaySwitch = 0：关闭显示 或 1：开启显示 , 
			unsigned char displayFlashPreq = 	
										{	
											LED_FLASH_OFF = 0, 
											LED_FLASH_2Hz = 1,
											LED_FLASH_1Hz = 2,
											LED_FLASH_HalfHz = 3
										}
Return	: void
Author	: firestaradmin
**********************************************/
void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)	
{
	if(displaySwitch != 0)
	{
		switch (displayFlashPreq)
		{
			case LED_FLASH_OFF:
				I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOn);//开启显示
				break;
			case LED_FLASH_1Hz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x04));//开启显示
				break;
			case LED_FLASH_2Hz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x02));//开启显示
				break;
			case LED_FLASH_HalfHz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x06));//开启显示
				break;
			default:
				I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOn);//开启显示
				break;
					
		}
		
		
	}
	else 
	{
		I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOff);//关闭显示
	}
}

//def: 0xEF
//1 1 1 0 P3 P2 P1 P0
//{P3~P0}
//只写
//定义 ROW 驱动信号的脉宽
//● {0,0,0,0}：1/16duty
//● {0,0,0,1}：2/16duty
//● {0,0,1,0}：3/16duty
//● {0,0,1,1}：4/16duty
//● {0,1,0,0}：5/16duty
//● {0,1,0,1}：6/16duty
//● {0,1,1,0}：7/16duty
//● {0,1,1,1}：8/16duty
//● {1,0,0,0}：9/16duty
//● {1,0,0,1}：10/16duty
//● {1,0,1,0}：11/16duty
//● {1,0,1,1}：12/16duty
//● {1,1,0,0}：13/16duty
//● {1,1,0,1}：14/16duty
//● {1,1,1,0}：15/16duty
//● {1,1,1,1}：16/16duty
/*********************************************
Function	:void LED_SetBrightness(unsigned char brightness)
Description:
Input	: unsigned char brightness = 1~16  数字越大越亮
Return	: void
Author	: firestaradmin
**********************************************/
void LED_SetBrightness(unsigned char brightness)
{

	if(brightness > 15)	brightness = 15;
	
	I2C_WriteByte(LED_HTK_Address_Wirte,0xE0 | (brightness-1));
}

void LED_SetBreathEfect(void)
{
	if(LED_BreathEfectFlag == 1)
	{
		LED_BreathEfectFlag = 0;
		
	}
	else
	{
		LED_BreathEfectFlag = 1;
		LED_SetDisplay(1,LED_FLASH_OFF);
		LED_FlashSwitchFlag = 0;
	}
}

void LED_Mode3(void)
{
	LED_WakeUp();
	LED_RamClearWith(0);
	LED_DrawPoint(5,1,1);//W
	LED_DrawPoint(5,6,1);//Right
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}
void LED_Mode2(void)
{
	LED_WakeUp();
	LED_RamClearWith(0);
	LED_DrawPoint(2,2,1);//W
	LED_DrawPoint(3,1,1);//A
	LED_DrawPoint(3,2,1);//S
	LED_DrawPoint(3,3,1);//D
	
	LED_DrawPoint(4,12,1);//Up
	LED_DrawPoint(5,8,1);//Left
	LED_DrawPoint(5,9,1);//Down
	LED_DrawPoint(5,10,1);//Right
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}

void LED_Mode1(void)
{
	LED_WakeUp();
	LED_RamClearWith(1);
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}

void LED_Off(void)
{
	LED_GoToSleep();
	LED_BreathEfectFlag = 0;
	LED_Brightness = 8;
	LED_FlashSwitchFlag = 0;
	LED_Status = 0;
}

void LED_BreathProcess(void)
{
	
	if(LED_Delt_Flag == 1)
	{
		if(LED_Brightness <= 16)
		{
			LED_SetBrightness(LED_Brightness);
			LED_Brightness ++;
		}
		else
		{
			LED_Brightness = 16;
			LED_Delt_Flag = 0;
		}
		
		
	}
	else if(LED_Delt_Flag == 0)
	{
		if(LED_Brightness >= 1)
		{
			LED_SetBrightness(LED_Brightness);
			LED_Brightness --;
		}
		else
		{
			LED_Brightness = 1;
			LED_Delt_Flag = 1;
		}
	}
}

void LED_SetFlash(void)
{
	if(LED_FlashSwitchFlag == 1)
	{
		LED_SetDisplay(1,LED_FLASH_OFF);
		LED_FlashSwitchFlag = 0;
	}
	else
	{
		LED_SetDisplay(1,LED_FLASH_1Hz);
		LED_FlashSwitchFlag = 1;
		LED_BreathEfectFlag = 0;
	}
}

//unsigned char LED_Ram[6][2]
void LED_FreashRam()//将模拟显存数组写入HT16K33芯片
{
	u8 i,j;

	IIC_Start(); //IIC START开始信号 
	IIC_Send_Byte(LED_HTK_Address_Wirte); //带 R/W 位的从机地址
	if(!IIC_Wait_Ack())//等待ACK信号
	{
		return;
	}
	IIC_Send_Byte(LED_HTK_CMD_SetRamAddr); 	//设置RAM地址指针CMD					   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		
	for(i = 0; i < 6; i++)//把12字节RAM显存写入芯片
	{
		for(j = 0; j < 2; j++)
		{
			IIC_Send_Byte(LED_Ram[i][j]); 						   
			if(!IIC_Wait_Ack())
			{
				return;
			}  	
		}	
	}
	for(i = 0; i < 4 ; i++)//因为键盘上只是用了6行16列LED阵列，所以后面四个字节的RAM直接写入0x00就好了。
	{
		IIC_Send_Byte(0x00); 						   
		if(!IIC_Wait_Ack())
		{
			return;
		}  
	}
	
    IIC_Stop();
}



void LED_AllLightOn()
{
	u8 i;
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_START);
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetROWOut);
	
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetPWM100);
	I2C_WriteByte(LED_HTK_Address_Wirte,0x87);
	//I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetRamAddr);
	
	IIC_Start();  
	IIC_Send_Byte(LED_HTK_Address_Wirte); 
	if(!IIC_Wait_Ack())
	{
		return;
	}
	IIC_Send_Byte(LED_HTK_CMD_SetRamAddr); 						   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		
	for(i = 0; i < 16; i++)
	{
		IIC_Send_Byte(0xff); 						   
		if(!IIC_Wait_Ack())
		{
			return;
		}  		
	}
	
    IIC_Stop();
	
}


void LED_HT16K33_Init()//初始化芯片
{
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetROWOut);//设置位ROW 输出模式
	LED_RamClearWith(0);
	LED_FreashRam();
	LED_SetBrightness(LED_Brightness);
	LED_SetDisplay(0,LED_FLASH_OFF);
	
}
//********************************************************************************************************
//======================================LOGO——LED的IO口初始化=======================================================


void LED_LOGO_GPIO_Init()
{
	
	GPIO_InitTypeDef GPIOType = {
		
			LED_LOGO_GPIOPin,
			GPIO_Speed_50MHz,
			GPIO_Mode_Out_PP		//推挽输出
	};
	
	GPIO_Init(LED_LOGO_GPIOPort , &GPIOType);
}

//********************************************************************************************************
//======================================模拟IIC=======================================================


void LED_I2C_Configuration()
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = LED_HTK_SCL_GPIOPin|LED_HTK_SDA_GPIOPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_HTK_PIN_GPIOPort, &GPIO_InitStructure);
	
	IIC_SCL_H;
	IIC_SDA_H;
 
}



//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_L;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：0，接收应答失败
//        1，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA_H;delay_us(1);	   
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 0;
		}
	}
	IIC_SCL_L;//时钟输出0 	   
	return 1;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT(); 	    
    IIC_SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
		if((txd&0x80)>>7)
		{
			IIC_SDA_H;
		}
		else{
			IIC_SDA_L;
		}
       
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
	for(i=0;i<8;i++ )
	{
    IIC_SCL_L; 
    delay_us(2);
	IIC_SCL_H;
    receive<<=1;
    if(READ_SDA)receive++;   
	delay_us(1); 
	}					 
	if (!ack)
		IIC_NAck();//发送nACK
	else
		IIC_Ack(); //发送ACK   
	return receive;
}
 

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
	IIC_Start();  
	IIC_Send_Byte(addr); 
	if(!IIC_Wait_Ack())
	{
		return;
	}
	IIC_Send_Byte(data); 						   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		    	   
    IIC_Stop();

}
 

//uint16_t I2C_ReadByte(uint16_t addr,uint8_t device_addr,uint8_t ByteNumToRead)  //读寄存器或读数据
//{	
//		uint16_t data;
//		IIC_Start();  
//		if(device_addr==0xA0)
//			IIC_Send_Byte(0xA0 + ((addr/256)<<1));
//		else
//			IIC_Send_Byte(device_addr);	
//		IIC_Wait_Ack();
//		IIC_Send_Byte(addr&0xFF);   //发送低地址
//		IIC_Wait_Ack(); 
// 
//		IIC_Start();  	
//		IIC_Send_Byte(device_addr+1);	    //发器件地址
//		IIC_Wait_Ack();
//		if(ByteNumToRead == 1)//LM75温度数据为11bit
//		{
//			data=IIC_Read_Byte(0);
//		}
//		else
//			{
//				data=IIC_Read_Byte(1);
//				data=(data<<8)+IIC_Read_Byte(0);
//			}
//		IIC_Stop();//产生一个停止条件	    
//		return data;
//}


//********************************************************************************************************







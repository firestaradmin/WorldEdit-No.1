#include "main.h"
#include "myKeyBoard.h"
#include <string.h>

#define myKeyBoard_row_GPIOPort		GPIOA
#define myKeyBoard_row0_GPIOPin		GPIO_Pin_0
#define myKeyBoard_row1_GPIOPin		GPIO_Pin_1
#define myKeyBoard_row2_GPIOPin		GPIO_Pin_2
#define myKeyBoard_row3_GPIOPin		GPIO_Pin_3
#define myKeyBoard_row4_GPIOPin		GPIO_Pin_4
#define myKeyBoard_row5_GPIOPin		GPIO_Pin_5

#define myKeyBoard_col3_0_GPIOPort	GPIOB
#define myKeyBoard_col0_GPIOPort	GPIOB
#define myKeyBoard_col1_GPIOPort	GPIOB
#define myKeyBoard_col2_GPIOPort	GPIOB
#define myKeyBoard_col3_GPIOPort	GPIOB
#define myKeyBoard_col15_4_GPIOPort	GPIOC
#define myKeyBoard_col4_GPIOPort	GPIOC
#define myKeyBoard_col5_GPIOPort	GPIOC
#define myKeyBoard_col6_GPIOPort	GPIOC
#define myKeyBoard_col7_GPIOPort	GPIOC
#define myKeyBoard_col8_GPIOPort	GPIOC
#define myKeyBoard_col9_GPIOPort	GPIOC
#define myKeyBoard_col10_GPIOPort	GPIOC
#define myKeyBoard_col11_GPIOPort	GPIOC
#define myKeyBoard_col12_GPIOPort	GPIOC
#define myKeyBoard_col13_GPIOPort	GPIOC
#define myKeyBoard_col14_GPIOPort	GPIOC
#define myKeyBoard_col15_GPIOPort	GPIOC
#define myKeyBoard_col0_GPIOPin		GPIO_Pin_12
#define myKeyBoard_col1_GPIOPin		GPIO_Pin_13
#define myKeyBoard_col2_GPIOPin		GPIO_Pin_14
#define myKeyBoard_col3_GPIOPin		GPIO_Pin_15
#define myKeyBoard_col4_GPIOPin		GPIO_Pin_0
#define myKeyBoard_col5_GPIOPin		GPIO_Pin_1
#define myKeyBoard_col6_GPIOPin		GPIO_Pin_2
#define myKeyBoard_col7_GPIOPin		GPIO_Pin_3
#define myKeyBoard_col8_GPIOPin		GPIO_Pin_4
#define myKeyBoard_col9_GPIOPin		GPIO_Pin_5
#define myKeyBoard_col10_GPIOPin	GPIO_Pin_6
#define myKeyBoard_col11_GPIOPin	GPIO_Pin_7
#define myKeyBoard_col12_GPIOPin	GPIO_Pin_8
#define myKeyBoard_col13_GPIOPin	GPIO_Pin_9
#define myKeyBoard_col14_GPIOPin	GPIO_Pin_10
#define myKeyBoard_col15_GPIOPin	GPIO_Pin_11

#define myKeyBoard_ControlKey 0x00
#define myKeyBoard_SpecialKey 0x00

#define xxCK	myKeyBoard_ControlKey 
#define xxSK	myKeyBoard_SpecialKey 

const char * myKeyBoard_KeyMap_Name[6][16] = 
{
	"Esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","PrtSc","ScrollLock","PauseBreak",
	"~","!","@","#","$","%","^","&","*","(",")","-","+","BackSpace","Insert","Home",
	"Tab","Q","W","E","R","T","Y","U","I","O","P","{","}","|","Delete","End",
	"CapsLock","A","S","D","F","G","H","J","K","L",";","'","Enter","","","PageUp",
	"LShift","Z","X","C","V","B","N","M",",",".","/","RShift","Up","","","PageDown",
	"LCtrl","Win","LAlt","Space","RAlt","FN","Menu","RCtrl","Left","Down","Right","","","","",""
};


const unsigned char myKeyBoard_KeyMap_ATValue[6][16] = 
{
	0x29,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
	0x35,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2D,0x2E,0x2A,0x49,0x4A,
	0x2B,0x14,0x1A,0x08,0x15,0x17,0x1C,0x18,0x0C,0x12,0x13,0x2F,0x30,0x31,0x4C,0x4D,
	0x39,0x04,0x16,0x07,0x09,0x0A,0x0B,0x0D,0x0E,0x0F,0x33,0x34,0x28,0x00,0x00,0x4B,
	xxCK,0x1D,0x1B,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,xxCK,0x52,0x00,0x00,0x4E,
	xxCK,xxCK,xxCK,0x2C,xxCK,xxSK,xxSK,xxCK,0x50,0x51,0x4F,0x00,0x00,0x00,0x00,0x00,
};


//const unsigned char myKeyBoard_KeyMap_ATValue[6][16] = 
//{
//	0x29,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
//	0x35,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2D,0x2E,0x2A,0x49,0x4A,
//	0x2B,0x14,0x1A,0x08,0x15,0x17,0x1C,0x18,0x0C,0x12,0x13,0x2F,0x30,0x31,0x4C,0x4D,
//	0x39,0x04,0x16,0x07,0x09,0x0A,0x0B,0x0D,0x0E,0x0F,0x33,0x34,0x28,0x00,0x00,0x4B,
//	0xE1,0x1D,0x1B,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,0xE5,0x52,0x00,0x00,0x4E,
//	0xE0,0xE3,0xE2,0x2C,0xE6,0x00,0x76,0xE4,0x50,0x51,0x4F,0x00,0x00,0x00,0x00,0x00,
//};


const uint16_t key_Col_Pin[16] = 
{
	myKeyBoard_col0_GPIOPin,
	myKeyBoard_col1_GPIOPin,
	myKeyBoard_col2_GPIOPin,	
	myKeyBoard_col3_GPIOPin,	
	myKeyBoard_col4_GPIOPin,	
	myKeyBoard_col5_GPIOPin,	
	myKeyBoard_col6_GPIOPin,	
	myKeyBoard_col7_GPIOPin,	
	myKeyBoard_col8_GPIOPin,	
	myKeyBoard_col9_GPIOPin,	
	myKeyBoard_col10_GPIOPin,	
	myKeyBoard_col11_GPIOPin,	
	myKeyBoard_col12_GPIOPin,	
	myKeyBoard_col13_GPIOPin,	
	myKeyBoard_col14_GPIOPin,	
	myKeyBoard_col15_GPIOPin	
		
};

typedef struct 
{
	unsigned char ATKeyData;
	unsigned char rowN;
	unsigned char colN;
}ATKeyDataStructureTypedef;

//普通按键暂存数组
ATKeyDataStructureTypedef ATKeyData[6];
unsigned char ATKeyControlByte5 = 0x00;//状态控制键字节 如Shift Ctrl键等
//6行x16列键盘 状态数组
KeyState_enumTypedef myKeyBoard_KeyState[6][16] = {KEYUNPRESSED};//当前按键状态
KeyState_enumTypedef myKeyBoard_KeyState_Ex[6][16] = {KEYUNPRESSED};//上次按键状态



unsigned char myKeyBoard_KeyStateChangedFlag = 0;//键盘状态改变标志
unsigned char myKeyBoard_KeyIsControl = 1;//键盘控制按键标志
unsigned char g_myKeyBoard_DataWaitForUploadFlag = 0;//数据等待上传标志


void myKeyBoard_ControlKeyProcess(u8 rowi, u8 colj);
void myKeyBoard_KeyScan_rowScan(GPIO_TypeDef * 		col_GPIOPort, 
								uint8_t 			col_GPIOPin_Index,
								const uint16_t *	p_col_GPIOPin);





//键盘更新
void myKeyBoard_ScanKeyAndUpdataATBuffer()
{
	myKeyBoard_KeyScan();//物理层键盘状态扫描，按键是否被按下 ， 
	myKeyBoard_JudgeKeyStateChange();//判断键盘状态是否有变化，有则置位myKeyBoard_KeyStateChangedFlag标志
	
	if(myKeyBoard_KeyStateChangedFlag)//判断是否有变化
	{
		myKeyBoard_KeyStateChangedFlag = 0;
		myKeyBoard_UpdataATDataPack();//键盘AT数据包更新
		g_myKeyBoard_DataWaitForUploadFlag = 1;//置位数据等待上传标志
	}
}

void myKeyBoard_UpdataATDataPack()
{
	u8 i,j,k;
	u8 AlreadeyExistflag = 0;
	ATKeyControlByte5 = 0x00;//清楚控制按键键值
	
	if(myKeyBoard_KeyState[5][5] == KEYPRESSED)//判断FN键是否被按下
	{
		
			
	}
	
	if(myKeyBoard_KeyState[5][6] == KEYPRESSED)//判断Menu键是否被按下
	{
		if(myKeyBoard_JudgeKeyPressWithName("PauseBreak"))
		{
			if(!g_USBModeFlag)
				USB_Mode();
			else 
				BLUETEETH_Mode();
			
//			LED_LOGO_FLASH_3TIMES();
		}
		
		else if(myKeyBoard_JudgeKeyPressWithName("Delete"))
		{
			BTK05_DeleteConnectInfo();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Insert"))
		{
			BTK05_PairMode();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Home"))
		{
			BTK05_RESET();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("End"))
		{
			BTK05_Sleep();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F12"))
		{
			LED_SetFlash();//闪烁开关
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F11"))
		{
			LED_SetBreathEfect();//呼吸灯开关	
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F4"))
		{
			//按谁亮谁模式
			//波浪模式
		
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F3"))
		{
			LED_Mode3();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F2"))
		{
			LED_Mode2();//亮WASD 上下左右
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F1"))
		{
			LED_Mode1();//全亮
		}

		else if(myKeyBoard_JudgeKeyPressWithName("+"))
		{
			LED_Brightness++;
			LED_SetBrightness(LED_Brightness);
			if(LED_Brightness > 16) LED_Brightness = 16;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("-"))
		{
			if(LED_Brightness > 0)
				LED_Brightness--;
			LED_SetBrightness(LED_Brightness);
			
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Esc"))
		{
			
			LED_ESCOFF();
			
		}
//		if(myKeyBoard_JudgeKeyPressWithName("ScrollLock"))
//		{
//			if(LED_LOGOENBreath_Flag)
//			{
//				LED_LOGOENBreath_Flag = 0;
//				TIM_Cmd(TIM3,DISABLE);
//			}
//			else
//			{
//				LED_LOGOENBreath_Flag = 1;
//				TIM_Cmd(TIM3,ENABLE);
//			}
//		}
	}
		
	for(i = 0; i < 6 ; i++)//判断上次按下的按键现在是否还被按下,若否则将ATKeyData的数据清零
	{
		if(ATKeyData[i].ATKeyData != 0x00)
		{
			if(myKeyBoard_KeyState[ATKeyData[i].rowN][ATKeyData[i].colN] == KEYUNPRESSED)
			{
				ATKeyData[i].ATKeyData = 0x00;
			}
		}
	}
	
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(myKeyBoard_KeyState[i][j] == KEYPRESSED)//如果按键被按下则处理键盘数据包
			{
				myKeyBoard_ControlKeyProcess(i,j);//控制按键处理
				if(myKeyBoard_KeyIsControl == 0)
				{
					for(k = 0; k < 6; k++)//判断ATKeyData数据包里是否已经有该键的值了，即是否之前已经被按下了
					{
						if(ATKeyData[k].ATKeyData == myKeyBoard_KeyMap_ATValue[i][j])
						{
							AlreadeyExistflag = 1;
							break;
						}
					}
					if(AlreadeyExistflag == 0)//如果ATKeyData数据包没有该键值则放入
					{
						//循环	只要ATKeyData数据包有空位则插入该键值，并且break。
						//如果六次循环完毕也没插就无效，因为一次只能按下六个按键
						for(k = 0; k < 6; k++)
						{
							if(ATKeyData[k].ATKeyData == 0x00)//将按键AT值放入ATKeyData  Buffer
							{
								ATKeyData[k].ATKeyData = myKeyBoard_KeyMap_ATValue[i][j];
								ATKeyData[k].rowN = i;
								ATKeyData[k].colN = j;
								break;
							}
						}
					}
					else {
						AlreadeyExistflag = 0;}
					myKeyBoard_KeyIsControl = 1;
				}
			}
			
		}
	}
	
	//按键键值判断完毕后，将键盘数据包更新
	BTK05_ATKeyDataPack[4] = ATKeyControlByte5;	//更新控制按键字节
	for(k = 0; k < 6; k++)
	{
		BTK05_ATKeyDataPack[6 + k] = ATKeyData[k].ATKeyData;//更新普通按键
	}
}


void myKeyBoard_ControlKeyProcess(u8 rowi, u8 colj)
{
	if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LShift") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 1);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RShift") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 5);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LCtrl") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 0);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RCtrl") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 4);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LAlt") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 2);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RAlt") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 6);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"Win") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 3);
	}
	else//如果以上都没有判别，则是普通按键，复位控制按键标志
	{
		myKeyBoard_KeyIsControl = 0;
	}
}


void myKeyBoard_JudgeKeyStateChange()
{
	u8 i,j;
	//检查键盘状态是否改变
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(myKeyBoard_KeyState_Ex[i][j] != myKeyBoard_KeyState[i][j])
			{
				myKeyBoard_KeyStateChangedFlag = 1;
				break;
			}
			
		}
		if(myKeyBoard_KeyStateChangedFlag)
			break;
	}
	
	//将当前的键盘状态传递给上次
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			myKeyBoard_KeyState_Ex[i][j] = myKeyBoard_KeyState[i][j];//将当前的键盘状态传递给上次
		}
	}
	
}


void myKeyBoard_KeyScan()
{
	u8 i;
	for(i = 0 ; i < 4 ;i ++)
	{
		myKeyBoard_KeyScan_rowScan(myKeyBoard_col3_0_GPIOPort, i, key_Col_Pin);
		//DelayUs(6);
	}
	for(i = 4 ; i < 16 ;i ++)
	{
		myKeyBoard_KeyScan_rowScan(myKeyBoard_col15_4_GPIOPort, i, key_Col_Pin);
		//DelayUs(6);
	}
}


void myKeyBoard_KeyScan_rowScan(GPIO_TypeDef * 		col_GPIOPort, 
								uint8_t 			col_GPIOPin_Index,
								const uint16_t *	p_col_GPIOPin)
{
	GPIO_SetBits(col_GPIOPort, *(p_col_GPIOPin + col_GPIOPin_Index));
	DelayUs(2);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row0_GPIOPin)) 
		{myKeyBoard_KeyState[0][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[0][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(50);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row1_GPIOPin)) 
		{myKeyBoard_KeyState[1][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[1][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row2_GPIOPin)) 
		{myKeyBoard_KeyState[2][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[2][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row3_GPIOPin)) 
		{myKeyBoard_KeyState[3][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[3][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row4_GPIOPin)) 
		{myKeyBoard_KeyState[4][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[4][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);	
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row5_GPIOPin)) 
		{myKeyBoard_KeyState[5][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[5][col_GPIOPin_Index] = KEYUNPRESSED;}
	
	GPIO_ResetBits(col_GPIOPort, *(p_col_GPIOPin + col_GPIOPin_Index));
	//DelayUs(10);
}

unsigned char myKeyBoard_JudgeKeyPressWithName(const char* keyName)
{
	
	unsigned char i,j;
	for(i = 0; i < 6; i++ )
	{
		for(j = 0; j < 16; j++)
		{
			if(strcmp(myKeyBoard_KeyMap_Name[i][j], keyName) == 0)
			{
				if(myKeyBoard_KeyState[i][j] == KEYUNPRESSED)
				{
					return 0;
				}
				else
				{
					myKeyBoard_KeyState[i][j] = KEYUNPRESSED;
					return 1;
				}
			}
				
		}
		
	}
	
	return 0;
}

//初始化键盘IO
void myKeyBoard_GPIO_Init()
{
	
	GPIO_InitTypeDef GPIOType;
	
	//初始化 row0-row5 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_row0_GPIOPin | 
						myKeyBoard_row1_GPIOPin | 
						myKeyBoard_row2_GPIOPin | 
						myKeyBoard_row3_GPIOPin | 
						myKeyBoard_row4_GPIOPin |
						myKeyBoard_row5_GPIOPin;
	
	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
	GPIO_Init(myKeyBoard_row_GPIOPort , &GPIOType);
	
	//初始化 col0-col3 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_col0_GPIOPin | 
						myKeyBoard_col1_GPIOPin | 
						myKeyBoard_col2_GPIOPin | 
						myKeyBoard_col3_GPIOPin ;

	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_Init(myKeyBoard_col3_0_GPIOPort , &GPIOType);
	
	//初始化 col4-col15 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_col4_GPIOPin | 
						myKeyBoard_col5_GPIOPin | 
						myKeyBoard_col6_GPIOPin | 
						myKeyBoard_col7_GPIOPin |
						myKeyBoard_col8_GPIOPin |
						myKeyBoard_col9_GPIOPin |
						myKeyBoard_col10_GPIOPin |
						myKeyBoard_col11_GPIOPin |
						myKeyBoard_col12_GPIOPin |
						myKeyBoard_col13_GPIOPin |
						myKeyBoard_col14_GPIOPin |
						myKeyBoard_col15_GPIOPin ;
						
	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_Init(myKeyBoard_col15_4_GPIOPort , &GPIOType);

}




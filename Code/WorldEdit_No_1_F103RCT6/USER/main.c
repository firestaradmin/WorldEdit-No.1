

#include "main.h"

void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_CH3_PWM_init(u16 arr,u16 psc);
void myUSB_Init(void);
void sysInit(void);
static unsigned short sleepTime1SCounter = 0;
unsigned char sleepTime50MsCounter = 0;
unsigned char LED_breath_Flag = 0;
unsigned char LED_LOGOBreath_Flag = 0;
unsigned char LED_LOGOENBreath_Flag = 0;
unsigned char system_Status = 1;  //1:运行中，0：休眠中
unsigned char g_Flag = 0;
uint8_t ledLogoPWM = 80;
int8_t ledLogoPWMDelt = 0;
bool g_USBModeFlag = FALSE;


int main()
{
	//sysInit();
	BTK05_Wake();//唤醒BTK05
	

	while(1)
	{ 
		if(g_USBModeFlag)//USB模式下
		{
			if(sleepTime1SCounter <= 1000)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//键盘事件更新
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					sleepTime1SCounter = 0;
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(bDeviceState == CONFIGURED)//如果连接上了 USB
						Keyboard_Send(BTK05_ATKeyDataPack+4);
					//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					
				}
			}
			else if(system_Status == 0)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//键盘事件更新
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(bDeviceState == CONFIGURED)//如果连接上了 USB
						Keyboard_Send(BTK05_ATKeyDataPack+4);
					//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					system_Status = 1;
					TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
					sleepTime1SCounter = 0;
					if(LED_Status)	
						LED_WakeUp();	
				}
			}
			else if(sleepTime1SCounter > 1000)
			{
				TIM_Cmd(TIM2, DISABLE);  //失能TIMx		
				system_Status = 0;
				LED_GoToSleep();
			}
		}
		else//蓝牙模块模式
		{
			//如果键盘休眠计时器小于400并且键盘处于醒着的状态
			if(sleepTime1SCounter <= 400 && BTK05_Status == BTK_WAKE)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//键盘事件更新
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					//GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					BTK05_UART_SendKeyData(BTK05_ATKeyDataPack,12);
					sleepTime1SCounter = 0;

					if(ATKeyControlByte5 != 0) 
					{
						GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					}
					else
					{
						GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					}
				}
			}
			//如果蓝牙处于休眠状态
			else if(BTK05_Status == BTK_SLEEP)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					system_Status = 1;
					BTK05_Wake();//唤醒BTK05
					TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
					sleepTime1SCounter = 0;
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(LED_Status)	
						LED_WakeUp();
					BTK05_UART_SendKeyData(BTK05_ATKeyDataPack,12);
				}
			}
			//如果 键盘休眠计时器大于600   即600S没有按下任何按键则然键盘进入休眠状态
			else if(sleepTime1SCounter > 400)   
			{
				//进入休眠模式...
				BTK05_Sleep();//休眠BTK05
				TIM_Cmd(TIM2, DISABLE);  //失能TIMx		
				system_Status = 0;
				LED_ESCOFF();	 
			}
		}
		
		if(LED_BreathEfectFlag && LED_breath_Flag)
		{
			LED_BreathProcess();
			LED_breath_Flag = 0;
		}
//		if(LED_LOGOBreath_Flag  && LED_LOGOENBreath_Flag)//logo呼吸灯处理标志
//		{
//			TIM_SetCompare3(TIM3, ledLogoPWM);
//			if(ledLogoPWMDelt == 0)
//			{
//				ledLogoPWM --;
//				if(ledLogoPWM <= 30)
//					ledLogoPWMDelt = 1;
//			}
//			else
//			{
//				ledLogoPWM ++;
//				if(ledLogoPWM == 98)
//					ledLogoPWMDelt = 0;
//			}
//			LED_LOGOBreath_Flag = 0;

//		}
			
	}

}


////定时器中断服务程序
void TIM2_IRQHandler(void)   //TIM中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
				
			sleepTime50MsCounter++;
			LED_LOGOBreath_Flag = 1;
			//LED_breath_Timer50ms++;
			if(sleepTime50MsCounter == 20)	
			{
				
				sleepTime50MsCounter = 0;                   
				sleepTime1SCounter++;
				
			}
			if(sleepTime50MsCounter % 4 == 0)
					LED_breath_Flag = 1;
			
			
		}
}


void sysInit()
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	DelayInit();
	
	
	myKeyBoard_GPIO_Init();
	
	
	BTK05_Init();
	
	
	LED_LOGO_GPIO_Init();
	LED_I2C_Configuration();
	LED_HT16K33_Init();//初始化芯片
	
	
	
	//TIM3_CH3_PWM_init(100,0);
	TIM2_Int_Init(1000,3600);//50ms一次中断
	myUSB_Init();
}



//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//一次中断的时间为t：t = (arr * psc / APB1*2) * 1000 ms
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM中断,允许更新中断
 
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}


void USB_Mode(void)
{

	g_USBModeFlag = TRUE;	
	
	//BTK05进入休眠模式...
	BTK05_Sleep();//休眠BTK05
	sleepTime1SCounter = 0;
	TIM_Cmd(TIM2, ENABLE);  		
	//system_Status = 1;
	//LED_GoToSleep();
	//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
}

void BLUETEETH_Mode(void)
{
 
	g_USBModeFlag = FALSE;	
	
	BTK05_Wake();//唤醒BTK05
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx	
	sleepTime1SCounter = 0;
	//GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
}


void myUSB_Init(void)
{
	USB_Port_Set(1);	//开启USB连接
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	 
}


void TIM3_CH3_PWM_init(u16 arr,u16 psc)
{
    //配置TIM3
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//注意结构体的声明必须在函数的开头
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=arr;
    TIM_TimeBaseStructure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    //配置TIM3 Channel3 PWM

    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OC3Init(TIM3,&TIM_OCInitStructure);//注意此处的函数名字以及函数的入口参数

    //配置GPIO口，并且设置成复用功能

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
    //把TIM3部分重映射到PB5
    //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

    //使能TIM3时钟
    TIM_Cmd(TIM3,DISABLE);
}

//void LED_LOGO_FLASH_3TIMES()
//{
//	
////------------------------------------------------------
//	

//}



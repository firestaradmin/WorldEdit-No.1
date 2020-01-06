#include "myPWR.h"

void EXTI_Init(void)
{
	
}

void RCC_Configuration(void)
{
	sysInit();
}

void myPWR_EnterStopMode(void)
{
	RCC_APB2PeriphResetCmd(0X01FC, DISABLE);//复位所有外设
	
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);//低功耗，等待外部中断
	RCC_Configuration();  // 唤醒后重新进行时钟配置
	
	
}

void myPWR_PWR_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//使能PWR外设时钟
	
}













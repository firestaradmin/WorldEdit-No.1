#ifndef __MAIN_H_
#define __MAIN_H_

#include <stm32f10x.h> 
#include "stm32f10x_it.h"
#include "LED.h"
#include "delay.h"
#include "myKeyBoard.h"
#include "BTK05.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"

//typedef enum
//{
//  FALSE = 0, TRUE  = !FALSE
//}
//bool;

#define true 1
#define false 0
	
extern unsigned char g_Flag;
extern bool g_USBModeFlag;
extern unsigned char LED_LOGOENBreath_Flag ;





//void LED_LOGO_FLASH_3TIMES(void);
void BLUETEETH_Mode(void);
void USB_Mode(void);





#endif




#ifndef __MYKEYBOARD_H_
#define __MYKEYBOARD_H_
//#include "main.h"



typedef enum 
{
	KEYUNPRESSED= 0,
	KEYPRESSED  = ~KEYUNPRESSED
}KeyState_enumTypedef;

//extern KeyState_enumTypedef myKeyBoard_KeyState[6][16];
extern unsigned char g_myKeyBoard_DataWaitForUploadFlag;//数据等待上传标志
extern unsigned char ATKeyControlByte5 ;//状态控制键字节 如Shift Ctrl键等


void myKeyBoard_GPIO_Init(void);//按键IO初始化
void myKeyBoard_KeyScan(void);//物理层键盘状态扫描，按键是否被按下 

void myKeyBoard_JudgeKeyStateChange(void);//判断键盘状态是否有变化，有则置位myKeyBoard_KeyStateChangedFlag标志
void myKeyBoard_UpdataATDataPack(void);//键盘AT数据包更新
void myKeyBoard_ScanKeyAndUpdataATBuffer(void);//键盘扫描并更新Key数据包
unsigned char myKeyBoard_JudgeKeyPressWithName(const char* keyName);
void myKeyBoard_Process_All(void);//键盘中心程序
#endif



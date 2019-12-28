#include "myUSART.h"



#define USART1_REC_LEN 256

u16 tnum = 0;
u8 Uart1_RevBuf_Tail = 0;//接收缓冲区尾部
u8 Uart1_RevBuf[USART1_REC_LEN];//接收缓冲区数组

void UART1_init()
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
  USART_DeInit(USART1);
 

  //USART1端口配置
  //UASART_TX   PA9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
  //USART1_RX      PA10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

  //USART1 初始化设置
  USART_InitStructure.USART_BaudRate = 115200;//波特率设置
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式     
  USART_Init(USART1, &USART_InitStructure); //初始化串口1

    //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;        //子优先级3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);    //根据指定的参数初始化VIC寄存器
    
  USART_Init(USART1, &USART_InitStructure);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
  USART_Cmd(USART1, ENABLE);  //使能串口1

}

//串口1中断服务程序
void USART1_IRQHandler(void)                    
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
    {    
        
        Uart1_RevBuf[Uart1_RevBuf_Tail] = USART_ReceiveData(USART1);//读取接收到的数据，将尾标后移
        //USART_SendData(USART1,Uart1_RevBuf[Uart1_RevBuf_Tail]);//发送接收到的数据
        //while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        //{}
        Uart1_RevBuf_Tail++;
        if(Uart1_RevBuf_Tail>USART1_REC_LEN-1)
        {
            Uart1_RevBuf_Tail = 0;    
        }
		
		
		tnum++;
    } 
}








#include "usart.h"	
#include "delay.h"



int fputc(int ch, FILE *f)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
int fgetc(FILE *f)
{
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		return (int)USART_ReceiveData(USART1);
}

u8 USART_RX_BUF[USART_REC_LEN];  
u8 USART_TX_BUF[USART_SED_LEN];	 
u16 USART_RX_STA=0;      	  
  
void uart_init(u32 bound)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}


//void USART1_IRQHandler(void) 
//{
//	u8 data;

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
//	{
//		data = USART_ReceiveData(USART1);	
//		
//		switch(data)
//		{
//			
//		}
//		USART_SendData(USART1,data);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
//	}
//	USART_ClearFlag(USART1,USART_FLAG_TC);
//}


int OpenMV_Rx_BUF[1];//openmv传递角度变量，还有黑洞的变量
u8 point;

void USART1_IRQHandler(void)			   
{
	static u8 rebuf[6]={0};
	static uint16_t i=0;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		rebuf[i++]=USART_ReceiveData(USART1);	
		if(rebuf[0]!=0xb3)//帧头
			i=0;
	  if((i==2)&&(rebuf[1]!=0xb3))//判断帧头
			i=0;
		if(i>=3)//代表一帧数据结束
		{
			OpenMV_Rx_BUF[0] = rebuf[2];
			OpenMV_Rx_BUF[1] = rebuf[3];
//			if(OpenMV_Rx_BUF[0]>128)
//			{
//				OpenMV_Rx_BUF[0] -= 256;
//			}
//			else
//				OpenMV_Rx_BUF[0] = OpenMV_Rx_BUF[0];
//			OpenMV_Rx_BUF[1] = rebuf[3];
//			OpenMV_Rx_BUF[2] = rebuf[4];
//			OpenMV_Rx_BUF[3] = rebuf[5];
			i = 0;
		}
		USART_ClearFlag(USART1,USART_FLAG_RXNE);
	}
}


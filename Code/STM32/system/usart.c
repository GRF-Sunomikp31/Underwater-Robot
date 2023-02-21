
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
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
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


int OpenMV_Rx_BUF[1];//openmv���ݽǶȱ��������кڶ��ı���
u8 point;

void USART1_IRQHandler(void)			   
{
	static u8 rebuf[6]={0};
	static uint16_t i=0;
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		rebuf[i++]=USART_ReceiveData(USART1);	
		if(rebuf[0]!=0xb3)//֡ͷ
			i=0;
	  if((i==2)&&(rebuf[1]!=0xb3))//�ж�֡ͷ
			i=0;
		if(i>=3)//����һ֡���ݽ���
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


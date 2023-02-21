#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"

	   		   
//IO��������
//#define MPU_SDA_IN()   {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
//#define MPU_SDA_OUT()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}

#define MPU_SDA_IN()   {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=(u32)8<<16;}
#define MPU_SDA_OUT()  {GPIOA->CRH&=0XFFF0FFFF;GPIOA->CRH|=(u32)3<<16;}

//#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}

//IO��������	 
//#define MPU_IIC_SCL     PBout(4) //SCL
//#define MPU_IIC_SDA     PBout(3) //SDA	
//#define MPU_READ_SDA   	PBin(3) //SDA	

#define MPU_IIC_SCL     PAout(11) //SCL
#define MPU_IIC_SDA     PAout(12) //SDA	
#define MPU_READ_SDA   	PAin(12) //SDA	

//#define IIC_SCL    PBout(8) //SCL
//#define IIC_SDA    PBout(9) //SDA	 
//#define READ_SDA   PBin(9)  //����SDA 



//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif

















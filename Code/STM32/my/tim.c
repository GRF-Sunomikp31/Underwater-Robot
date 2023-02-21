

#include "tim.h"
#include "pio.h"
#include "pid.h"
#include "servo.h"
#include "io.h"



PositionPID_t Depth_pid = 
{
	0,0,0,
	0,0,0,
	0
};
PositionPID_t Angle = //����PΪ25�ı仯���ȱȽϺ�������ӽ���ֵʱ�������������ƽ���ˮ�к����������о��ᱻ�Ŵ�
{
	25,0,0,
	0,0,0,
	0
};
PositionPID_t Turn = //�����p�о�������Ϊ10�ȽϺ���
{
	0,0,0,
	0,0,0,
	0
};

void TIM1_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; 
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
 
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1,ENABLE); 					 
}
float data;//�������
int speed,target;
u8 s1,s2,flag = 0;
u8 flagsb = 0;
void TIM1_UP_IRQHandler(void)
{
	static u32 time = 0;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET) 
	{
		time++;
		if(time % 2 == 0)
		{
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	
			s1 = read_s1;
			s2 = read_s2;
		}
		if(time % 10 == 0)
		{//ֱ������
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 1&&flag == 0)//�ߵ�ƽ�͵�ƽ�Ҳ���ȷ��
//			{
//				speed = Position_PID(&Angle,1500,Pitch);//�������Ҳ����ȷ�ϣ�Ŀ��ֵҪ�������ŵ�ʱ���Ŀ��ֵ
//				move_FB(speed);		
//			}//��һ��ת��
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 0)
//			{
//				flag = 1;
//				speed = Position_PID(&Angle,90,Pitch);//����Ƕ�ҲҪ����ʵ��ֵ������
//				move_Turn(speed);
//			}//Ŀ��ֵ90������
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 1&&flag == 1)
//			{
//				flag = 2;
//				speed = Position_PID(&Angle,1500,Pitch);//�������Ҳ����ȷ�ϣ�Ŀ��ֵҪ�������ŵ�ʱ���Ŀ��ֵ
//				move_FB(speed);	
//			}//�ڶ���ת��
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 2)
//			{
//				speed = Position_PID(&Angle,180,Pitch);//����Ƕ�ҲҪ����ʵ��ֵ������
//				move_Turn(speed);
//			}//Ŀ��ֵ180������
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 2)
//			
//				flag = 3;
				flagsb = 10*OpenMV_Rx_BUF[0]+OpenMV_Rx_BUF[1];
				speed = Position_PID(&Angle,flagsb,Pitch);//�������Ҳ����ȷ�ϣ�Ŀ��ֵҪ�������ŵ�ʱ���Ŀ��ֵ
				move_FB(speed);	
		
		}
		if(time >= 1000)
		{
			time = 0;
			led1toggle;
		}
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  
	}		
}


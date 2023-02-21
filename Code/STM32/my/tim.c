

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
PositionPID_t Angle = //测试P为25的变化幅度比较合理，电机接近中值时候有死区，估计进入水中后这种死区感觉会被放大
{
	25,0,0,
	0,0,0,
	0
};
PositionPID_t Turn = //这个的p感觉就设置为10比较合适
{
	0,0,0,
	0,0,0,
	0
};

void TIM1_Int_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); //时钟使能

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
float data;//深度数据
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
		{//直线行走
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 1&&flag == 0)//高电平低电平我不能确认
//			{
//				speed = Position_PID(&Angle,1500,Pitch);//这个轴我也不能确认，目标值要按照正放的时候的目标值
//				move_FB(speed);		
//			}//第一次转向
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 0)
//			{
//				flag = 1;
//				speed = Position_PID(&Angle,90,Pitch);//这个角度也要根据实际值来测试
//				move_Turn(speed);
//			}//目标值90度行走
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 1&&flag == 1)
//			{
//				flag = 2;
//				speed = Position_PID(&Angle,1500,Pitch);//这个轴我也不能确认，目标值要按照正放的时候的目标值
//				move_FB(speed);	
//			}//第二次转向
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 2)
//			{
//				speed = Position_PID(&Angle,180,Pitch);//这个角度也要根据实际值来测试
//				move_Turn(speed);
//			}//目标值180度行走
//			if(OpenMV_Rx_BUF[0] == 1&&s2 == 0&&flag == 2)
//			
//				flag = 3;
				flagsb = 10*OpenMV_Rx_BUF[0]+OpenMV_Rx_BUF[1];
				speed = Position_PID(&Angle,flagsb,Pitch);//这个轴我也不能确认，目标值要按照正放的时候的目标值
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


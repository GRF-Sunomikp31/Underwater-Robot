
#include "sys.h"  
#include "pio.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "tim.h"
#include "servo.h"
#include "io.h"


/*******************
电机布局：
	1->后左
	2->前右
	3->前左
	4->中右
	5->中左
	6->后右
	俯仰角在Pitch轴
********************/

int val1[6]={1500,1500,1500,1500,1500,1500};

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度


int main(void)
{
 	key_exti_init();
	delay_init();
	uart_init(115200);
	
	MPU_Init();
	mpu_dmp_init();
	
	Pio_init();

	PWM_Init_TIM2(); //电调电机初始化
	PWM_Init_TIM3();	
	moto_init();
	
	TIM1_Int_Init();
	 
	while(1)
	{ 		
//		TIM_SetCompare1(TIM2,val1[0]);
//		TIM_SetCompare2(TIM2,val1[1]);
//		TIM_SetCompare3(TIM2,val1[2]);
		TIM_SetCompare4(TIM2,1800);
		TIM_SetCompare3(TIM3,1800);

//		TIM_SetCompare4(TIM3,val1[5]);
	}	
}


#ifndef _SERVO_H
#define _SERVO_H


#include "sys.h"




void PWM_Init_TIM2(void);
void PWM_Init_TIM3(void);

void moto_init(void);

void move_Turn(int speed);
void move_FB(int speed);
void move_Dive(int speed);

void move_demo(int speed);
void move_M1(int speed);
void move_M2(int speed);


#endif


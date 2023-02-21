

#ifndef _PID_H
#define _PID_H


#include "sys.h"


typedef struct
{
	float Kp, Ki, Kd;
	float P, I, D;
	float Error_Last;	
}PositionPID_t;






int Position_PID( PositionPID_t *pid, float set_value, float now_value);

#endif




#include "pid.h"




int Position_PID( PositionPID_t *pid, float set_value, float now_value)
{
	pid->P = set_value - now_value;
	pid->I += pid->P;
	pid->D = pid->P - pid->Error_Last;
	pid->Error_Last = pid->P;
	pid->I=pid->I>10000?10000:(pid->I<(-10000)?(-10000):pid->I);
	if( set_value == 0 )			pid->I = 0;
	
	return( pid->Kp*pid->P  +  pid->Ki*pid->I  +  pid->Kd*pid->D );
}




#ifndef _IO_H
#define _IO_H



#include "sys.h"


void io_init(void);


#define read_s1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
#define read_s2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);



#endif


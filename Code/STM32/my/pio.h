

#ifndef _PIO_H
#define _PIO_H

#include "sys.h"

#define led1 PCout(13)
#define led1toggle  GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13))));




void Pio_init(void);


#endif


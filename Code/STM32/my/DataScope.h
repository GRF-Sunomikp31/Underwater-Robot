


#ifndef _DATASCOPE_H
#define _DATASCOPE_H




#include "sys.h"



void Float2Byte(float *target,unsigned char *buf,unsigned char beg);
void DataScope_Get_Channel_Data(float Data,unsigned char Channel);
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);
void DataScope(void);


#endif



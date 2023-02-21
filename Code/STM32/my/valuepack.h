

#ifndef _VALUEPACK_H
#define _VALUEPACK_H

#include "sys.h"



// ������ͨ��DMA��USART �������ݰ��Ľ��պͷ���
// ���յ������Զ�д�뵽buffer�У�ͨ����ʱ����readValuePack()��������������ʱ���������10ms���ڡ�
// ���ݷ���Ҳ����DMA

// 1.ָ�����ջ������Ĵ�С --------------------------------------------------------------------------------
// һ����Ҫ512�ֽ����ϣ���Ҫ����ʵ�ʽ������ݵ��ٶȺ�proc������Ƶ�ʿ��ǡ�
#define VALUEPACK_BUFFER_SIZE 1024

// 2.ָ�����͵��ֻ������ݰ��Ľṹ----------�ڷ���ʱ���Զ�������ǰ����ϰ�ͷ����β��У������ݣ���˻���3���ֽ�
// ����ʵ����Ҫ�ı������������ݰ��� bool byte short int float �������͵���Ŀ

#define TX_BOOL_NUM 0
#define TX_BYTE_NUM 0
#define TX_SHORT_NUM 0
#define TX_INT_NUM 0
#define TX_FLOAT_NUM 0

// 3.ָ���������ݰ��Ľṹ-----------------------------------------------------------------------------------
// ����ʵ����Ҫ�ı������������ݰ��� bool byte short int float �������͵���Ŀ

#define RX_BOOL_NUM 0
#define RX_BYTE_NUM 2
#define RX_SHORT_NUM 2
#define RX_INT_NUM 0
#define RX_FLOAT_NUM 0

typedef struct
{
#if TX_BOOL_NUM > 0
	unsigned char bools[TX_BOOL_NUM];
#endif

#if TX_BYTE_NUM > 0
	char bytes[TX_BYTE_NUM];
#endif

#if TX_SHORT_NUM > 0
	short shorts[TX_SHORT_NUM];
#endif

#if TX_INT_NUM > 0
	int integers[TX_INT_NUM];
#endif

#if TX_FLOAT_NUM > 0
	float floats[TX_FLOAT_NUM];
#endif
	char space; // �����壬ֻΪ�˲��ýṹ��Ϊ�գ��ṹ��Ϊ�ջᱨ��
} TxPack;
typedef struct
{
#if RX_BOOL_NUM > 0
	unsigned char bools[RX_BOOL_NUM];
#endif

#if RX_BYTE_NUM > 0
	char bytes[RX_BYTE_NUM];
#endif

#if RX_SHORT_NUM > 0
	short shorts[RX_SHORT_NUM];
#endif

#if RX_INT_NUM > 0
	int integers[RX_INT_NUM];
#endif

#if RX_FLOAT_NUM > 0
	float floats[RX_FLOAT_NUM];
#endif
	char space; // �����壬ֻΪ�˲��ýṹ��Ϊ�գ��ṹ��Ϊ�ջᱨ��
} RxPack;
// ��ʼ�� valuepack ����һЩ��Ҫ��Ӳ����������

void initValuePack(int baudrate);

// ��Ҫ��֤����ÿ��ִ��10�θú���
// �ú�������Ҫ�������Ƚ������յĻ�������������յ�������RX���ݰ��������RX���ݰ��е����ݣ�Ȼ��ʼ���ڷ���TX���ݰ� ��
// ���յ����ݰ�ʱ ���� 1 �����򷵻� 0
unsigned char readValuePack(RxPack *rx_pack_ptr);
// �������ݰ�
void sendValuePack(TxPack *tx_pack_ptr);

#define PACK_HEAD 0xa5
#define PACK_TAIL 0x5a



#endif


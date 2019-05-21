#include "config.h"
#include "wave.h"

uint Distance_Get(void)
{
	uint Distance;
	uchar Count = 0;

//	EA = 0;
	RX = 1;
	TR1 = 1;
	Send_Wave();		
	while (RX && !TF1);
	TR1 = 0;
	if (TF1)
	{
		TF1 = 0;
		Distance = 0;
	}
	else
	{
		Distance = TH1;
		Distance <<= 8;
		Distance |= TL1;
////////////////改动处///////////
// 		Distance = Distance * 0.17;	//单位为mm    
//		0.17 = 0.017*10
//		0.017 = 17/1000 = (2^4+1)/1000 = 2^4/1000 + 0.001 约为 2^4/1000 在精度不高的情况下 约为 2^4/1024 = 2^4/2^10 = 2^-6
////////////故函数可以修改位:
		Distance = (time>>6)*10;  //这样可以提高处理速度

	}
	TH1 = TL1 = 0;
//	EA = 1;
	
	return Distance;	
}
void Init_Timer1(void)
{
	TMOD |= 0x10;
	TH1 = TL1 = 0;
}

void Send_Wave(void)
{
	uchar i;

	for (i = 0; i < 8; i++)
	{
		TX = 1;
		Delay12us();
		TX = 0;
		Delay12us();
	}
}

void Delay12us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}

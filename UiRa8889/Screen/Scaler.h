#ifndef		__SCALER_H
#define		__SCALER_H
#include	"STC15Fxxxx.H"



#define ScalerCount 2
struct ScalerType //�༭��������
{	u16 Addr;
	u8 PageName;
	u16 x;//���
	u16 y;
	u16 width;//��
	u16 length;//��
	u32 Color;
	u32 Bcolor;
	u8 First;
};

extern struct ScalerType Scaler;
	

void ScalerFlush(u8 PageName);
#endif
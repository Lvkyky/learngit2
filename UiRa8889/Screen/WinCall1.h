#ifndef		__WINCALL1_H
#define		__WINCALL1_H
#include "STC15Fxxxx.H"

#define WinScanCallCount  23
struct WinScanCall //�����Ļص�����
{
	u8  Name;//��������	
	void (*FuncScan)(u16 x,u16 y,u8 WinName);
};


extern const struct WinScanCall code WinScanCallGroup[WinScanCallCount];
#endif
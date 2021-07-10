#ifndef		__WINCALL_H
#define		__WINCALL_H
#include "STC15Fxxxx.H"

#define WinOkCallCount  27
#define WinCanCallCount  26


struct WinOkCall //�����Ļص�����
{
	u8  Name;//��������	
	void (*FuncOk)(void);
};

struct WinCanCall //�����Ļص�����
{
	u8  Name;//��������	
	void (*FuncCan)(void);
};



extern const struct WinOkCall code WinOkCallGroup[WinOkCallCount];
extern const struct WinCanCall code WinCanCallGroup[WinCanCallCount];
#endif
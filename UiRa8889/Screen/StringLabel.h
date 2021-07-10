#ifndef __STRIMGLABEL_H
#define __STRINGLABEL_H	 
#include "STC15Fxxxx.H"

#define StringLabelVarCount 9
#define Trans 1
#define Untrans 0

#define CenterAlign 0
#define LeftAlign 1

struct StringInfoType//�ַ�������Ϣ�ṹ
{  
	u8 Align;
	u8 TransFlag;//͸����   1��͸��   0����͸��
	u16 x;
	u16 y;//λ��
	u16 Width;//����
	u16 Length;//�߶�
	u32 Color;//��ɫ
	u32 Bcolor;
};	


struct StringLabelVarType
{
	u16 Addr;//������ַ
	u8 PageName;//��������ҳ��
	struct StringInfoType VarInfo;//����������Ϣ
}; //����



void StringLabelFlush(u8 PageName);
void StringInit();
void StringSingleInit(u8 *mem,u8 *p);
#endif
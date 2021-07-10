#ifndef __NUMLABEL_H
#define __NUMLABEL_H	 
#include "STC15Fxxxx.H"

#define NumLabelVarCount 73


struct FormatType
{
	u8 Left;
	u8 Right;
};


struct UnitType
{
	u8 Pre;  //1��ǰ׺  0����׺
	u8 Count; //����
	u8 *p; //��λ�ַ���ָ��
};



struct NumInfoType//�ַ�������Ϣ�ṹ
{  
	u8 Align;
	u8 TransFlag;//͸����   1��͸��   2����͸��
	u16 x;
	u16 y;//λ��
	u16 Width;//����
	u16 Length;//�߶�
	u32 Color;//��ɫ
	u32 Bcolor;
	struct FormatType Format;//��ʽ
	struct UnitType Unit;//��λ
};	


struct NumLabelVarType
{
	u16 Addr;//������ַ
	u8 PageName;//��������ҳ��
	struct NumInfoType VarInfo;//����������Ϣ
	u8 DataLength;//�������ݳ���
}; //����






void NumLabelFlush(u8 PageName);
#endif
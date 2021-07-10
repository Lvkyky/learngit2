
/*************	����˵��	**************
���ļ�ʵ�����ж������Լ��Դ����¼��Ĵ���
��״̬ת�����ڲ�������
******************************************/
#include "Exti.h"
#include "USART.h"
#include "ads7843.h"
#include "delay.h"
#include "timer.h"

#include "screen.h"
#include "api.h"
#include "All_8889_Pic_NOR.h"
#include  "RA8889.h"
#include  "UserDef.h"
#include  "Button.h"
#include  "Win.h"

/********************* INT0�жϺ��� *************************/
//========================================================================
// ����: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�ж�2������.
// ����: ��ȡ�������꣨��λ�����أ�
// �汾: V1.0, 2021-05-21
//========================================================================
void Ext_INT2 (void) interrupt INT2_VECTOR
{
	ButtonDecreTimer.swit=1;//������ʱ����	
	PrintString1("EXT\r\n");
}



	
//========================================================================
// ����: u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
// ����: �ⲿ�жϳ�ʼ������.
// ����: INTx: �ṹ����,��ο�Exti.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx)
{ PrintString1("��ʼ�жϳ�ʼ��\r\n");  
	if(EXT >  EXT_INT4)
	{
	 PrintString1("�ղ���\r\n");
	 return 1;	//�ղ���
	}		
	
	if(EXT == EXT_INT0)	//���ж�0
	{
		if(INTx->EXTI_Interrupt == ENABLE)		EX0 = 1;	//�����ж�
		else									EX0 = 0;	//��ֹ�ж�
		if(INTx->EXTI_Polity == PolityHigh)		PX0 = 1;	//�����ȼ��ж�
		else									PX0 = 0;	//�����ȼ��ж�
		if(INTx->EXTI_Mode == EXT_MODE_Fall)	IT0 = 1;	//�½����ж�
		else									IT0 = 0;	//����,�½����ж�
	  PrintString1(" �жϳ�ʼ���ɹ�\r\n");      
		return	0;		//�ɹ�
	}
	
	if(EXT == EXT_INT2)		//���ж�2, �̶�Ϊ�½��ص����ȼ��ж�
	{
		if(INTx->EXTI_Interrupt == ENABLE)	INT_CLKO |=  (1 << 4);	//�����ж�	
		else								INT_CLKO &= ~(1 << 4);	//��ֹ�ж�
		return	0;		//�ɹ�
	}

	PrintString1("�жϳ�ʼ��ʧ��\r\n");
	return 2;	//ʧ��
}


void	EXTI_config(void)                          //�ⲿ�ж�2 ��ʼ��
{ 
	EXTI_InitTypeDef	EXTI_InitStructure;					//�ṹ����
	PrintString1("��ʼ�ж�2��ʼ��\r\n");
	EXTI_InitStructure.EXTI_Mode      = EXT_MODE_Fall;	//�ж�ģʽ,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	EXTI_InitStructure.EXTI_Polity    = PolityLow;			//�ж����ȼ�,   PolityLow,PolityHigh
	EXTI_InitStructure.EXTI_Interrupt = ENABLE;				//�ж�����,     ENABLE��DISABLE
	Ext_Inilize(EXT_INT2,&EXTI_InitStructure);				//��ʼ��INT0	EXT_INT0,EXT_INT1,EXT_INT2,EXT_INT3,EXT_INT4
}














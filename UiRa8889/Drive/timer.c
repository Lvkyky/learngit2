
/*************	����˵��	**************
���ļ�ʵ���˶Զ�ʱ���ĳ�ʼ�������ã�
�ڴ˻�����ʵ�������ڷ���PAGE_ID��
���һ�ʵ��������֡��ʱ�ж���
******************************************/
#include "timer.h"
#include "USART.h"
#include "screen.h"
#include "delay.h"
#include "api.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include "RA8889.h"
#include "ads7843.h"

struct Timer  PageTimer;  //���ڷ���page_id����
struct Timer  InfoWinTimer;
struct Timer  tempFluTimer;
struct Timer  CursorFluTimer;
struct Timer  ButtonReleaTimer;
struct Timer  ButtonDecreTimer;
struct Timer  AnimitationTimer;

u32 CurentInfoWinTime=0X00FF;//��ǰ��Ϣ������ʱ��
//======================================================================
// ����: u8	timer0_int()
// ����: ��ʱ��0�жϺ���
// ����: ��
// ����: ��
// �汾: V1.0, 2021-05-26
//======================================================================
void timer0_int (void) interrupt TIMER0_VECTOR   //1s<---->200  
{
	
	PageTimer.count=(PageTimer.count+1)%1000;
	if(PageTimer.count==250)  PageTimer.update=1;//���ڷ���Page_ID��500ms��
		
	if(InfoWinTimer.swit==1)	
	{
		InfoWinTimer.count=(InfoWinTimer.count+1)%(65530);//��Ϣ������ʱ(500ms)
		if(InfoWinTimer.count==CurentInfoWinTime) InfoWinTimer.update=1;
	}
		
	tempFluTimer.count=(tempFluTimer.count+1)%1000;//��Ļˢ��(500ms)
	if(tempFluTimer.count==80) tempFluTimer.update=1;
		
	if(CursorFluTimer.swit==1) 
	{
		CursorFluTimer.count=(CursorFluTimer.count+1)%1000;//�����˸��500ms��
		if(CursorFluTimer.count==250) CursorFluTimer.update=1;
	}
	
	if(ButtonReleaTimer.swit==1)
	{
		ButtonReleaTimer.count=(ButtonReleaTimer.count+1)%1000;//�����ͷż���ʱ����50ms��
		if (ButtonReleaTimer.count==25) ButtonReleaTimer.update=1;
	}
	if (INTT_0==0)
	{
		ButtonReleaTimer.count=0;
	}

	
	if(ButtonDecreTimer.swit==1)   
	{
		ButtonDecreTimer.count=(ButtonDecreTimer.count+1)%1000;//����������50ms��
		if (ButtonDecreTimer.count==25)  ButtonDecreTimer.update=1;
	}
	
	if(AnimitationTimer.swit==1)	
	{
		AnimitationTimer.count=(AnimitationTimer.count+1)%(65530);//��Ϣ������ʱ(100ms)
		if(AnimitationTimer.count==50) AnimitationTimer.update=1;
	}
}




//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		TR0 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		else									ET0 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		else									PT0 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		else										TMOD &= ~0x04;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		else							INT_CLKO &= ~0x01;	//�����ʱ��
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		else									ET1 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		else									PT1 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		else										TMOD &= ~0x40;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		else							INT_CLKO &= ~0x02;	//�����ʱ��
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		AUXR &= ~(1<<4);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		else										IE2  &= ~(1<<2);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		else										AUXR &= ~(1<<3);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��
		else							INT_CLKO &= ~0x04;	//�����ʱ��

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	return 2;	//����
}




//=======================================================================
// ����: u8	Timer_config()
// ����: ��ʱ����ʼ������.
// ����: ��
// ����: ��
// �汾: V1.0, 2012-10-22
//========================================================================
void Timer_config_t0(void)
{
	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure.TIM_Value     = 65536UL - 44236UL;	//��ֵ,2ms�ж�һ��
	TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2
	
	TimerInit(&PageTimer);
	TimerInit(&InfoWinTimer);
	TimerInit(&tempFluTimer);
	TimerInit(&CursorFluTimer);
	TimerInit(&ButtonReleaTimer); 
	TimerInit(&ButtonDecreTimer);
	TimerInit(&AnimitationTimer); 														
}




//=======================================================================
// ����: u8	TimerInit()
// ����: ��ʱ��������ʼ��
// ����: ��ʱ������
// ����: ��
// �汾: V1.0, 2021-06-09
//========================================================================
void TimerInit(struct Timer *timer)
{
	(*timer).update=0;
	(*timer).count=0;
	(*timer).swit=0;
}




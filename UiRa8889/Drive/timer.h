
#ifndef	__TIMER_H
#define	__TIMER_H

#include	"config.h"

#define	Timer0						0
#define	Timer1						1
#define	Timer2						2
#define	Timer3						3
#define	Timer4						4

#define	TIM_16BitAutoReload			0
#define	TIM_16Bit					1
#define	TIM_8BitAutoReload			2
#define	TIM_16BitAutoReloadNoMask	3

#define	TIM_CLOCK_1T				0
#define	TIM_CLOCK_12T				1
#define	TIM_CLOCK_Ext				2

/*********************************************************************************/
extern struct Timer PageTimer;
extern struct Timer  InfoWinTimer;
extern struct Timer  tempFluTimer;
extern struct Timer  CursorFluTimer;
extern struct Timer  ButtonReleaTimer;
extern struct Timer  ButtonDecreTimer;
extern struct Timer  AnimitationTimer;
extern u32 CurentInfoWinTime;//��ǰ��Ϣ������ʱ��


struct Timer
{
	u16	count;	//��ǰ����ֵ
	u8	swit;	//��������
	u8	update;	//ʱ���Ƿ񵽴�
};


typedef struct
{
	u8	TIM_Mode;		//����ģʽ,  	TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	u8	TIM_Polity;		//���ȼ�����	PolityHigh,PolityLow
	u8	TIM_Interrupt;	//�ж�����		ENABLE,DISABLE
	u8	TIM_ClkSource;	//ʱ��Դ		TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	u8	TIM_ClkOut;		//�ɱ��ʱ�����,	ENABLE,DISABLE
	u16	TIM_Value;		//װ�س�ֵ
	u8	TIM_Run;		//�Ƿ�����		ENABLE,DISABLE
} TIM_InitTypeDef;


u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx);
void	Timer_config_t0(void);
void TimerInit(struct Timer *timer);
#endif

/*************	����˵��	**************

���ļ�ʵ�ֶ�ADS7843������

******************************************/
#include "ads7843.h"
#include "GPIO.h"
#include  "USART.h"
#include  "delay.h"
#include	"config.h"
#include	"screen.h"
#include	"String.h"


void Ads7843_Init(void)
{
u16 t;	
GPIO_InitTypeDef  IOP00;                 //Dout
GPIO_InitTypeDef  IOP01;                // Busy
GPIO_InitTypeDef  IOP02;                // Din
GPIO_InitTypeDef  IOP03;                 //Cs
GPIO_InitTypeDef  IOP04;                // Dclk

PrintString1("��ʼADS7843��ʼ��\r\n");
IOP00.	Pin=GPIO_Pin_0;
IOP00.	Mode=GPIO_PullUp;

IOP01.	Pin=GPIO_Pin_1;	
IOP01.	Mode=GPIO_PullUp;
	
	
IOP02.	Pin=GPIO_Pin_2;
IOP02.	Mode=GPIO_PullUp;   
	
IOP03.	Pin=GPIO_Pin_3;
IOP03.	Mode=GPIO_PullUp;   

IOP04.	Pin=GPIO_Pin_4;
IOP04.	Mode=GPIO_PullUp;   

	
GPIO_Inilize(GPIO_P0,&IOP00);	
GPIO_Inilize(GPIO_P0,&IOP01);	
GPIO_Inilize(GPIO_P0,&IOP02);	
GPIO_Inilize(GPIO_P0,&IOP03);	
GPIO_Inilize(GPIO_P0,&IOP04);

Ads_start();
Ads_w(0x90);
DCLK=1;  //һ��ʱ���½��ع���æ�ź�
delay_us(4);
DCLK=0;
delay_us(4);
t=Ads_r();
CS=1;
}


void Ads_start(void)
{
DCLK=0;
delay_us(3);
	
CS=1;
delay_us(3);
	
DIN=1;
delay_us(3);
	
DCLK=1;
delay_us(3);

CS=0;
}

void Ads_w(u8 dat)
{
u8 count=0;
DCLK=0;	
for(count=0;count<8;count++)
	{
	 if((dat&0x80)==0x80)
	 {
		 DIN=1;
		 //PrintString2("1");
	 }
	 else
	 {
		 DIN=0;
		  //PrintString2("0");
	 }
	 
	 DCLK=0;  //ʱ��������������
	 delay_us(1);
	 DCLK=1;
	 delay_us(1);
	 dat=dat <<1;
	}

}


int Ads_r(void)
{
int dat=0;
u8 count=0;
u8 t=0;
for(count=0;count<12;count++)
	{
	 dat=dat<<1;
	 DCLK=1;     //ʱ���½��ض�����
	 delay_us(1);
	 DCLK=0;
   delay_us(1);
	 t=DOUT;
	 if(t==1){dat++;}
	}
return dat;
}


//========================================================================
// ����: Cord_read()
// ����: ��ȡ������X,Y�����꣨����Ϊ��λ��
// ����:��������x,y��ָ��
// ����: ��
// �汾: V1.0, 2021-5-26
//========================================================================
void Cord_read()
{
	u8 str[5]; //��ʱ�ַ�������	
	u8 i; 
	float c=0.00;
	int t=0;	
	int xx=0,yy=0;
	for(i=0;i<6;i++)
	{
		Ads_start();
		Ads_w(0x90);

		DCLK=1;  //һ��ʱ���½��ع���æ�ź�
		delay_us(4);
		DCLK=0;
		delay_us(4);
		t=Ads_r();
		xx+=t;

		Ads_w(0xD0);
		DCLK=1;  //ʱ���½�����ָ��
		delay_us(4);
		DCLK=0;
		delay_us(4);
		t=Ads_r();
		yy+=t;
		CS=1; //�ͷ�оƬ	 
	}
	c=((xx/6)-200)/3680.0;
	if(c<0) c=0;  //���������
	if(c>1) c=1; 
	x=480-480*c;
	//#ifdef Debug
	PrintString1("x:");
	PrintString1(u8_to_str_4(x,str));
	//#endif

	c=((yy/6)-200)/3400.0;
	if(c<0) c=0;  //���������
	if(c>1) c=1;
	y=272-272*c;
	//	#ifdef Debug
	PrintString1(" y:");
	PrintString1(u8_to_str_4(y,str));
	PrintString1("\r\n");
	//	#endif
	res_05[0]=0x5A; //���±�־�Ĵ���
	res_07[0]=y;    //��������Ĵ���
	res_07[1]=y>>8;
	res_07[2]=x;
	res_07[3]=x>>8;
}
	















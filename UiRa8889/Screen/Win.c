
#include "Win.h"
#include "api.h"
#include "UserDef.h"
#include "USART.h"
#include "timer.h"
#include "All_8889_Pic_NOR.h"
#include "RA8889.h"
#include "screen.h"
#include "Button.h"
#include "Page.h"
#include "String.h"
#include "WinCall.h"
#include "WinCall1.h"
#include "Stdlib.h"

const  struct WinType code WinGroup[Wincount]={
/////////////////Setting����////////////////
{Select,Setting,SettingSelectFact,0xFF09,123,124,3},
{Info,Setting,SettingInfoFac,0x0105,139,0,0},
/////////////////Motor����////////////////
{Info,Motor,MotorSave,0x0106,140,0,0},
/////////////////Fans����////////////////
{Info,Fansped,FansSave,0x0106,140,0,0},
/////////////////Preheat����////////////////
{Info,Preheat,PreheSave,0x0106,140,0,0},	
 /////////////////Move����////////////////        
{Info,Move,MoveHoming,0x0107,141,0,0},
{Info,Move,MovemovingAsix,0x0108,142,0,0},
 ////////////////AutoLevel����/////////////   
{Info,AoutoLeve1,AoutoLeve1CalibrationProbe,0X010B,145,0,0},	
{Info,AoutoLeve1,AoutoLeve1CalibrationMes,0X010F,148,0,0}, 
{Info,AoutoLeve1,AoutoLeve1Save,0x0106,140,0,0},
{Select,AoutoLeve1,Aoutolevel1SelectCalibrate,0xFF17,123,124,2},
{Info,AoutoLeve2,AoutoLeve2CalibrationProbe,0X010B,145,0,0}, 
 /////////////////Failment����////////////////   
{Info,Failment,FailmentLow,0x010E,147,0,0},
//////////////////��ӡ����///////////////////
{Select,Print,PrintSelectCancelPrint,0xFF16,123,124,4},
////////////////��ӡ��ͣ����/////////////////
{SingleSelect,PrintPause,PrintPauseChangeDone,0xFF14,123,124,1},
{Info,PrintPause,PrintPauseChangeMes,0x0109,143,0,0}
////////////////Adjust����//////////////////
};

u8 CurentWin=0xFF;
/***************************���ں��ĺ���***************************/

//==============================
// ����: WinDebug()
// ����: ���ַ���ʾ����Ļ�̶�����
// ����:�ַ���
// ����: ��
// �汾: V1.0, 2021-6-18
//===============================
void WinDebug(u8 *String)
{
	Select_Font_Height_WxN_HxN_ChromaKey_Alignment(16,1,1,0,0);
	Print_GB2312String(3,0,0,0,60,200,50,0X00FFFFFF,0xFF00FF,String);
}



//==============================
// ����: Window_on()
// ����: �򿪵���
// ����:Ҫ�򿪵���������
// ����: ��
// �汾: V1.0, 2021-6-5
//===============================
void WindowOn(u8 WinName)
{
	u8 i;
	struct WinType Win;
	for(i=0;i<Wincount;i++)
	{
		if(WinName==WinGroup[i].Name) break;
	}
	if(i==Wincount||i>Wincount)
	{
		PrintString1("Invalide Win can not be open\r\n");
		return;
	}
	Win=WinGroup[i];
	CurentWin=Win.Name;			
	switch(Win.WinClass)
	{
	
		case Select:
		{
			WinGraph(Win);
			PrintString1("turn to select window_factory(draw emulate)\r\n");
			for(i=0;i<Wincount;i++)
			{
				if(WinGroup[i].Name==Win.Name&&WinGroup[i].PageName==Win.PageName) break;
			}
			if(i==Wincount||i>Wincount)
			{
				PrintString1("Invalide Win to find adderss\r\n");
				return;
			}
			
			mem_0603[0]=(WinGroup[i].Addr>>8)&0X00FF;
			mem_0603[1]=(WinGroup[i].Addr)&0X00FF;
			Send_Mesg_var(0x0603,1); //֪ͨmaster�Ѿ������������Info����
			break;
		}
		
		case SingleSelect:
		{
			WinGraph(Win);
			PrintString1("Turn to single select window(draw emulate)\r\n");
			for(i=0;i<Wincount;i++)
			{
				if(WinGroup[i].Name==Win.Name&&WinGroup[i].PageName==Win.PageName) break;
			}
			if(i==Wincount||i>Wincount)
			{
				PrintString1("Invalide Win to find adderss\r\n");
				return;
			}
			
			mem_0603[0]=(WinGroup[i].Addr>>8)&0X00FF;
			mem_0603[1]=(WinGroup[i].Addr)&0X00FF;
			Send_Mesg_var(0x0603,1); //֪ͨmaster�Ѿ������������Info����
			break;
		}
		case Info:
		{   
			WinGraph(Win);//ͼ��ʵ��
			PrintString1("turn to info window(draw emulate)\r\n");//�򿪵���
			Send_Mesg_var(0x0603,1);   //֪ͨmaster�Ѿ����뵯������)
			CurentInfoWinTime=mem_0604[0];
			CurentInfoWinTime=CurentInfoWinTime<<8;
			CurentInfoWinTime|=mem_0604[1];//�趨ʱ��
			CurentInfoWinTime=CurentInfoWinTime*(2); //(5ms)
			InfoWinTimer.swit=1;//��ʼ��ʱ
		}			
}
}


//========================================================================
// ����: WinGraph()
// ����: ����ͼƬʵ��
// ����:��������
// ����: ��
// �汾: V1.0, 2021-7-5
//========================================================================
void WinGraph(struct WinType Win)
{
	if(Win.WinClass==Select||Win.WinClass==SingleSelect)//ѡ�񵯴�
	{
		JPG_NOR(BINARY_INFO[Win.PicIndex].start_addr,BINARY_INFO[Win.PicIndex].img_size,canvas_image_width,480,0);
		JPG_NOR(BINARY_INFO[Win.PicIndex1].start_addr,BINARY_INFO[Win.PicIndex1].img_size,canvas_image_width,480,272);
		switch(Win.Position)
		{
			case 1:
			{
				BTE_Memory_Copy(0,canvas_image_width,(480+0-2),(0+0),0,canvas_image_width,(480+0-2),(0+0),0,canvas_image_width,119,67,12,242,138);		
				break;
			}
			case 2:
			{
				BTE_Memory_Copy(0,canvas_image_width,(480+242-4),(0+0),0,canvas_image_width,(480+242-4),(0+0),0,canvas_image_width,119,67,12,242,138);
				break;
			}
			case 3:
			{
				BTE_Memory_Copy(0,canvas_image_width,(480+0),(0+138-4),0,canvas_image_width,(480+0),(0+138-4),0,canvas_image_width,119,67,12,242,138);
				break;
			}
			
			case 4:
			{
				BTE_Memory_Copy(0,canvas_image_width,(480+242-4),(0+138-4),0,canvas_image_width,(480+242-4),(0+138-4),0,canvas_image_width,119,67,12,242,138);
				break;
			}
		}
	}
	else if(Win.WinClass==Info)//��Ϣ����
	{
		JPG_NOR(BINARY_INFO[Win.PicIndex].start_addr,BINARY_INFO[Win.PicIndex].img_size,canvas_image_width,119,67);		
	}
}


//========================================================================
// ����: SeletButtonPressEffect()
// ����:ѡ�񵯴��İ���Ч��
// ����:��������,x,y
// �汾: V1.0, 2021-6-10
//========================================================================	
void SeletButtonPressEffect(u8 WinName,u16 x,u16 y)
{	
	u8 Index;
	for(Index=0;Index<Wincount;Index++)
	{
		if(WinName==WinGroup[Index].Name) break;
	}
	if(Index>Wincount)
	{
		PrintString1("Invalid Win to Call Press Effect\r\n");
		return;
	}
	
	if(WinGroup[Index].WinClass==SingleSelect) 
	{
		if(x>81&&x<(81+118)&&y>92&&y<(92+60)) 
		{
			BTE_Memory_Copy(0,canvas_image_width,(480+0),(272+92),0,canvas_image_width,(480+0),(272+92),0,canvas_image_width,119,(67+92),12,240,43);	
		}
	}
	else
	{	
		if(x>81&&x<(81+118)&&y>92&&y<(92+60)) //155,170,90,20  OK
		{
			switch(WinGroup[Index].Position)
			{
				case 1:
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+0),(272+92),0,canvas_image_width,(480+0),(272+92),0,canvas_image_width,119,(67+92),12,240,43);
					break;
				}
				case 2:
				{
						
					BTE_Memory_Copy(0,canvas_image_width,(480+243),(272+90),0,canvas_image_width,(480+243),(272+90),0,canvas_image_width,123,(67+90),12,120,44);
					break;
				}
				case 3:
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+0),(272+227),0,canvas_image_width,(480+0),(272+227),0,canvas_image_width,119,(67+93),12,120,44);
					break;
				}
				case 4:
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+242),(272+226),0,canvas_image_width,(480+242),(272+226),0,canvas_image_width,123,(67+93),12,120,44);
					break;
				}
			}
		}
		
		else if(x>255&&x<(255+118)&&y>92&&y<(92+60))//CANCEL
		{
			switch(WinGroup[Index].Position)
			{
				case 2:
				{
						
					BTE_Memory_Copy(0,canvas_image_width,(480+243+120),(272+90),0,canvas_image_width,(480+243+120),(272+90),0,canvas_image_width,(123+120),(67+90),12,120,44);
					break;
				}
				case 3:
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+0+120),(272+227),0,canvas_image_width,(480+0+120),(272+227),0,canvas_image_width,(119+120),(67+93),12,120,44);
					break;
				}
				case 4:
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+242+120),(272+226),0,canvas_image_width,(480+242+120),(272+226),0,canvas_image_width,(119+122+2),(67+93),12,120,44);
					break;
				}
			}	
		}
	}
}




//========================================================================
// ����: WindowOff()
// ����: �رյ���
// ����:Ҫ�رյĵ���������
// ����: ��
// �汾: V1.0, 2021-6-5
//========================================================================
void WindowOff(u8 WinName)
{
	u8 i;
	u8 str[4];
	struct WinType Win;
	for(i=0;i<Wincount;i++)
	{
		if(WinName==WinGroup[i].Name) break;
	}
	if(i==Wincount||i>Wincount) 
	{
		PrintString1("Unvalid Win to turn off\r\n");
		return;
	}

	Win=WinGroup[i];
	CurentWin=0xFF;
	switch(Win.WinClass)
	{
		case Select: //������ѭ���ĵ�Э�鷵��һ��0603:00 00
		{
			mem_0603[0]=0x00;
			mem_0603[1]=0X00;
			PrintString1("�ر�ѡ�񵯴�\r\n");
			Send_Mesg_var(0x0603,1);  
			PageShift(Win.PageName);		
			break;
		}	
		case Info: ////������ѭ���ĵ�Э�鷵��һ��0603:00 00
		{
			mem_0603[0]=0x00;
			mem_0603[1]=0X00;
			Send_Mesg_var(0x0603,1);
			PrintString1("�ر���Ϣ����\r\n");				
			PageShift(Win.PageName);
			InfoWinTimer.count=0;
			InfoWinTimer.swit=0;
			break;
		}
	}
}



//========================================================================
// ����: GetWinClass()
// ����: ��ȡ���ڵ�����
// ����:��������
// ����: ��������
// �汾: V1.0, 2021-6-7
//========================================================================
u8 GetWinClass(u8 WinName)
{
	u8 Index;
	for(Index=0;Index<Wincount;Index++)
	{
		if(WinGroup[Index].Name==WinName) break;
	}
	if(Index==Wincount||Index>Wincount)
	{
		PrintString1("Invalid Win to get class\r\n");	
		return NULL;
	}
	return WinGroup[Index].WinClass;
}






//========================================================================
// ����: WinExecuteOkCall()
// ����: ִ�б༭(ѡ��)����OK�ص�����
// ����:��������
// �汾: V1.0, 2021-6-7
//========================================================================
void WinExecuteOkCall(u8 WinName)
{
	u8 index;
	for(index=0;index<WinOkCallCount;index++)
	{
		if(WinOkCallGroup[index].Name==WinName) break;
	}
	if(index==WinOkCallCount||index>WinOkCallCount)
	{
		PrintString1("Invalid Win to Call ok\r\n");
		return ;
	}
	WinOkCallGroup[index].FuncOk();
}


	
//========================================================================
// ����: WinExecuteCancleCall()
// ����: ִ�б༭(ѡ��)����Cancel�ص�����
// ����:��������
// �汾: V1.0, 2021-6-10
//========================================================================	
void WinExecuteCancleCall(u8 WinName)
{
	u8 index;
	for(index=0;index<WinCanCallCount;index++)
	{
		if(WinCanCallGroup[index].Name==WinName) break;
	}
	if(index==WinCanCallCount||index>WinCanCallCount)
	{
		PrintString1("Invalid Win to Call Cancel\r\n");
		return ;
	}
	WinCanCallGroup[index].FuncCan();
}




//========================================================================
// ����: SelectButtonCall()
// ����:ʵ��ѡ�񵯴��Ļص�����ִ��
// ����:��ǰ����,x,y
// �汾: V1.0, 2021-6-10
//========================================================================	
void SelectButtonCall(u8 WinName,u16 x, u16 y)
{   
	u8 index;
	for(index=0;index<WinOkCallCount;index++)
	{
		if(WinOkCallGroup[index].Name==WinName) break;
	}	
	if(index==WinOkCallCount||index>WinOkCallCount)
	{
		PrintString1("Invalid SelectButton to Ok Call\r\n");
	}
	else
	{
		if(x>81&&x<(81+118)&&y>92&&y<(92+60)) WinOkCallGroup[index].FuncOk();//�ж��Ƿ���OK
	}
	for(index=0;index<WinCanCallCount;index++)
	{
		if(WinCanCallGroup[index].Name==WinName) break;
	}
	if(index==WinCanCallCount||index>WinCanCallCount)
	{
		PrintString1("Invalid SelectButton to Ok Call\r\n");
	}	
	else  //255,170,90,20  CANCEL
	{ 	
		if(x>255&&x<(255+118)&&y>92&&y<(92+60)) WinCanCallGroup[index].FuncCan();//�ж��Ƿ���Can
	}
}



//========================================================================
// ����: SingleSelectButtonCall()
// ����:ʵ�ֵ�ѡ�񵯴��Ļص�����ִ��
// ����:��ǰ����,x,y
// �汾: V1.0, 2021-6-28
//========================================================================	
void SingleSelectButtonCall(u8 WinName,u16 x,u16 y)
{   
	u8 index;
	for(index=0;index<WinOkCallCount;index++)
	{
		if(WinOkCallGroup[index].Name==WinName) break;
	}	
	if(index==WinOkCallCount||index>WinOkCallCount)
	{
		PrintString1("Invalid SelectButton to Ok Call\r\n");
	}
	else
	{
		if(x>81&&x<(81+220)&&y>92&&y<(92+60)) WinOkCallGroup[index].FuncOk();
	}
}





/*************************�ص�����****************************/
////////////////////Setting���浯���ص�����//////////////////////
void SelectFacOkCall(void)
{				
	mem_0603[0]=0x00;
	mem_0603[1]=0XBA;
	Send_Mesg_var(0x0603,1);
	WindowOff(SettingSelectFact);	
}

void SelectFacCanCall(void)
{
	mem_0603[0]=0x00;
	mem_0603[1]=0XFE;
	Send_Mesg_var(0x0603,1);	
	WindowOff(SettingSelectFact);	
}



void SkipCall()
{
	mem_0603[0]=0x00;
	mem_0603[1]=0xBC;
	Send_Mesg_var(0x0603,1);	
}

void AgainCall()
{
	mem_0603[0]=0x00;
	mem_0603[1]=0xBD;
	Send_Mesg_var(0x0603,1);	
}


void PrintSelectCancelPrintOkCall()
{
	mem_0603[0]=0x00;
	mem_0603[1]=0xBB;
	Send_Mesg_var(0x0603,1);
}


void PrintSelectCancelPrintCanCall()
{
	mem_0603[0]=0x00;
	mem_0603[1]=0xFE;
	Send_Mesg_var(0x0603,1);
	WindowOff(PrintSelectCancelPrint);
}


void ChangeDoneOkCall()
{
	mem_0603[0]=0x00;
	mem_0603[1]=0xB6;
	Send_Mesg_var(0x0603,1);
	WindowOff(PrintSelectCancelPrint);
}








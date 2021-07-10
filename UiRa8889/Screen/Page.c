#include "Page.h"
#include "All_8889_Pic_NOR.h"
#include "api.h"
#include "UserDef.h"
#include "timer.h"
#include "USART.h"
#include "screen.h"


u16 Page_Id;//ҳ��ID
u8 Page_Name;

const struct PageType code PageGroup[PageCount]={
{0x0000,PowerOn,0,0},
{0x0031,Main,48,52},
{0x0062,Version,97,98},
{0x0054,Setting,83,85},
{0x0058,Motor,87,86},
{0x005A,Fansped,89,86},
{0x005C,Preheat,91,86},
{0x0042,Move,65,66},
{0x005F,AoutoLeve1,94,86},   //0ff
{0x0060,AoutoLeve2,95,86},    //on
{0x0034,MainPreheat,51,53}, 
{0x0045,Failment,68,69},
{0x002B,MainUdisk,42,52},

{0x0048,UdiskNext,71,78}, //��һ��
{0x004A,UdiskBoth,73,78}, //��+��  
{0x0049,UdiskLast,72,78}, //��һ��
{0x0047,UdiskOne,70,78}, //��һ��

{0x004C,UdiskNextUp,75,78}, //��һ��
{0x004E,UdiskBothUp,77,78}, //��+��  
{0x004D,UdiskLastUp,76,78}, //��һ��
{0x004B,UdiskOneUp,74,78},

{0x0068,PrintConfirm,103,104},
{0x0039,Print,56,60},
{0x002E,MainUdiskPreheat,45,53},
{0x003C,PrintPause,59,61},
{0x0050,Adjust,79,80}
};



//============================================
// ����: PageShiftGrap
// ����: ҳ���л���ͼ��ʵ��
// ����:Ҫ�л���ҳ�������
// ����: ��
// �汾: V1.0, 2021-6-18
//============================================
void PageShift(u8 PageName)
{
	u8 i;
	for(i=0;i<PageCount;i++)
	{
		if(PageGroup[i].Name==PageName) break;
	}
	if(i==PageCount||i>PageCount)
	{
		PrintString1("Invalid Page to turn\r\n");
		return;
	}
	JPG_NOR(BINARY_INFO[PageGroup[i].PicIndex].start_addr,BINARY_INFO[PageGroup[i].PicIndex].img_size,canvas_image_width,0,0);
	JPG_NOR(BINARY_INFO[PageGroup[i].PicIndex1].start_addr,BINARY_INFO[PageGroup[i].PicIndex1].img_size,canvas_image_width,0,272);
}




//===============================================
// ����: PageId_to_PageName()
// ����: ��ҳ��ID��ҳ�����ֵ��л�
// ����:ҳ��Id
// ����: �л�ҳ�������
// �汾: V1.0, 2021-6-7
//===============================================
u8 PageIdtoPageName(u16 PageId)
{
	u8 i;
	for(i=0;i<PageCount;i++)
		{
			if(PageGroup[i].Id==PageId) break;
		}

	return PageGroup[i].Name;
}



//===============================================
//����:UpdatePageId
//����:���õ�ǰָ����¼Ĵ����ͱ�����ֵ
//����������
//����ֵ����
//===============================================
void UpdatePageName()
{
	Page_Id=res_03[0];
	Page_Id=Page_Id<<8;
	Page_Id|=res_03[1];
	
	Page_Name=PageIdtoPageName(Page_Id);
}








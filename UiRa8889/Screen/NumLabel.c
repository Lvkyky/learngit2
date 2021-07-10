/*************����˵��**************
ʵ���˾��У�������롣ʵ����͸�����͸����ʾ��
***********************************/
#include "NumLabel.h"
#include "Page.h"
#include "screen.h"
#include "USART.h"
#include "api.h"
#include "Stdlib.h"
#include "UserDef.h"

const struct NumLabelVarType code NumLabelGroup[NumLabelVarCount]={
/////////////////////////Failment//////////////////////	
{0x0022,Failment,{CenterAlign,Untrans,34,28,30,Font16x16,0xFFFFFF,0x000000,{3,0},{2,0,""}},2},	
//////////////////////////Main����////////////////////	
{0X0000,Main,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,Main,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,Main,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,Main,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,Main,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,Main,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,Main,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,Main,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},//�¶ȱ���1	
//////////////////////////MainPreheat����////////////////////		
{0X0000,MainPreheat,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,MainPreheat,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,MainPreheat,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,MainPreheat,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,MainPreheat,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,MainPreheat,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,MainPreheat,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,MainPreheat,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},//�¶ȱ���2	
//////////////////////////Move����(x,y,z)//////////////////////
{0X0073,Move,{CenterAlign,Untrans,132,226,56,Font16x16,0xFFFFFF,0x000000,{3,2},{2,0,""}},4},
{0X0075,Move,{CenterAlign,Untrans,232,226,56,Font16x16,0xFFFFFF,0x000000,{3,2},{2,0,""}},4},
{0X0077,Move,{CenterAlign,Untrans,333,226,56,Font16x16,0xFFFFFF,0x000000,{3,2},{2,0,""}},4},
/////////////////////////Motor����(x,y,z,e)////////////////////////////
{0X0011,Motor,{CenterAlign,Untrans,144,89,72,Font16x16,0xFFFFFF,0x000000,{3,4},{2,0,""}},4},
{0X0013,Motor,{CenterAlign,Untrans,374,89,72,Font16x16,0xFFFFFF,0x000000,{3,4},{2,0,""}},4},
{0X0015,Motor,{CenterAlign,Untrans,144,139,72,Font16x16,0xFFFFFF,0x000000,{3,4},{2,0,""}},4},
{0X0017,Motor,{CenterAlign,Untrans,374,139,72,Font16x16,0xFFFFFF,0x000000,{3,4},{2,0,""}},4},
////////////////////////Fans����//////////////////////////////////
{0X000C,Fansped,{CenterAlign,Untrans,274,69,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},//���ȱ���
{0X0071,Fansped,{CenterAlign,Untrans,274,114,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},
{0X0072,Fansped,{CenterAlign,Untrans,274,159,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},

//////////////////////////////Preheat����//////////////////////////////////
{0X000F,Preheat,{CenterAlign,Untrans,274,69,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},//Ԥ�ȱ�����p1,p2,p3��
{0X0010,Preheat,{CenterAlign,Untrans,274,114,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0019,Preheat,{CenterAlign,Untrans,274,159,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},

/////////////////////////////AoutoLeve1����/////////////////////////////
{0X0079,AoutoLeve1,{CenterAlign,Untrans,179,69,100,Font16x16,0xFFFFFF,0x000000,{3,2},{0,2,"mm"}},2},
{0X007A,AoutoLeve1,{CenterAlign,Untrans,357,154,100,Font16x16,0xFFFFFF,0x000000,{3,1},{0,2,"mm"}},2},

/////////////////////////////AoutoLeve2����/////////////////////////////
{0X0079,AoutoLeve2,{CenterAlign,Untrans,179,69,100,Font16x16,0xFFFFFF,0x000000,{3,2},{0,2,"mm"}},2},
{0X007A,AoutoLeve2,{CenterAlign,Untrans,357,154,100,Font16x16,0xFFFFFF,0x000000,{3,1},{0,2,"mm"}},2},
////////////////////////////////Print����//////////////////////////////////////////
{0X0000,Print,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,Print,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,Print,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,Print,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,Print,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,Print,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,Print,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,Print,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},   
{0x0023,Print,{CenterAlign,Trans,(480+198),(272+140),72,Font24x24,0x0000F0,0x0000FF,{1,1},{0,1,"%"}},2},
{0x0077,Print,{CenterAlign,Trans,(480+302),(272+140),144,Font24x24,0x0000F0,0x0000FF,{1,2},{1,2,"Z:"}},4},

//////////////////////////MainUdisk����////////////////////	
{0X0000,MainUdisk,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,MainUdisk,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,MainUdisk,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,MainUdisk,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,MainUdisk,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,MainUdisk,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,MainUdisk,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,MainUdisk,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},//�¶ȱ���
////////////////////////MainUdiskPreheat����/////////////
{0X0000,MainUdiskPreheat,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,MainUdiskPreheat,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,MainUdiskPreheat,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,MainUdiskPreheat,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,MainUdiskPreheat,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,MainUdiskPreheat,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,MainUdiskPreheat,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,MainUdiskPreheat,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
////////////////////////Adjust����/////////////////////
{0X000B,Adjust,{CenterAlign,Untrans,274,70,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},
{0X000D,Adjust,{CenterAlign,Untrans,274,115,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},
{0X000C,Adjust,{CenterAlign,Untrans,274,160,48,Font16x16,0xFFFFFF,0x000000,{3,0},{1,1,"%"}},2},
////////////////////////PrintPause����//////////////////
{0X0000,PrintPause,{CenterAlign,Untrans,202,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0001,PrintPause,{CenterAlign,Untrans,272,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0006,PrintPause,{CenterAlign,Untrans,342,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0008,PrintPause,{CenterAlign,Untrans,412,36,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0003,PrintPause,{CenterAlign,Untrans,202,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0004,PrintPause,{CenterAlign,Untrans,272,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0007,PrintPause,{CenterAlign,Untrans,342,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},
{0X0009,PrintPause,{CenterAlign,Untrans,412,100,40,Font16x16,0xFFFFFF,0x000000,{3,0},{0,1,"C"}},2},

{0x0023,PrintPause,{CenterAlign,Trans,(480+198),(272+140),72,Font24x24,0x0000F0,0x0000FF,{1,1},{0,1,"%"}},2},
{0x0077,PrintPause,{CenterAlign,Trans,(480+302),(272+140),144,Font24x24,0x0000F0,0x0000FF,{1,2},{1,2,"Z:"}},4}
};







//============================================
// ����: StringFlush()
// ����: ���ݵ�ǰ��ҳ��ˢ���ַ���
// ����:��ǰҳ��
// ����: ��
// �汾: V1.0, 2021-6-12
//============================================
void NumLabelFlush(u8 PageName)
{  
	u8 index;
	u16 Absolutex,Absolutey;
	u8 Reletivex;
	u8 length,width;
	u32 color;
	u32 Bcolor;
	u8 DataCount;
	long int Valu;
	u32 BitPower;
	u8 *DataPointer=0;
	u8 i;
	u8 j;
	u8 WeiCount;
	u8 Right;
	u8 StrDisplay[20];//ˢ��String����������
	struct FormatType StringFormat;
	for(index=0;index<NumLabelVarCount;index++)
	{
		if(PageName==NumLabelGroup[index].PageName)  
		{
			Absolutex=NumLabelGroup[index].VarInfo.x;
			Absolutey=NumLabelGroup[index].VarInfo.y;
			width=NumLabelGroup[index].VarInfo.Width;
			length=NumLabelGroup[index].VarInfo.Length;
			color=NumLabelGroup[index].VarInfo.Color;
			Bcolor=NumLabelGroup[index].VarInfo.Bcolor;
			StringFormat=NumLabelGroup[index].VarInfo.Format;//���ݸ�ʽ
			if(VaddrtoPaddrVar(NumLabelGroup[index].Addr)!=NULL) 	DataPointer=VaddrtoPaddrVar(NumLabelGroup[index].Addr);//����ָ��			
			else return;
			DataCount=NumLabelGroup[index].DataLength;//���ݳ���
			
			/***************************������ֵ***************************/
			BitPower=1;//Ȩ��Ϊ1
			Valu=0;	//��Ϊ0
			if(DataCount==2)
			{
				Valu=*((int*)DataPointer);
			}
			else if(DataCount==4)
			{
				Valu=*((long int*)DataPointer);
			}
			

			if(Valu>10000000||Valu<-10000000)
			{
				PrintString1("������Χ����ˢ��\r\n");
				return;				
			}
			/***************************��ֵת��Ϊ�ַ���***********************/
			if(Valu==0)
			{   
				Right=NumLabelGroup[index].VarInfo.Format.Right;
				for(i=0;i<Right;i++)
				{
					StrDisplay[i]='0';
				}
				StrDisplay[i]='0';
				WeiCount=i+1;
			}
			else if(Valu>0)
			{							
				BitPower=1;//ȨΪ��1
				WeiCount=0;//λ����0
				while((Valu/BitPower)!=0) 
				{
					BitPower=BitPower*10;
					WeiCount++;//λ��
				}
				BitPower=BitPower/10;    
				for(i=0;i<WeiCount;i++)
				{
					StrDisplay[i]=(Valu/BitPower)+'0';           
					Valu=Valu%BitPower;					
					BitPower=BitPower/10;						
				}				
			}
			else 
			{   
				BitPower=1;
				WeiCount=0;
			    Valu=-Valu;	
				while((Valu/BitPower)!=0) 
				{
					BitPower=BitPower*10;
					WeiCount++;
				}
				BitPower=BitPower/10;
	
				StrDisplay[0]='-';
				WeiCount=WeiCount+1;
				for(i=1;i<WeiCount;i++)
				{
					StrDisplay[i]=(Valu/BitPower)+'0';           
					Valu=Valu%BitPower;					
					BitPower=BitPower/10;						
				}	
			}
			
			/*******************��С����********************/
			Right=NumLabelGroup[index].VarInfo.Format.Right;
			if(Right!=0)
			{
				j=WeiCount;
				for(i=0;i<Right;i++)
				{
					StrDisplay[j]=StrDisplay[j-1];
					j--;				
				}
				StrDisplay[j]='.';
				WeiCount=WeiCount+1;
			}
			
			/************************�ӵ�λ***********************/
			if(NumLabelGroup[index].VarInfo.Unit.Pre==0)//��׺
			{	
				for(j=0;j<NumLabelGroup[index].VarInfo.Unit.Count;j++)
				{
					StrDisplay[WeiCount]=NumLabelGroup[index].VarInfo.Unit.p[j];
					WeiCount++;
				}					
			}
			
			
			else if(NumLabelGroup[index].VarInfo.Unit.Pre==1)//ǰ׺
			{
				for(j=0;j<NumLabelGroup[index].VarInfo.Unit.Count;j++)
				{
					for(i=WeiCount;i>0;i--)
					{
						StrDisplay[i]=StrDisplay[i-1];
					}
					StrDisplay[0+j]=NumLabelGroup[index].VarInfo.Unit.p[j];
					WeiCount++;					
				}
			}
			else
			{
				//�ղ���				
			}
			StrDisplay[WeiCount]=0;
		   /************************��ʾ***********************/
			if(NumLabelGroup[index].VarInfo.TransFlag!=Trans)//��͸��
			{
				BTE_Solid_Fill(0,canvas_image_width,(480+Absolutex),(272+Absolutey),Bcolor,width,length);
				Select_Font_Height_WxN_HxN_ChromaKey_Alignment(NumLabelGroup[index].VarInfo.Length,1,1,0,0);
			}
			else
			{
				BTE_Solid_Fill(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0X000000,width,length);
				Select_Font_Height_WxN_HxN_ChromaKey_Alignment(NumLabelGroup[index].VarInfo.Length,1,1,1,0);
			}
			
			if(NumLabelGroup[index].VarInfo.Align==CenterAlign)//����
			{
				if(NumLabelGroup[index].VarInfo.Unit.Pre!=2)
				{
					Reletivex=width/2-((WeiCount*(length/2))+(NumLabelGroup[index].VarInfo.Unit.Count)*(length/2))/2;
				}
				else
				{
					Reletivex=width/2-((WeiCount*(length/2)))/2;			
				}	
				Print_GB2312String(3,0,0,(480+Absolutex+Reletivex),(272+Absolutey),width,length,color,Bcolor,StrDisplay);
				if(NumLabelGroup[index].VarInfo.TransFlag!=Trans)//��͸��
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,Absolutex,Absolutey,12,width,length);
				}
				else
				{
					BTE_Memory_Copy_Chroma_key(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,Absolutex,Absolutey,0X000000,width,length);
				}	
			}
			else if(NumLabelGroup[index].VarInfo.Align==LeftAlign)
			{
				Print_GB2312String(3,0,0,(480+Absolutex),(272+Absolutey),width,length,color,Bcolor,StrDisplay);
				if(NumLabelGroup[index].VarInfo.TransFlag!=Trans)//��͸��
				{
					BTE_Memory_Copy(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,Absolutex,Absolutey,12,width,length);
				}
				else
				{
					BTE_Memory_Copy_Chroma_key(0,canvas_image_width,(480+Absolutex),(272+Absolutey),0,canvas_image_width,Absolutex,Absolutey,0X000000,width,length);
				}
			}				
		}			
	}	
}

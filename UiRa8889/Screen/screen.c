#include "screen.h"
#include "timer.h"
#include "USART.h"
#include "delay.h"
#include "Exti.h"
#include "api.h"
#include "UserDef.h"
#include "All_8889_Pic_NOR.h"
#include  "RA8889.h"
#include  "Button.h"
#include  "Win.h"
#include  "Page.h"
#include  "String.h"
#include  "Stdlib.h"
#include  "Icon.h"
#include  "Fifo.h"
#include  "Input.h"
#include  "StringLabel.h"
#include  "NumLabel.h"
/*************	����˵��	**************
���ļ�����Ļ���ںˣ�ʵ���˴������ļĴ���
�����Լ�����֡�Ľ���ִ�С�
******************************************/
u8 send[15]; //�·�����֡������

u8 VerifyFlag=0; 
u8 VerifyFlag1=0; 
u8 RxSwitch=0;//�ر�  
u8 first_BYET=1;
u8 first_FIFO=1;
u8 first_FIFOBig=1;
u8 Rxcount=0;
u8 ParticleFlag=0;   //0��С����   1��������
u8 RxStatus=0;      //0:��      1��
u8 RxStatusBig=0;      //0:��      1��
u8 CmdExchange=1;


u16 x;
u16 y; 
u8 TouchStatus=Rlease;
u8 TouchDetectSwit=1;//��������

u8 CmdUpdateFlag=0;
struct CmdType CurentCmd;//��ǰ����


u8 FileSelect=0xFF;//�ļ�ѡ�б�־ 0XFF��ʾδѡ��


u8 FlushExchange=0; //����ˢ��
/******************************�Ĵ�����************************/
const struct ResType code ResGroup[ResCount]={
{0x03,res_03,2},
{0x05,res_05,1},	
{0x07,res_07,4},	
{0x0B,res_0B,1}	
};

u8 res_03[2];   //ҳ��ID
u8 res_05[1];   //����������±�־
u8 res_07[4];   //��������ѹ����ֵ
u8 res_0B[1];   //������ʹ��λ
/************************�Ĵ�����***********************/



/************************������************************/
const struct MappingType code VarMapTable[VarCount]={
{0x0140,mem_0140,40},	
{0x0603,mem_0603,2},	
{0x0604,mem_0604,2},		
{0x0030,mem_0030,16},		
{0x0038,mem_0038,16},		
{0x0020,mem_0020,2},		
{0x0021,mem_0021,2},		
{0x0022,mem_0022,2},		
{0x0060,mem_0060,2},		
{0x0061,mem_0061,2},		
{0x0062,mem_0062,2},	
{0x00B0,mem_00B0,16},	
{0X0700,mem_0700,2},
///////�¶ȱ���/////
{0X0000,mem_0000,2},		
{0X0001,mem_0001,2},		
{0X0006,mem_0006,2},		
{0X0008,mem_0008,2},		
{0X0003,mem_0003,2},		
{0X0004,mem_0004,2},		
{0X0007,mem_0007,2},		
{0X0009,mem_0009,2},

{0X0100,mem_0100,2},	
{0X0101,mem_0101,2},		
{0X0106,mem_0106,2},		
{0X0108,mem_0108,2},

///////MOVE(x,y,z)/////
{0X0073,mem_0073,4},		
{0X0075,mem_0075,4},		
{0X0077,mem_0077,4},

///////MOTOR(x,y,z,e)/////
{0X0011,mem_0011,4},		
{0X0013,mem_0013,4},	
{0X0015,mem_0015,4},		
{0X0017,mem_0017,4},

///////�༭MOTOR(x,y,z,e)/////
{0X0111,mem_0111,4},		
{0X0113,mem_0113,4},	
{0X0115,mem_0115,4},		
{0X0117,mem_0117,4},

//////�汾����//////
{0x0027,mem_0027,4},

//////Fans(YZE)///////
{0X000C,mem_000C,2},		
{0X0071,mem_0071,2},		
{0X0072,mem_0072,2},	
//////Fans Edit///////
{0X010C,mem_010C,2},		
{0X0171,mem_0171,2},
{0X0172,mem_0172,2},
/////Ԥ�ȱ���(p1,p2,p3,p4)///////
{0X000F,mem_000F,2},		
{0X0010,mem_0010,2},
{0X0019,mem_0019,2},
{0X001A,mem_001A,2},
/////Ԥ�ȱ༭����(p1,p2,p3,p4)///////
{0X010F,mem_010F,2},		
{0X0110,mem_0110,2},
{0X0119,mem_0119,2},
{0X011A,mem_011A,2},
/////AutoLevel����//////
{0X0079,mem_0079,2},
{0X007A,mem_007A,2},
/////AutoLevel�༭����//////
{0X0179,mem_0179,2},
{0X017A,mem_017A,2},
/////�ļ�ͼ��////////
{0X030F,mem_030F,2},		
{0X031F,mem_031F,2},
{0X032F,mem_032F,2},
{0X033F,mem_033F,2},
{0X034F,mem_0344F,2},
{0X035F,mem_0355F,2},
{0X036F,mem_036F,2},

{0x0024,mem_0024,5},//��ӡʱ��
{0x0023,mem_0023,2},//�ٷֱ�	

{0X000B,mem_000B,2},
{0X000C,mem_000C,2},
{0X000D,mem_000D,2},

{0X010B,mem_010B,2},
{0X010C,mem_010C,2},
{0X010D,mem_010D,2}
};

u8 mem_0140[40];
u8 mem_0603[2];  //��������
u8 mem_0604[2];  //��Ϣ����ʱ��
u8 mem_0030[16];
u8 mem_0038[16];
u8 mem_0020[2];
u8 mem_0021[2];
u8 mem_0022[2];
u8 mem_0060[2];
u8 mem_0061[2];
u8 mem_0062[2];
u8 mem_00B0[16];
u8 mem_0700[2];  //cmd

u8 mem_0000[2];
u8 mem_0001[2];
u8 mem_0006[2];
u8 mem_0008[2];
u8 mem_0003[2];
u8 mem_0004[2];
u8 mem_0007[2];
u8 mem_0009[2];//�¶ȱ���

u8 mem_0100[2];
u8 mem_0101[2];
u8 mem_0106[2];
u8 mem_0108[2];//�༭�����ص��¶ȱ���



u8 mem_0011[4];
u8 mem_0013[4];
u8 mem_0015[4];
u8 mem_0017[4];//�������X,Y,Z��E   

u8 mem_0027[4];//�汾��Ϣ


u8 mem_0111[4];//�������X,Y,Z��E    
u8 mem_0113[4];//Y
u8 mem_0115[4];//Z
u8 mem_0117[4];//E



u8 mem_000C[2];//Y ���Ȳ���
u8 mem_0071[2];//Z
u8 mem_0072[2];//E

u8 mem_010C[2];//Y ���Ȳ���
u8 mem_0171[2];//Z
u8 mem_0172[2];//E

u8 mem_001A[2];//Ԥ��
u8 mem_0010[2];
u8 mem_0019[2];
u8 mem_000F[2];

u8 mem_011A[2];//Ԥ��(�༭)
u8 mem_0110[2];
u8 mem_0119[2];
u8 mem_010F[2];


u8 mem_0073[4];//Move(x,y,z)
u8 mem_0075[4];
u8 mem_0077[4];

u8 mem_0079[2];//AutoLevel(al1 al2)
u8 mem_007A[2];

u8 mem_0179[2];//AutoLevel(al1 al2)�༭
u8 mem_017A[2];


u8 mem_030F[2];//�ļ�ͼ�����
u8 mem_031F[2];
u8 mem_032F[2];
u8 mem_033F[2];
u8 mem_0344F[2];
u8 mem_035F[2];
u8 mem_0355F[2];
u8 mem_036F[2];


u8 mem_0024[5];//��ӡʱ��
u8 mem_0023[2];//�ٷֱ�


u8 mem_000B[2];//��ӡ�ٶ�
u8 mem_000C[2];//Flow rate
u8 mem_000D[2];//��ȴ�ٶ�

u8 mem_010B[2];
u8 mem_010C[2];
u8 mem_010D[2];

u8 mem_0021[2];
/*********************������**********************/



/**************************�ں˺���*******************************/
//===============================================
// ����: Cmd_receive1()
// ����: �������������
// ����:����Ӳ������
// �汾: V1.0, 2021-6-16
//===============================================
void CmdReceive1(u8 SBUF)
{	
	if(VerifyFlag1==1)
	{
		RxSwitch=1;//�򿪽��տ���
		Rxcount=(SBUF+1);//Ҫ���յ��ֽ�
		COM2.RX_Cnt=0;//������ռ���
		VerifyFlag1=0;//
		if(Rxcount<10)						
		{	
			ParticleFlag=0;
			if(first_FIFO==1) first_FIFO=0;
			else
			{
				if((RX2_Buffer_FIFO.head+1)%FIFO_Length!=RX2_Buffer_FIFO.tail)//������δ��
				{
					RX2_Buffer_FIFO.head=(RX2_Buffer_FIFO.head+1)%FIFO_Length;//������һ��������
				}
				else
				{
					PrintString1("С���Ȼ��������\r\n");
				}	
			}
			RxStatus=0;
		}
		else
		{	
			ParticleFlag=1;
			if(first_FIFOBig==1) first_FIFOBig=0;
			else
			{
				if((RX2_Buffer_FIFOBig.head+1)%FIFO_LengthBig!=RX2_Buffer_FIFOBig.tail)//������δ��
				{
					RX2_Buffer_FIFOBig.head=(RX2_Buffer_FIFOBig.head+1)%FIFO_LengthBig;//������һ��������
				}
				else
				{
					PrintString1("�����Ȼ��������\r\n");
				}	
			}
			RxStatusBig=0;
		}	
	}	
	
	if(VerifyFlag==1) 
	{
		if(SBUF==0xA5)//A5��֤
		{
			VerifyFlag1=1;
		}
		VerifyFlag=0;
	}
	if(SBUF==0x5A) //5A��֤
	{
		VerifyFlag=1;
	}
	
	if(RxSwitch==1)//����֡����
	{	
		if(ParticleFlag==0)
		{
			if(Rxcount>0) 
			{
				RX2_Buffer_FIFO.dataa[RX2_Buffer_FIFO.head][COM2.RX_Cnt++]=SBUF;
				Rxcount--;	
			}
			if(Rxcount==0)
			{	
				RxSwitch=0;
				RxStatus=1;
			}	
		}
		else if(ParticleFlag==1)
		{
			if(Rxcount>0) 
			{
				RX2_Buffer_FIFOBig.dataa[RX2_Buffer_FIFOBig.head][COM2.RX_Cnt++]=SBUF;
				Rxcount--;	
			}
			if(Rxcount==0)
			{	
				RxSwitch=0;
				RxStatusBig=1;
			}	
		}
	}	
}



//===============================================
// ����: CmdUpdate()
// ����: �ӽ��ջ��������ȡһ��ָ����µ�ǰָ��
// ����:���յ�������
// �汾: V1.0, 2021-6-10
//===============================================
void UpdateCmd()
{
	if(Page_Name==MainUdisk||Page_Name==UdiskNext||Page_Name==UdiskBoth||Page_Name==UdiskLast||Page_Name==UdiskOne||
		Page_Name==UdiskNextUp||Page_Name==UdiskBothUp||Page_Name==UdiskLastUp||Page_Name==UdiskOneUp)
	{
		CmdExchange=1;//�󻺳�������	
	}
	else if(Page_Name==PrintPause||Page_Name==Print)
	{
			CmdExchange=0;//С����������
	}
	
	if(CmdExchange==1)                                         															
	{	
		CmdExchange=0;
		if(DeQueueBig()==0) DeQueue();
	}
	else
	{
		CmdExchange=1;
		if(DeQueue()==0) DeQueueBig();
	}
}


//===============================================
//���֣�VaddrtoPaddrRes
//���ܣ�������Ĵ�����ַ�õ��Ĵ���ʵ�ʵ�ַ
//�������Ĵ��������ַ
//����ֵ���Ĵ��������ַ
//===============================================
u8* VaddrtoPaddrRes(u8 ResAddress)        
{
	u8 index;
	for(index=0;index<ResCount;index++)
	{   
		if(ResAddress==ResGroup[index].ResAddr)  break;
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Res address\r\n");
		return NULL;;
	}
	else
	{
		return ResGroup[index].p;
	}
}


//===============================================
//���֣�VaddrtoPaddrVar()
//���ܣ������������ַ��ʵ�ʱ�����ַ��ת��
//���������������ַ
//����ֵ��ʵ�ʱ�����ַ
//===============================================
u8 *VaddrtoPaddrVar( u16 Vaddr)  
{
	u8 index;
	for(index=0;index<VarCount;index++)
	{
		if(Vaddr==VarMapTable[index].VarAddress) break;  
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Var address\r\n");
		return NULL;
	}
	else
	{
		return VarMapTable[index].p;
	}	
}


//===============================================
//���֣�VaddrtoCountVar
//���ܣ������������ַ��ʵ���ڴ��ַ��ת��
//���������������ַ
//����ֵ��ʵ�ʱ�����ַ�ڴ��С
//===============================================
u8 VaddrtoCountVar(u16 Vaddr)
{
	u8 index;
	for(index=0;index<VarCount;index++)
	{
		if(Vaddr==VarMapTable[index].VarAddress) break;  
	}
	if(index>VarCount||index==VarCount)
	{
		PrintString1("Invalid Var address\r\n");
		return NULL;
	}
	else
	{
		return VarMapTable[index].Size;
	}	
}



//===============================================
//���֣�Send_Mesg_res()
//���ܣ��·��Ĵ�����Ϣ
//�������Ĵ�����ַ���Ĵ������ݳ���
//����ֵ����
//===============================================
void Send_Mesg_res(u8 res_address,u8 data_length_r)      
{
	u8 j;
	u8 *DataPointer;
	DataPointer=VaddrtoPaddrRes(res_address);
	if(DataPointer==NULL)
	{
		PrintString1("��Ч�ĵ�ַ�Ĵ����·�ʧ��\r\n");
		return;	
	}	
	send[0]=0x5A;
	send[1]=0xA5;
	send[2]=0x03+data_length_r; //���ݳ���
	send[3]=0x81; //ָ��
	send[4]=res_address;//�Ĵ�����ַ
	send[5]=data_length_r; //��ȡ�ֽڳ���								
	for(j=0;j<data_length_r;j++)
	{
		send[j+6]=DataPointer[j]; 			 
	} 
	for(j=0;j<data_length_r+0x06;j++)
	{
		TX2_write2buff(send[j]);
	}								
}



//===============================================
//���֣�Send_Mesg_var()
//���ܣ��·�������Ϣ
//������������ַ��������ַ����
//����ֵ����
//===============================================
void Send_Mesg_var(u16 var_addres,u8 data_length_r )    
{
	u8 j;
	u8 T;
	u8 *DataPointer;
	DataPointer=VaddrtoPaddrVar(var_addres);
	if(DataPointer==NULL)
	{
		PrintString1("��Ч�ĵ�ַ�����·�ʧ��\r\n");
		return;	
	}
	
	
	send[0]=0x5A;
	send[1]=0xA5;
	send[2]=0x04+data_length_r*2; //���ݳ���
	send[3]=0x83; //ָ��
	send[4]=(var_addres>>8)&0x00FF;//�Ĵ�����ַ��λ
	send[5]=var_addres&0x00FF;//�Ĵ�����ַ��λ
	send[6]=data_length_r;  
	T=data_length_r*2;
	for(j=0;j<T;j++)
	{
		send[7+j]=DataPointer[j];		
	}
	T=data_length_r*2+7;
	for(j=0;j<T;j++)
	{
		TX2_write2buff(send[j]);   //����MASTER   
	}
}





//===============================================
//����Update_var_res
//����:���õ�ǰָ����¼Ĵ����ͱ�����ֵ
//����������
//����ֵ����
//===============================================
void Update_var_res()
{
	u8	j;
	u8 str[8];
	u8 res_address;
	u16 var_addres;
	u8 *DataPointer;
	switch(CurentCmd.Cmd)
	{
		case 0x80: 
		{ 				
			res_address=CurentCmd.Addr&0x00FF;
			DataPointer=VaddrtoPaddrRes(res_address); //�õ��Ĵ�������	
			if(DataPointer==NULL)
			{
				PrintString1("��Ч�ĵ�ַ�����мĴ�������\r\n");
			}
			else
			{
				for(j=0;j<CurentCmd.ByteSize;j++)//д������;
				{
					DataPointer[j]=CurentCmd.Data[j];   
				} 	
			}	
			break;
		 }    
					 
		case 0x82: 
		 {     
			var_addres=(0x00FF&(CurentCmd.Addr>>8));  
			var_addres=var_addres<<8;						 
			var_addres=(var_addres&0xFF00);
			var_addres|=(0x00FF&CurentCmd.Addr);	 
			DataPointer=VaddrtoPaddrVar(var_addres); //�õ���������	
			if(DataPointer==NULL)
			{	
				Select_Font_Height_WxN_HxN_ChromaKey_Alignment(16,1,1,0,0);	
				switch(var_addres)
				{		
					case 0x6000://ֱ��д�򻺴�
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*0+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*0+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6100:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*1+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*1+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6200:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*2+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*2+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6300:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*3+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*3+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6400:
					{	BTE_Solid_Fill(0,canvas_image_width,480,(40*4+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*4+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6500:
					{	BTE_Solid_Fill(0,canvas_image_width,480,(40*5+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*5+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					case 0x6600:
					{	
						BTE_Solid_Fill(0,canvas_image_width,480,(40*6+544),0x000000,480,40);
						Print_UnicodeString(3,0,0,480,(40*6+544),480,16,0XFFFFFF,0x000000,(u16 *)CurentCmd.Data);
						break;
					}
					default:
					{
						PrintString1("��Ч�ĵ�ַ�����б�������\r\n");
						break;
					}
				}
			}
			else
			{	
				for(j=0;j<CurentCmd.ByteSize;j++)
				{
					DataPointer[j]=CurentCmd.Data[j];  // д������;			
				}
			}
			break;
		 } 
		default:
		{
			PrintString1("δ��ʶ���ָ��\r\n");
			break;
		}
	}
}



//===============================================
//���֣�Return_var_res
//����:����Ҫ��ȡ�ļĴ����ͱ�����ֵ
//����������
//����ֵ����
//===============================================
void Return_var_res()
{
	u8 res_address;
	u16 var_addres;  
	switch(CurentCmd.Cmd)
	{
		case 0x81://����Ҫ��ȡ�ļĴ���ֵ
		 { 						     		
			res_address=CurentCmd.Addr&0x00FF;		
			Send_Mesg_res(res_address,CurentCmd.ByteSize);  
			break;
		 }    
											 
		case 0x83: //����Ҫ��ȡ�ı�����ֵ
		 {					 
			var_addres=(CurentCmd.Addr>>8)&0X00FF;   
			var_addres=var_addres<<8;						 
			var_addres=var_addres&0xFF00;
			var_addres|=CurentCmd.Addr&0X00FF;				  						 
			Send_Mesg_var(var_addres,CurentCmd.ByteSize);
			break;
		 }                                                       									 
	}
}



//===============================================
//���֣�ImediaFlushScreen
//����:��ҳ�棬��������Ҫ����ˢ�µ�Ԫ�ؽ���ˢ��
//������ҳ������
//����ֵ����
//===============================================         
void ImediaFlushScreen(u8 PageName)
{
	u16 PageId;
	u8 res_address;	
	u16 var_addres;
	u8  *DataPointer;
	u8 str[4];
	PageId=res_03[0];
	PageId =PageId<<8;
	PageId|=res_03[1];
	switch(CurentCmd.Cmd)
	{
		case 0x80:              
		 {   
			res_address=(CurentCmd.Addr&0x00FF);	
			switch(res_address)                  
			{
				case 0x03://�л�ҳ��
				{ 		   		
//					PrintString1("page_shift(u8 ID):");		
//					PrintString1(u8_to_str_hex(res_03[0],str));
//					PrintString1(u8_to_str_hex(res_03[1],str));			
//					PrintString1("\r\n");
//					PrintString1("");
					WindowOff(CurentWin);
					InputOff(CurrentInput);
					PageShift(PageName);			
					FileNameFlush(PageName);//�ļ�����ˢ��
					FileIconFlush(PageName);//�ļ�ͼ��ˢ��
					NumLabelFlush(PageName);
					StringLabelFlush(PageName);
				}
				
				case 0x0B: //�򿪴���
				{
					PrintString1("open_touch(void);\r\n");	
					break;
				}
				
				default:
				{
					PrintString1("��������Ĵ�������д\r\n");	
					PrintString1("���ظ��±�־������\r\n");	
					break;
				}
			} 
			break;
		}   
							 
			case 0x82:                
			 {
				  var_addres=(CurentCmd.Addr>>8)&0X00FF;   
				  var_addres=var_addres<<8;						 
				  var_addres=var_addres&0xFF00;
				  var_addres|=(CurentCmd.Addr&0X00FF);
				  DataPointer=VaddrtoPaddrVar(var_addres); //�õ���������		  
				  if(var_addres==0x0603)
				  {	    
					  WinFlush(PageName);				  
				  }
				  break;
			 }			  					
	}
}	 
/**********************�ں˺���**************************/








/*********************��Ļˢ�º���**********************/


//============================================
// ����: WinFlush()
// ����: ����ˢ�º���
// ����: ��
// �汾: V1.0, 2021-6-17
//============================================
void WinFlush(u8 PageName)
{
	u8 Index;
	u16 M0603;
	M0603=mem_0603[0];
	M0603 =M0603<<8;
	M0603|=mem_0603[1];
	if(M0603==0x00)
	{	
		WindowOff(CurentWin);
	}
	else
	{
		for(Index=0;Index<Wincount;Index++)
		{
			if(WinGroup[Index].PageName==PageName&&M0603==WinGroup[Index].Addr)break;
		}
		if(Index==Wincount||Index>Wincount) PrintString1("��Ч�ĵ���\r\n");
		else
		{	PrintString1("��������\r\n");	
			WindowOn(WinGroup[Index].Name);
		}
	}
}




//============================================
// ����: FileNameFlush()
// ����: ���ļ����ֽ���ˢ��
// ����:��ǰҳ��
// ����: ��
// �汾: V1.0, 2021-6-23
//============================================
void FileNameFlush(u8 PageName)
{		
	if(PageName==UdiskOne||PageName==UdiskNext||PageName==UdiskBoth||PageName==UdiskLast||
		PageName==UdiskNextUp||PageName==UdiskBothUp||PageName==UdiskLastUp||PageName==UdiskOneUp)   
	{		
		BTE_Memory_Copy(0,canvas_image_width,480,544,0,canvas_image_width,480,544,0,canvas_image_width,30,0,12,380,272);
	}
	else if(PageName==PrintConfirm)
	{	
		if(FileSelect==0xFF) 
		{
			
		}
		else
		{
			BTE_Memory_Copy(0,canvas_image_width,480,(544+40*FileSelect),0,canvas_image_width,480,(544+40*FileSelect),0,canvas_image_width,40,120,12,380,16);
			FileSelect=0xFF;
		}
	}
}



	
	



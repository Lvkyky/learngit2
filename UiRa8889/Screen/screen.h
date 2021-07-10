#ifndef __SCREEN_H
#define __SCREEN_H	
#include "STC15Fxxxx.H"

#define Debug //������ϢDebug����
#define VarCount 70
#define ResCount 4  

#define Trans 1
#define Untrans 0

#define Font16x16 16
#define Font24x24 24

#define CenterAlign 0
#define LeftAlign 1


struct ResType//�Ĵ���
{
	u8 ResAddr;
	u8 *p;
	u8 DataLength;
};                


struct MappingType
{
	u16 VarAddress;
	u8 *p;
	u8 Size;
}; 


struct CmdType
{
  u8 Cmd;
  u16 Addr;
  u8 ByteSize;
  u8 Data[80];
}; 

	
enum VarClas{STRING=0x00,WINDOW,ICON,CMD,NUM,TIME};//�������͵�ö��
enum Pre{Pressed=0X00,Rlease,PresLong};


extern u8 VerifyFlag1;  
extern u8 VerifyFlag; 
extern u8 RxSwitch;  
extern u8 first_BYET;
extern u8 Rxcount;
extern u8 ParticleFlag;
extern u8 first_FIFO;
extern u8 first_FIFOBig;
extern u8 RxStatus;
extern u8 RxStatusBig;
extern u8 CmdExchange;


extern struct CmdType CurentCmd;//ָ��ṹ��
extern u8 CmdUpdateFlag;


extern u8 send[15];//�·�����֡������
	
extern u16 x;
extern u16 y; //����
extern u8 TouchStatus;
extern u8 TouchDetectSwit;


extern u16 Page_Id;
extern u8 FileSelect;

extern u8 FlushExchange;

/*************************������*******************************/
extern u8 mem_0140[40];
extern u8 mem_0603[2];  //��������
extern u8 mem_0604[2];  //����ʱ��
extern u8 mem_0030[16];
extern u8 mem_0038[16];
extern u8 mem_0020[2];
extern u8 mem_0021[2];
extern u8 mem_0022[2];
extern u8 mem_0060[2];
extern u8 mem_0061[2];
extern u8 mem_0062[2];
extern u8 mem_00B0[16];

extern u8 mem_0000[2];
extern u8 mem_0001[2];
extern u8 mem_0006[2];
extern u8 mem_0008[2];
extern u8 mem_0003[2];
extern u8 mem_0004[2];
extern u8 mem_0007[2];
extern u8 mem_0009[2];//�¶ȱ���


extern u8 mem_0100[2];
extern u8 mem_0101[2];
extern u8 mem_0106[2];
extern u8 mem_0108[2];//�༭�����ص��¶ȱ���


extern u8 mem_0700[2]; //CMD_addr
extern u8 mem_0027[4];//�汾��Ϣ

extern u8 mem_0011[4];
extern u8 mem_0013[4];
extern u8 mem_0015[4];
extern u8 mem_0017[4];//�������

extern u8 mem_0111[4];//�������X,Y,Z��E    
extern u8 mem_0113[4];//Y
extern u8 mem_0115[4];//Z
extern u8 mem_0117[4];//E

extern u8 mem_010C[2];//f1 ���Ȳ���
extern u8 mem_0171[2];//f2
extern u8 mem_0172[2];//f3

extern u8 mem_000C[2];//f1���Ȳ������༭��
extern u8 mem_0071[2];//f2
extern u8 mem_0072[2];//f3


extern u8 mem_001A[2];//Ԥ��
extern u8 mem_0010[2];
extern u8 mem_0019[2];
extern u8 mem_000F[2];

extern u8 mem_011A[2];//Ԥ��(�༭)
extern u8 mem_0110[2];
extern u8 mem_0119[2];
extern u8 mem_010F[2];


extern u8 mem_0073[4];//Move(x,y,z)
extern u8 mem_0075[4];
extern u8 mem_0077[4];


extern u8 mem_0079[2];//AutoLevel(al1 al2)
extern u8 mem_007A[2];

extern u8 mem_0179[2];//AutoLevel(�༭)
extern u8 mem_017A[2];



extern u8 mem_030F[2];//�ļ�ͼ�����
extern u8 mem_031F[2];
extern u8 mem_032F[2];
extern u8 mem_033F[2];
extern u8 mem_0355F[2];
extern u8 mem_036F[2];
extern u8 mem_0344F[2];


extern u8 mem_0024[5];//��ӡʱ��
extern u8 mem_0023[2];//�ٷֱ�

extern u8 mem_000B[2];//��ӡ�ٶ�
extern u8 mem_000C[2];//Flow rate
extern u8 mem_000D[2];//��ȴ�ٶ�

extern u8 mem_010B[2];
extern u8 mem_010C[2];
extern u8 mem_010D[2];
extern u8 mem_0021[2];
/***********************������****************************/
	
	
	
	
/**********************�Ĵ�����************************/	
extern struct ResType code ResGroup[ResCount];	
extern u8 res_03[2];   //ҳ��ID
extern u8 res_05[1];   //����������±�־
extern u8 res_07[4];   //��������ѹ����ֵ
extern u8 res_0B[1];   //������ʹ��λ	 
/***************************�Ĵ�����***********************/	


u8 *VaddrtoPaddrVar( u16 Vaddr);
u8* VaddrtoPaddrRes(u8 ResAddress);
u8 VaddrtoCountVar(u16 Vaddr);

void Send_Mesg_res(u8 res_address,u8 data_length_r);
void Send_Mesg_var(u16 var_addres,u8 data_length_r );
void Update_var_res();
void Return_var_res();
void ImediaFlushScreen(u8 PageName);
void UpdateCmd();//�����������
void CmdReceive1(u8 SBUF);//�������1

void Cursor_on();//�򿪹��
void Cursor_off();//�رչ��
void Flush_cursor(u16 x,u16 y);//���ˢ��

void WinFlush(u8 PageName);
void FileNameFlush(u8 PageName);
void AnimationFlush();
#endif



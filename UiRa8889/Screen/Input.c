#include "Input.h"
#include "Page.h"
#include "USART.h"
#include "api.h"
#include "UserDef.h"
#include "Page.h"
#include "All_8889_Pic_NOR.h"
#include "screen.h"
#include "Stdlib.h"
#include "String.h"
#include "Win.h"
#include "delay.h"
#include "timer.h"
u8 str_num[9]={0,'0','0','0','0','0','0','0','0'}; 
u8 CurrentInput=0xFF;
u8 CursorRever=0;
u8 Cursorx=60;
u8 Cursory=80;//���

const struct InputType code InputGroup[InputCount]={
///////////////////////Main//////////////	
{Main,MainEditt1,113,120,{UnsingedInt,3,0},0x0100},           
{Main,MainEditt2,113,120,{UnsingedInt,3,0},0x0101},
{Main,MainEditt3,113,120,{UnsingedInt,3,0},0x0106},
{Main,MainEditt4,113,120,{UnsingedInt,3,0},0x0108},
/////////////////Motor����////////////////
{Motor,MoveEditx,112,120,{UnsingedFloat,3,4},0x0111},
{Motor,MoveEdity,112,120,{UnsingedFloat,3,4},0x0113},
{Motor,MoveEditz,112,120,{UnsingedFloat,3,4},0x0115},
{Motor,MoveEdite,112,120,{UnsingedFloat,3,4},0x0117},
/////////////////Fans����////////////////
{Fansped,FansEditF1,111,120,{UnsingedInt,3,0},0x010C},
{Fansped,FansEditF2,111,120,{UnsingedInt,3,0},0x0171},
{Fansped,FansEditF3,111,120,{UnsingedInt,3,0},0x0172},
/////////////////Preheat����////////////////
{Preheat,PreheatEditP1,113,120,{UnsingedInt,3,0},0X010F},
{Preheat,PreheatEditP2,113,120,{UnsingedInt,3,0},0X0110},
{Preheat,PreheatEditP3,113,120,{UnsingedInt,3,0},0X0119},	
 ////////////////AutoLevel����/////////////   
{AoutoLeve1,Auto1EditAl1,117,120,{Float,2,2},0X0179},
{AoutoLeve1,Auto1EditAl2,117,120,{Float,2,2},0X017A},
 ////////////////AutoLeve2����/////////////  
{AoutoLeve2,Auto2EditAl1,117,120,{Float,2,2},0X0179},
{AoutoLeve2,Auto2EditAl2,117,120,{Float,2,2},0X017A},
//////////////////��ӡ����///////////////////
{Print,PrintEditt1,113,120,{UnsingedInt,3,0},0x0100},           
{Print,PrintEditt2,113,120,{UnsingedInt,3,0},0x0101},
{Print,PrintEditt3,113,120,{UnsingedInt,3,0},0x0106},
{Print,PrintEditt4,113,120,{UnsingedInt,3,0},0x0108},
////////////////Adjust����//////////////////
{Adjust,AdjustEditAd1,115,120,{UnsingedInt,3,0},0X010B},
{Adjust,AdjustEditAd2,116,120,{UnsingedInt,3,0},0X010D},
{Adjust,AdjustEditAd3,111,120,{UnsingedInt,3,0},0X010C}
};

const struct NumButtonType code NumButtonGroup[NumButtonCount]={
{EditBack,402,184,79,88},
{EditOk,403,2,78,94},
{Edit7,176,16,60,60},
{Edit8,245,16,60,60},
{Edit9,315,16,60,60},
{Edit4,176,76,60,60},
{Edit5,245,76,60,60},
{Edit6,315,76,60,60},
{Edit1,176,136,60,60},
{Edit2,245,136,60,60},
{Edit3,315,136,60,60},
{EditDian,176,196,60,60},
{Edit0,245,196,60,60},
{EditX,315,196,60,60},
{EditSined,406,99,69,75}
};//���ּ���





void  ClearStrNum(u8 str[9])
{
	u8 j;
	str[0]=0;
	for(j=1;j<9;j++) //δ���
	{
		str[j]=='0';
	}
}


u8 FindSing(u8 str[9])
{
	u8 j;
	for(j=0;j<9;j++) //δ���
	{
		if(str[j]=='-') return j;
	}
	return 0XFF;
}


u8 FindDot(u8 str[9])
{
	u8 j;
	for(j=0;j<9;j++) //δ���
	{
		if(str[j]=='.') return j;
	}
	return 0XFF;
}


u8 FindEnd(u8 str[9])
{
	u8 j;
	for(j=0;j<9;j++) //δ���
	{
		if(str[j]==0) return j;
	}
	return 0XFF;
}




//========================================================================
// ����: KeyDealFloat()
// ����: �����ַ��Ĳ���
// ����:ȫ���ַ�����Ҫ������ַ�
// �汾: V1.0, 2021-6-30
//========================================================================
void KeyDealUnsignedFloat(struct InputType Input,u8 str[9],u8 inser)
{
	u8 j=0;
	u8 i=0;
	if(inser=='X') //ɾ��������
	{
		i=FindEnd(str);
		if(i!=0)
		{
			str[i-1]=str[i];
			str[i]='0';
		}
	}
	else//������㴦��
	{
		if(inser!='.'&&FindDot(str)==0XFF)  //����Ĳ��ǵ㲢�����滹û��С����
		{
			j=FindEnd(str);
			if(j<Input.DataClass.IntCount)  //δ���
			{
				str[j]=inser;
				str[j+1]=0;	
			}
			else    //���
			{
				for(i=0;i<(Input.DataClass.IntCount-1);i++)
				{
					str[i]=str[i+1];
				}
				str[i]=inser;
			}
		}

		else if(inser=='.'&&FindDot(str)==0XFF) //�������С���㣬��������û��С����
		 {
			j=FindEnd(str);
			str[j]='.';
			str[j+1]=0;
		 }
	 
		else if(inser!='.'&&FindDot(str)!=0XFF) //����Ĳ���С���㣬����������С����
		 {
			j=FindEnd(str);
			if(j<(Input.DataClass.IntCount+Input.DataClass.DotCount+1)) //δ��� 8
			{
				 str[j]=inser;
				 str[j+1]=0;
			}
			else //���
			{
				i=FindDot(str); //���λ��
				for(j=0;j<(i-1);j++)
				{
					str[j]=str[j+1];
				}
				str[i-1]=str[i+1];//��֮ǰ����λ				
				j=1;			
				while((i+j)<(Input.DataClass.IntCount+Input.DataClass.DotCount))
				{
					 str[i+j]=str[i+j+1];
					 j++;
				}
				str[(Input.DataClass.IntCount+Input.DataClass.DotCount)]=inser;
			}
		}
	 else if(inser=='.'&&FindDot(str)!=0XFF) //�������С���㣬����������С����
	 {
		//�ղ���
	 }
	}
}





//========================================================================
// ����: KeyDealFloat()
// ����: �����ַ��Ĳ���
// ����:ȫ���ַ�����Ҫ������ַ�
// �汾: V1.0, 2021-6-30
//========================================================================
void KeyDealFloat(struct InputType Input,u8 str[9],u8 inser)
{
	u8 j=0;
	u8 i=0;
	if(inser=='X') //ɾ��������
	{
		i=FindEnd(str);
		if(i!=0)
		{
			str[i-1]=str[i];
			str[i]='0';
		}
	}
	else if(inser=='-')//���Ŵ���
	{
		if(FindSing(str)==0xFF)
		{
			for(i=FindEnd(str);i>0;i--)
			{
				str[i+1]=str[i];	
			}
			str[1]=str[0];
			str[0]='-';
		}
		else
		{
			for(i=0;i<FindEnd(str);i++)
			{
				str[i]=str[i+1];	
			}
		}			
	}
	else
	{
		if(FindSing(str)==0xFF)//����
		{
			if(inser!='.'&&FindDot(str)==0XFF)//����Ĳ��ǵ㲢��û��С����
			 {
				j=FindEnd(str);
				if(j<Input.DataClass.IntCount)//δ���
				{
					str[j]=inser;
					str[j+1]=0;	
				}
				else//���
				{
					for(i=0;i<(Input.DataClass.IntCount-1);i++)
					{
						str[i]=str[i+1];
					}
					str[i]=inser;
				}
			 }

			else if(inser=='.'&&FindDot(str)==0XFF) //�������С���㲢��û��С����
			 {
				j=FindEnd(str);
				str[j]='.';
				str[j+1]=0;
			 }
		 
			else if(inser!='.'&&FindDot(str)!=0XFF) //����Ĳ���С���㣬����������С����
			 {
				j=FindEnd(str);
				if(j<(Input.DataClass.IntCount+Input.DataClass.DotCount+1)) //δ���
				{
					 str[j]=inser;
					 str[j+1]=0;
				}
				else //���
				{
					i=FindDot(str); //���λ��
					for(j=0;j<(i-1);j++)
					{
						str[j]=str[j+1];
					}
					str[i-1]=str[i+1];//��֮ǰ����λ				
					j=1;			
					while((i+j)<(Input.DataClass.IntCount+Input.DataClass.DotCount))
					{
						 str[i+j]=str[i+j+1];
						 j++;
					}
					str[(Input.DataClass.IntCount+Input.DataClass.DotCount)]=inser;
				}
			 }
			else if(inser=='.'&&FindDot(str)!=0XFF) //�������С���㣬����������С����
			 {
				//�ղ���
			 }	
		  }
		else//����
		{
			if(inser!='.'&&FindDot(str)==0XFF)  //����Ĳ��ǵ㲢�����滹û��С����
			 {
				j=FindEnd(str);
				if(j<(Input.DataClass.IntCount+1)) //δ���
				{
					str[j]=inser;
					str[j+1]=0;	
				}
				else//���
				{
					for(i=1;i<(Input.DataClass.IntCount);i++)
					{
						str[i]=str[i+1];
					}
					str[i]=inser;
				}
			 }

			else if(inser=='.'&&FindDot(str)==0XFF) //�������С���㣬��������û��С����
			 {
				j=FindEnd(str);
				str[j]='.';
				str[j+1]=0;
			 }
		 
			else if(inser!='.'&&FindDot(str)!=0XFF) //����Ĳ���С���㣬����������С����
			 {
				j=FindEnd(str);
				if(j<(Input.DataClass.IntCount+Input.DataClass.DotCount+2)) //δ���
				{
					 str[j]=inser;
					 str[j+1]=0;
				}
				else //���
				{
					i=FindDot(str); //���λ��
					for(j=1;j<(i-1);j++)
					{
						str[j]=str[j+1];
					}
					str[i-1]=str[i+1];//��֮ǰ����λ				
					j=1;			
					while((i+j)<(Input.DataClass.IntCount+Input.DataClass.DotCount+1))
					{
						 str[i+j]=str[i+j+1];
						 j++;
					}
					str[(Input.DataClass.IntCount+Input.DataClass.DotCount+1)]=inser;
				}
			 }
			else if(inser=='.'&&FindDot(str)!=0XFF) //�������С���㣬����������С����
			 {
				//�ղ���
			 }	
		}
	  }
}



void KeyDealUnsingedInt(u8 str[9],u8 inser)
{
	u8 i=0;
	if(inser=='X') //�����ɾ����
	{
		i=FindEnd(str);
		if(i!=0)
		{
		str[i-1]=str[i];
		str[i]='0';
		}
	}
	else
	{
		i=FindEnd(str);
		if(i<3)  //δ���
		{
		str[i]=inser;
		str[i+1]=0;	
		}
		else    //���
		{
		str[0]=str[1];
		str[1]=str[2];
		str[2]=inser;
		}
	}
}



//========================================================================
// ����: KeyScanUnsinedInt()
// ����: ���ּ���ɨ�����1
// ����:��������x,y,��������
// ����: ��
// �汾: V1.0, 2021-6-7
//========================================================================
void KeyScanUnsingedInt(struct InputType Input,u16 x,u16 y)
{
	if(IsPushNumButton(NumButtonGroup[2],x,y))  //7
	{
		KeyDealUnsingedInt(str_num,'7');  	
	}
	else if(IsPushNumButton(NumButtonGroup[3],x,y)) //8
	{
		KeyDealUnsingedInt(str_num,'8');	
	}
	else if(IsPushNumButton(NumButtonGroup[4],x,y)) //9
	{
		KeyDealUnsingedInt(str_num,'9');	
	}
		
	else if(IsPushNumButton(NumButtonGroup[5],x,y)) //4
	{
		KeyDealUnsingedInt(str_num,'4');		
	}
	else if(IsPushNumButton(NumButtonGroup[6],x,y)) //5
	{
		KeyDealUnsingedInt(str_num,'5');
	}
	else if(IsPushNumButton(NumButtonGroup[7],x,y)) //6
	{	
		KeyDealUnsingedInt(str_num,'6');
	}
		
	else if(IsPushNumButton(NumButtonGroup[8],x,y))  //1
	{
		KeyDealUnsingedInt(str_num,'1');	 	
	}
	else if(IsPushNumButton(NumButtonGroup[9],x,y))  //2
	{
		KeyDealUnsingedInt(str_num,'2');	
	}
	else if(IsPushNumButton(NumButtonGroup[10],x,y))  //3
	{
		KeyDealUnsingedInt(str_num,'3');
	}	
		
	else if(IsPushNumButton(NumButtonGroup[12],x,y))  //0
	{
		KeyDealUnsingedInt(str_num,'0');	
	}
	else if(IsPushNumButton(NumButtonGroup[13],x,y))  //X
	{
		KeyDealUnsingedInt(str_num,'X');	
	}
		
	else if(IsPushNumButton(NumButtonGroup[0],x,y))  //back
	{
		InputExecuteCancleCall(Input);
	}
			
	else if(IsPushNumButton(NumButtonGroup[1],x,y))  //ok
	{   
		InputExecuteOkCall(Input);
	}
}	
	

//========================================================================
// ����: KeyScanUnsingedFloat()
// ����: ���ּ���ɨ�����
// ����:��������x,y,��������
// ����: ��
// �汾: V1.0, 2021-6-7
//========================================================================
void KeyScanUnsingedFloat(struct InputType Input,u16 x,u16 y)
{
	if(IsPushNumButton(NumButtonGroup[2],x,y))  //7
	{
		PrintString1("7 is pressed\r\n"); 
		KeyDealUnsignedFloat(Input,str_num,'7');  	
	}
		
	else if(IsPushNumButton(NumButtonGroup[3],x,y)) //8
	{
		PrintString1("8 is pressed\r\n"); 
		KeyDealUnsignedFloat(Input,str_num,'8');	
	}
	else if(IsPushNumButton(NumButtonGroup[4],x,y)) //9
	{
		PrintString1("9 is pressed\r\n");
		KeyDealUnsignedFloat(Input,str_num,'9');	
	}
		
	else if(IsPushNumButton(NumButtonGroup[5],x,y)) //4
	{
		PrintString1("4 is pressed\r\n"); 	
		KeyDealUnsignedFloat(Input,str_num,'4');		
	}
	else if(IsPushNumButton(NumButtonGroup[6],x,y)) //5
	{
		PrintString1("5 is pressed\r\n");
		KeyDealUnsignedFloat(Input,str_num,'5');
	}
	else if(IsPushNumButton(NumButtonGroup[7],x,y)) //6
	{
		PrintString1("6 is pressed\r\n");	
		KeyDealUnsignedFloat(Input,str_num,'6');
	}
	else if(IsPushNumButton(NumButtonGroup[8],x,y))  //1
	{
		PrintString1("1 is pressed\r\n");
		PrintString1("the pressed effect\r\n");
		KeyDealUnsignedFloat(Input,str_num,'1');	 	
	}
	else if(IsPushNumButton(NumButtonGroup[9],x,y))  //2
	{
		PrintString1("2 is pressed\r\n");  
		KeyDealUnsignedFloat(Input,str_num,'2');	
	}
	else if(IsPushNumButton(NumButtonGroup[10],x,y))  //3
	{
		PrintString1("3 is pressed\r\n"); 
		KeyDealUnsignedFloat(Input,str_num,'3');
	}	
	else if(IsPushNumButton(NumButtonGroup[11],x,y))  //.
	{
		PrintString1(". is pressed\r\n");
		KeyDealUnsignedFloat(Input,str_num,'.');
	}
	else if(IsPushNumButton(NumButtonGroup[12],x,y))  //0
	{
		KeyDealUnsignedFloat(Input,str_num,'0');	
	}
	else if(IsPushNumButton(NumButtonGroup[13],x,y))  //X
	{
		KeyDealUnsignedFloat(Input,str_num,'X');	
	}
		
	else if(IsPushNumButton(NumButtonGroup[0],x,y))  //back
	{
		InputExecuteCancleCall(Input);
	}
			
	else if(IsPushNumButton(NumButtonGroup[1],x,y))  //ok
	{   
		InputExecuteOkCall(Input);	
	}
}





//========================================================================
// ����: KeyScanFloat()
// ����: ���ּ���ɨ�����2��ʵ���з�����������ɨ�裩
// ����:��������x,y,��������
// ����: ��
// �汾: V1.0, 2021-6-17
//========================================================================
void KeyScanFloat(struct InputType Input,u16 x,u16 y)
{
	if(IsPushNumButton(NumButtonGroup[2],x,y))  //7
	{
		PrintString1("7 is pressed\r\n"); 
		KeyDealFloat(Input,str_num,'7');  	
	}
		
	else if(IsPushNumButton(NumButtonGroup[3],x,y)) //8
	{
		PrintString1("8 is pressed\r\n"); 
		KeyDealFloat(Input,str_num,'8');	
	}
	else if(IsPushNumButton(NumButtonGroup[4],x,y)) //9
	{
		PrintString1("9 is pressed\r\n");	
		KeyDealFloat(Input,str_num,'9');	
	}
	
	else if(IsPushNumButton(NumButtonGroup[5],x,y)) //4
	{
		PrintString1("4 is pressed\r\n"); 
		KeyDealFloat(Input,str_num,'4');		
	}
	else if(IsPushNumButton(NumButtonGroup[6],x,y)) //5
	{
		PrintString1("5 is pressed\r\n");
		KeyDealFloat(Input,str_num,'5');
	}
	else if(IsPushNumButton(NumButtonGroup[7],x,y)) //6
	{
		PrintString1("6 is pressed\r\n");	
		KeyDealFloat(Input,str_num,'6');
	}
		
	else if(IsPushNumButton(NumButtonGroup[8],x,y))  //1
	{
		PrintString1("1 is pressed\r\n");	
		KeyDealFloat(Input,str_num,'1');	 	
	}
	else if(IsPushNumButton(NumButtonGroup[9],x,y))  //2
	{
		PrintString1("2 is pressed\r\n");  
		KeyDealFloat(Input,str_num,'2');	
	}
	else if(IsPushNumButton(NumButtonGroup[10],x,y))  //3
	{
		PrintString1("3 is pressed\r\n"); 	
		KeyDealFloat(Input,str_num,'3');
	}	
		
	else if(IsPushNumButton(NumButtonGroup[11],x,y))  //.
	{
		PrintString1(". is pressed\r\n");
		KeyDealFloat(Input,str_num,'.');
	}
	else if(IsPushNumButton(NumButtonGroup[12],x,y))  //0
	{
		PrintString1("0 is pressed\r\n");
		KeyDealFloat(Input,str_num,'0');	
	}
	else if(IsPushNumButton(NumButtonGroup[13],x,y))  //X
	{
		PrintString1("X is pressed\r\n");
		KeyDealFloat(Input,str_num,'X');	
	}
			
	else if(IsPushNumButton(NumButtonGroup[14],x,y))  //X
	{
		PrintString1("- is pressed\r\n");
		KeyDealFloat(Input,str_num,'-');	
	}
	
	else if(IsPushNumButton(NumButtonGroup[13],x,y))  //-
	{
		PrintString1("- is pressed\r\n");
		KeyDealFloat(Input,str_num,'-');	
	}
			
	else if(IsPushNumButton(NumButtonGroup[0],x,y))  //back
	{
		PrintString1("back is pressed\r\n"); 
		InputExecuteCancleCall(Input);
	}		
	else if(IsPushNumButton(NumButtonGroup[1],x,y))  //ok
	{   
		PrintString1("ok is pressed\r\n");
		InputExecuteOkCall(Input);
	}
}	





//========================================================================
// ����: StrToInt()
// ����: ���ַ���ת����Long Int
// ����:Ҫת�����ַ���,С����λ��  0����ʾInt�� 
// ����: ת�����ֵ
// �汾: V1.0, 2021-6-30
//========================================================================
long int StrToInt(u8 str[9],u8 Dotcount)                 //-2147483648~2147483647
{
	long int val=0;
	u8 End=FindEnd(str); //J2
	u8 Dot;
	u8 i=0;
	u32 wei=1;
	u8 Singed=0;
	if(End==0) 
	{
		return 0; 
	}
	if(str[0]=='-')//����
	{
		for(i=0;i<End;i++)
		{	
			str[i]=str[i+1];
		}
		Singed=1;
	}
	End=FindEnd(str); 
	Dot=FindDot(str); 	
	
	if(Dot!=0xFF)//�����ֵ
	{	
		if(Dot==0)
		{
			PrintString1("Υ������\r\n");	
			return 0;
		}
		while((End-Dot)!=(Dotcount+1))
			{
				str[End]='0';
				str[++End]=0;
			}
		for(i=(End-1);i>Dot;i--)//С����֮��
			{
				val+=(str[i]-48)*wei;
				wei=wei*10;
			}		
		for(i=(Dot-1);i>0;i--) //С����֮ǰ
			{
				 val+=(str[i]-48)*wei;
				 wei=wei*10;
			}
		val+=(str[0]-48)*wei;
	}
	else if(Dot==0xFF)//��С����
	{
		 if(Dotcount!=0)
		 {
			for(i=End;i<(End+Dotcount);i++)
			{
				str[i]='0';
			}
			str[i]=0; //������־
			End=i; //end ����
		 }
		 
		for(i=(End-1);i>0;i--)//С����֮��
		{
			val+=(str[i]-48)*wei;
			wei=wei*10;
		}
			val+=(str[0]-48)*wei;
	}
	if(Singed==0)
	{
		return val;	
	}
	else
	{	
		val=-val;
		return val;
	}
}





//========================================================================
// ����: InputExecuteOkCall
// ����: ʵ��Ok�ص�
//������Input����
//����ֵ����
// �汾: V1.0, 2021-06-30
//========================================================================	
void InputExecuteOkCall(struct InputType Input)
{
	 long int num;
	 int num1;
	 u8 *DatePointer;
	 u8 DataCount;
	 u8 str[4];
	 DatePointer=VaddrtoPaddrVar(Input.Addr);
	 DataCount=VaddrtoCountVar(Input.Addr);
	 if(DatePointer==NULL)
	 {
		  PrintString1("Invalid Input Addr\r\n");
		  return;
	 }
     num=StrToInt(str_num,Input.DataClass.DotCount);
	 if(DataCount==2)
	 {
		 DataCount--;
		 num1=(int)num;
		 while(DataCount>0)
		 {
			 DatePointer[DataCount]=num1&0x00FF;
			 num1=num1>>8;
			 DataCount--;
			 PrintString1(u8_to_str_3(DataCount,str));
			 PrintString1("\r\n");
		 }
		 DatePointer[0]=num1&0x00FF;
		 DatePointer[0]=DatePointer[0]|0x8000;
	 }
	 else if(DataCount=4)
	 {
		 DataCount--;
		 while(DataCount>0)
		 {
			 DatePointer[DataCount]=num&0x000000FF;
			 num=num>>8;
			 DataCount--;
			 PrintString1(u8_to_str_3(DataCount,str));
			 PrintString1("\r\n");
		 }
		 DatePointer[0]=num&0x000000FF;
	 }
	 DataCount=VaddrtoCountVar(Input.Addr);
	 Send_Mesg_var(Input.Addr,(DataCount/2));	 
	 InputOff(Input.Name);
}



//========================================================================
// ����: InputExecuteCancleCall
// ����: ʵ��Cancel�ص�
//����ֵ����
// �汾: V1.0, 2021-06-30
//========================================================================	
void InputExecuteCancleCall(struct InputType Input)
{	
	InputOff(Input.Name);
}


//========================================================================
// ����: IsPush_NumButton
// ����: ���ĳ����ť�Ƿ񱻰���
//����ֵ��1�����£�0��û����
// �汾: V1.0, 2021-06-5
//========================================================================	
u8 IsPush_NumButton(struct NumButtonType button,u16 x,u16 y)
{
	if(x>button.x&&x<(button.x+button.width)&&y>button.y&&y<(button.y+button.length))
	{
	 return 1;
	}
	else
	{
	 return 0;
	}
}



//========================================================================
// ����: InputOn
// ����: ��Input
//����ֵ����
// �汾: V1.0, 2021-06-30
//========================================================================
void InputOn(u8 InputName)
{
	u8 InputIndex;
	CurrentInput=InputName;
	CursorOn();
	ClearStrNum(str_num);
	for(InputIndex=0;InputIndex<InputCount;InputIndex++)
	{
		if(InputGroup[InputIndex].Name==InputName) break;
	}
	if(InputIndex==InputCount||InputIndex>InputCount)
	{
		PrintString1("Invalid Input to on\r\n");
		return;
	}
	
	JPG_NOR ( BINARY_INFO[InputGroup[InputIndex].PicIndex].start_addr,BINARY_INFO[InputGroup[InputIndex].PicIndex].img_size,canvas_image_width,0,0);
	JPG_NOR ( BINARY_INFO[InputGroup[InputIndex].PicIndex1].start_addr,BINARY_INFO[InputGroup[InputIndex].PicIndex1].img_size,canvas_image_width,0,272);
}




//========================================================================
// ����: InputOff
// ����: �ر�Ipunt
//����ֵ����
// �汾: V1.0, 2021-06-30
//========================================================================
void InputOff(u8 InputName)
{	
	u8 InputIndex;
	u8 PageIndex;
	CurrentInput=0xFF;
	CursorOff();
	for(InputIndex=0;InputIndex<InputCount;InputIndex++)
	{
		if(InputGroup[InputIndex].Name==InputName) break;
	}
	if(InputIndex==InputCount||InputIndex>InputCount)
	{
		PrintString1("Invalid Input to off\r\n");
		return;
	}
	
	for(PageIndex=0;PageIndex<PageCount;PageIndex++)
	{
		if(PageGroup[PageIndex].Name==InputGroup[InputIndex].PageName) break;
	}
	if(PageIndex==PageCount||PageIndex>PageCount)
	{
		PrintString1("Invalid Input to find a affilated Page\r\n");
		return;
	}
	JPG_NOR ( BINARY_INFO[PageGroup[PageIndex].PicIndex].start_addr,BINARY_INFO[PageGroup[PageIndex].PicIndex].img_size,canvas_image_width,0,0);
	JPG_NOR ( BINARY_INFO[PageGroup[PageIndex].PicIndex1].start_addr,BINARY_INFO[PageGroup[PageIndex].PicIndex1].img_size,canvas_image_width,0,272);
}




//========================================================================
// ����: IsPush_NumButton
// ����: ���ĳ����ť�Ƿ񱻰���
//����ֵ��1�����£�0��û����
// �汾: V1.0, 2021-06-5
//========================================================================	
u8 IsPushNumButton(struct NumButtonType button,u16 x,u16 y)
{
	if(x>button.x&&x<(button.x+button.width)&&y>button.y&&y<(button.y+button.length))
	{
	 return 1;
	}
	else
	{
	 return 0;
	}
}



//========================================
// ����: NumPressEffect()
// ����: ���ּ��̵İ���Ч��
// ����:����,x,y,��ǰ�༭����
// �汾: V1.0, 2021-6-7
//========================================
void NumButtonPressEffect(u16 x,u16 y)
{
	u8 Index;
	u16 xx,yy;
	u8 width,length;
	for(Index=0;Index<NumButtonCount;Index++)
	{
		if(IsPush_NumButton(NumButtonGroup[Index],x,y))
		{
			if(Index==14)
			{
				if((CurrentInput==Auto1EditAl1||CurrentInput==Auto1EditAl2||CurrentInput==Auto2EditAl1||CurrentInput==Auto2EditAl2)) break;
				else return;
			}
			else
			{
				break;
			}
		}			
	}
	if(Index==NumButtonCount||Index>NumButtonCount)
	{
		PrintString1("Invalid NumButton to do effect\r\n");
		return;
	}
	xx=NumButtonGroup[Index].x;
	yy=NumButtonGroup[Index].y;
	width=NumButtonGroup[Index].width;
	length=NumButtonGroup[Index].length;	
	BTE_Memory_Copy(0,canvas_image_width,xx,(272+yy),0,canvas_image_width,xx,(272+yy),0,canvas_image_width,xx,yy,12,width,length);	
}


//========================================================================
// ����: NumButtonReleaEffect()
// ����: ���л�ԭͼ�ķ�ʽʵ�����ְ������ͷ�
// ����:Ҫ�ͷŰ����ı༭����
// ����: ��
// �汾: V1.0, 2021-6-8
//========================================================================
void NumButtonReleaEffect(u8 InputName,u16 x,u16 y)
{
	u8 IpuntIndex;
	u8 ButtonIndex;
	u8 PicIndex;
	u16 xx,yy;
	u8 width,length;
	for(IpuntIndex=0;IpuntIndex<InputCount;IpuntIndex++)
	{
		if(InputGroup[IpuntIndex].Name==InputName) break;
	}
	if(IpuntIndex==InputCount||IpuntIndex>InputCount)
	{
		PrintString1("Invalid Input to release\r\n");
		return;
	}
	PicIndex=InputGroup[IpuntIndex].PicIndex;
	JPG_NOR (BINARY_INFO[PicIndex].start_addr,BINARY_INFO[PicIndex].img_size,canvas_image_width,480,0);//���ص���1

	
	for(ButtonIndex=0;ButtonIndex<NumButtonCount;ButtonIndex++)
	{
		if(IsPush_NumButton(NumButtonGroup[ButtonIndex],x,y)) break;
	}
	if(ButtonIndex==NumButtonCount||ButtonIndex>NumButtonCount)
	{
		PrintString1("Invalid NumButton to release\r\n");
		return;
	}
	xx=NumButtonGroup[ButtonIndex].x;
	yy=NumButtonGroup[ButtonIndex].y;
	width=NumButtonGroup[ButtonIndex].width;
	length=NumButtonGroup[ButtonIndex].length;	
	BTE_Memory_Copy(0,canvas_image_width,(xx+480),yy,0,canvas_image_width,(xx+480),yy,0,canvas_image_width,xx,yy,12,width,length);	
}



//========================================================================
// ����: NumButtonCall()
// ����:���ּ��̵Ļص�����
// ����:��ǰ����,x,y
// �汾: V1.0, 2021-6-8
//========================================================================
void NumButtonCall(u8 InputName,u16 x,u16 y)
{
	u8 InputIndex;
	for(InputIndex=0;InputIndex<InputCount;InputIndex++)
	{
		if(InputGroup[InputIndex].Name==InputName) break;
	}
	if(InputIndex==InputCount||InputIndex>InputCount)
	{
		PrintString1("Invalid Input to do button call\r\n");
		return;
	}
	
	
	switch(InputGroup[InputIndex].DataClass.Type)
	{
		case UnsingedInt:
		{
			KeyScanUnsingedInt(InputGroup[InputIndex],x,y);
			break;
		}
	
		case UnsingedFloat:
		{
			KeyScanUnsingedFloat(InputGroup[InputIndex],x,y);
			break;
		}
		
		case Float:
		{
			KeyScanFloat(InputGroup[InputIndex],x,y);			
			break;
		}
	}
}



//============================================
// ����: InputStrFlush
// ����: �����ּ��̱༭���ַ�������ˢ��
// ����: ��
// �汾: V1.0, 2021-6-30
//============================================
void InputStrFlush()
{
	
	Select_Font_Height_WxN_HxN_ChromaKey_Alignment(24,1,1,0,0);
	Cursorx=20+12*(FindEnd(str_num));//�������
	Cursory=80;
	BTE_Solid_Fill(0,canvas_image_width,480+20,272+80,0x000000,120,24);
	FlushCursor(Cursorx,Cursory);
	Print_GB2312String(3,0,0,480+20,272+80,250,24,0xffffff,0x000000, str_num);
	BTE_Memory_Copy(0,canvas_image_width,480+20,(272+80),0,canvas_image_width,480+60,(272+80),0,canvas_image_width,20,80,12,120,24);	
}





//============================================
// ����: FlushCursor()
// ����: ʵ�ֹ����˸
// ����: ��
// �汾: V1.0, 2021-6-30
//============================================
void FlushCursor(u16 x,u16 y)  
{   Select_Font_Height_WxN_HxN_ChromaKey_Alignment(24,1,1,0,0);
	if(CursorRever==0)
	{
		Print_GB2312String(3,0,0,480+x,272+y,37,32,0xffffff,0x000000, "|");
	}
else
	{ 	
		Print_GB2312String(3,0,0,480+x,272+y,37,32,0xffffff,0x000000, " ");
	}	
}


void CursorOn()
{
	CursorFluTimer.swit=1;
}

void CursorOff()
{
	CursorFluTimer.swit=0;
}





































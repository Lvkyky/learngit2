#include <config.h>
#include <gpio.h>
#include "delay.h"
#include  <spi.h>
#include  <USART.h>



void SPI3_Init(void)//������ͬʱ����
{
	
GPIO_InitTypeDef  IOP05;                 //scl
GPIO_InitTypeDef  IOP06;                // da
GPIO_InitTypeDef  IOP07;                // cs
GPIO_InitTypeDef  IOP40;                //reset
  
IOP05.	Pin=GPIO_Pin_2;
IOP05.	Mode=GPIO_OUT_PP;

IOP06.	Pin=GPIO_Pin_3;	
IOP06.	Mode=GPIO_OUT_PP;
	
IOP07.	Pin=GPIO_Pin_5;
IOP07.	Mode=GPIO_OUT_PP;   //��ʼ��ʱ�������⣬�ȵ�Ҫ��������ʱ��������IOp2��
	
IOP40.	Pin=GPIO_Pin_0;
IOP40.	Mode=GPIO_OUT_PP;   // //����p40Ϊ�����������
	

GPIO_Inilize(GPIO_P0,&IOP05);	
GPIO_Inilize(GPIO_P0,&IOP06);	
GPIO_Inilize(GPIO_P0,&IOP07);	                  
GPIO_Inilize(GPIO_P4,&IOP40);	

	
Set_SPI3_SCL;  
Set_SPI3_SDO; 
Set_SPI3_ZCS;  //���ڿ���̬
}




void SPI3_Write(unsigned char dat)//spiд8λ���ݵ�ʱ��ģ��
{
	unsigned char t = 8;

	do
	{
	  if  ((dat & 0x80)==0x80) //�����������ź�
		{
	    Set_SPI3_SDO;		   
		}
		else
	  {
		  Reset_SPI3_SDO;	
		}

		dat <<= 1;//׼����һλ����
		
		Reset_SPI3_SCL;// ʱ������
		Set_SPI3_SCL;//	  ʱ�������������д��  
	}while(--t !=0);
	
	Set_SPI3_SCL;		   
	Set_SPI3_SDO;// �ٴν��ź������ڿ���̬
}





void  delay_spi(void)
{
	short int i;
	i = 2;
	while(--i)	;   //14T per loop 
}


unsigned char SPI3_Read()//spi��8λʱ��ģ��
{
	unsigned char temp =0;
	unsigned char dat=0;//��ȡ����
	unsigned char t = 8;//Ҫ�����ַ�����

	do
	{
		Reset_SPI3_SCL;//����ʱ��
		//SPI3_Delay();
		delay_spi();

		temp=Read_SPI3_SDO;//��ȡ����
		dat <<= 1;
		delay_spi();//SPI3_Delay();
		if(temp==0x01)
		{
	    dat++;
	  }
	  Set_SPI3_SCL;//����ʱ��
		  
	}while(--t !=0 );

	return dat;
}





void LCD_CmdWrite(unsigned char Command)//д�����
{	
	unsigned char cmd=Command;
	Set_SPI3_SCL;//			   //SCL ʱ����Ϊ����̬
	Set_SPI3_SDO;			   //SDO   ��������Ϊ����
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			       //ZCS            //ƬѡҺ������оƬ
	SPI3_Write(0x00); //���͵�һ�ֽڣ�д�����
	SPI3_Write(cmd);  //���͵ڶ��ֽ�
	Set_SPI3_ZCS;//GPIO_SetBits(GPIOE, GPIO_Pin_7);			       //ZCS	             //�ͷ�Һ������оƬ
}




unsigned char LCD_DataRead(void)  //�����ݺ���
{	     
  unsigned int Data;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				  
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				       
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			      
	SPI3_Write(0xc0);//������Ϊ����̬�����ҷ��͵�һ�ֽڣ����������


	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);     //��д1;
	

	GPIO_InitStructure.Mode= GPIO_HighZ ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //������
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	 //���óɸ�������

	
	
	Data = SPI3_Read();                //������


  GPIO_InitStructure.Mode= GPIO_OUT_PP ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //������
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //���ó��������
	
	
	Set_SPI3_ZCS;      //GPIO_SetBits(GPIOE, GPIO_Pin_7);	    �ͷ�оƬ
                                                  

	return Data;
}





void LCD_DataWrite(unsigned char Data) //д���ݺ���
{   
  unsigned int writedata;

	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				   
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				  
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);			 //spi���ڿ���̬������Ƭѡ��оƬ��   

	SPI3_Write(0x80); 
	SPI3_Write(Data);
	Set_SPI3_ZCS;//	GPIO_SetBits(GPIOE, GPIO_Pin_7);			 	 //�ͷ�оƬ
}




unsigned char LCD_StatusRead(void)						
{
	unsigned char Data=0;
  GPIO_InitTypeDef GPIO_InitStructure;

	Set_SPI3_SCL;//GPIO_SetBits(GPIOE, GPIO_Pin_10);				
	Set_SPI3_SDO;//GPIO_SetBits(GPIOE, GPIO_Pin_8);				 
	Reset_SPI3_ZCS;//GPIO_ResetBits(GPIOE, GPIO_Pin_7);		  //ѡ��оƬ	 

	
	SPI3_Write(0x40);        //������Ϊ����̬�����ҷ��͵�һ�ֽڣ���״̬���
	
	
	/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8  ;
															 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	  
	Data = SPI3_Read();

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //�������
	GPIO_Init(GPIOE, &GPIO_InitStructure);
*/


	GPIO_InitStructure.Mode=GPIO_HighZ ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //������
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //���óɸ�������
	
	
 
	Data = SPI3_Read();                //������

	
  GPIO_InitStructure.Mode= GPIO_OUT_PP ;
	GPIO_InitStructure.Pin=GPIO_Pin_6;     //������
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	     //���ó��������


	Set_SPI3_ZCS;	//GPIO_SetBits(GPIOE, GPIO_Pin_7);			      //�ͷ�оƬ  	.
	
	return Data;
}






#ifndef		__INPUT_H
#define		__INPUT_H
#include "STC15Fxxxx.H"

#define InputCount 25
#define NumButtonCount 15

struct DataType 
{
	u8 Type;
	u8 IntCount; 
	u8 DotCount; 
};
	
struct InputType 
{
	u8  PageName;
	u8  Name;
	u8  PicIndex;
	u8  PicIndex1;
	struct DataType DataClass;
	u16 Addr;
};

struct NumButtonType//���ֱ༭��ť
{ 	u8 Name;
	u16 x;
	u16 y;
	u8 width;
	u8 length;
};

enum InputDataType{UnsingedInt=0x00,UnsingedFloat,Float,Int};
enum InputButton{EditBack=0x00,EditOk,Edit7,Edit8,Edit9,Edit4,Edit5,Edit6,
Edit1,Edit2,Edit3,EditDian,Edit0,EditX,EditSined};

enum Input{
///////////Main����///////////////	
MainEditt1=0x00,MainEditt2,MainEditt3,MainEditt4,
///////////Move����///////////////	
MoveEditx,MoveEdity,MoveEditz,MoveEdite,
///////////AutoLevel����/////////
Auto1EditAl1,Auto1EditAl2,
///////////AutoLeve2����/////////
Auto2EditAl1,Auto2EditAl2,
///////////Preheat����////////////
PreheatEditP1,PreheatEditP2,PreheatEditP3,
////////////Fans����////////////
FansEditF1,FansEditF2,FansEditF3,
////////Print����////////////	
PrintEditt1,PrintEditt2,PrintEditt3,PrintEditt4,
////////Adjust����////////////
AdjustEditAd1,AdjustEditAd2,AdjustEditAd3
};


extern u8 CurrentInput;
extern u8 CursorRever;
extern u8 Cursorx;
extern u8 Cursory;//���



void InputOn(u8 InputName);
void InputOff(u8 InputName);
void InputExecuteOkCall(struct InputType Input);
void InputExecuteCancleCall(struct InputType Input);
void NumButtonPressEffect(u16 x,u16 y);
void NumButtonReleaEffect(u8 InputName,u16 x,u16 y);
void NumButtonCall(u8 InputName,u16 x,u16 y);
u8 IsPushNumButton(struct NumButtonType button,u16 x,u16 y);


void KeyScanFloat(struct InputType Input,u16 x,u16 y);
void KeyScanUnsingedInt(struct InputType Input,u16 x,u16 y);
void KeyScanUnsingedFloat(struct InputType Input,u16 x,u16 y);


void InputStrFlush();
void FlushCursor(u16 x,u16 y);
void CursorOn();
void CursorOff();

void ClearStrNum(u8 str[9]);
u8 FindDot(u8 str[9]);
u8 FindEnd(u8 str[9]);
u8 FindSing(u8 str[9]);
void KeyDealUnsignedFloat(struct InputType Input,u8 str[9],u8 inser);
void KeyDealFloat(struct InputType Input,u8 str[9],u8 inser);
void KeyDealUnsignedInt(u8 str[9],u8 inser);
long int StrToInt(u8 str[9],u8 Dotcount);
#endif
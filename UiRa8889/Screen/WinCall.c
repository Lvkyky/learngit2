#include "WinCall.h"
#include "Win.h"
const struct WinOkCall code WinOkCallGroup[WinOkCallCount]={
{Aoutolevel1SelectCalibrate,SkipCall},  
{SettingSelectFact,SelectFacOkCall},
///////////////////Print����////////////////////////
{PrintSelectCancelPrint,PrintSelectCancelPrintOkCall},             
{PrintPauseChangeDone,ChangeDoneOkCall}
};



const struct WinCanCall code WinCanCallGroup[WinCanCallCount]={

{Aoutolevel1SelectCalibrate,AgainCall},  
{SettingSelectFact,SelectFacCanCall},
//////////////////////Print����///////////////////
{PrintSelectCancelPrint,PrintSelectCancelPrintCanCall}
};






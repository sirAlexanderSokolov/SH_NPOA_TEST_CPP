//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
this->Left=Form1->Left+20;
this->Top=Form1->Top+35;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if (Shift.Contains(ssLeft)==true)
{
ReleaseCapture();
SendMessage(this->Handle,WM_NCLBUTTONDOWN,HTCAPTION,0);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
Form1->mode=0;
Form1->protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton2Click(TObject *Sender)
{
Form1->mode=1;
Form1->protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton3Click(TObject *Sender)
{
Form1->mode=2;
Form1->protect=true;
}
//---------------------------------------------------------------------------

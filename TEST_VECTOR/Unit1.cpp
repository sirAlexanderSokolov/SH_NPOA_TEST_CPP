//---------------------------------------------------------------------------
#define PRIM1 canv1->PMap
#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//-------NPrim
class NPrim {//����� ���������
public:
int type; //��� ���������
	//0 - �������������
	//1 - ����������
	//2 - �����
TColor bcolor; //������� ���� �������
int p_x, p_y, p_w, p_h; //���������� ��������� �, �, ������ � ������ �������������� � ������� ������ ��������
};
//-------NPrim

int p_count=1; //����� ����� ���������� �� �������
map<int, NPrim*> PMap; //��������� ��� �������� � ��������� � ���������� ����: ������ - ��������
int mode=100; //����������� ��������� �����
int p_cur=-1; //��������� ������������� ��� ������ ��������
bool protect=false; //����� �� ��������� ������� ��� ������� ���

void PDraw()
{
for (int i = 0; i < PMap.size(); i++)
	{
	Form1->Canvas->Brush->Color=PMap[i]->bcolor;
		switch (PMap[i]->type)
		{
		case 0: Form1->Canvas->Rectangle(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;
		case 1: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;
		case 2: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+1),(PMap[i]->p_y+1));
		break;
		default:;
		}
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
Form1->DoubleBuffered=true;
PMap[0]=new NPrim;
PMap[0]->type=0;
PMap[0]->bcolor=clWhite;
PMap[0]->p_x=0;
PMap[0]->p_y=0;
PMap[0]->p_w=Form1->Width;
PMap[0]->p_h=Form1->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
PDraw();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
for (unsigned int j = 0; j<PMap.size(); j++) delete PMap[j];
PMap.clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
mode = 0;
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
mode = 1;
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
mode = 3;
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&&(protect==true)) //���� ������� ����� ���������
	{
	p_cur=p_count;
	PMap[p_cur]=new NPrim;
	PMap[p_cur]->type=0;
	PMap[p_cur]->bcolor=clWhite;
	PMap[p_cur]->p_x=X;
	PMap[p_cur]->p_y=Y;
	PMap[p_cur]->p_w=0;
	PMap[p_cur]->p_h=0;
	p_count++;
	protect=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //����� ���������
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //���� ������� ����� ���������
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	p_cur=-1;
	mode=100;
	protect=true;
	}
}
//---------------------------------------------------------------------------


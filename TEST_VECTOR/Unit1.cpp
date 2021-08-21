//---------------------------------------------------------------------------
#define PRIM1 canv1->PMap
#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//������� ��������
//��������� ������� ������� ���������
//�����������

TForm1 *Form1;

//-------NPrim
class NPrim {//����� ���������
public:
int type; //��� ���������
	//0 - �������������
	//1 - ����������
	//2 - �����
//����� ������� bool enabled
TColor bcolor, pcolor; //������� ���� �������
int p_x, p_y, p_w, p_h; //���������� ��������� �, �, ������ � ������ �������������� � ������� ������ ��������
};
//-------NPrim

int p_count=2; //����� ����� ���������� �� �������
map<int, NPrim*> PMap; //��������� ��� �������� � ��������� � ���������� ����: ������ - ��������
int mode=100; //����������� ��������� �����
int p_cur=-1; //��������� ������������� ��� ������ ��������
bool protect=false; //����� �� ��������� ������� ��� ������� ���
int dragstate=0; //��������� ��������������

void PDraw()  //������� ��������� ����������
{
for (int i = 0; i < PMap.size(); i++)
	{
	Form1->Canvas->Brush->Color=PMap[i]->bcolor;
	Form1->Canvas->Pen->Color=PMap[i]->pcolor;;
		switch (PMap[i]->type)
		{
		case 0: Form1->Canvas->Rectangle(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;
		case 1: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;
		case 2: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+4),(PMap[i]->p_y+4));
		break;
		default:;
		}
	}
}

int PickP(int x, int y) //��������� ��������� �� ������ ��� �������������� - ����� ��� �������
	{
	for(int i=PMap.size()-1; i>=1;i--) //����� �������������� - ������� � ������� �����
		{
		if (i==1) return -1;
		else if ((x>=PMap[i]->p_x) && (x<=PMap[i]->p_x+PMap[i]->p_w) &&	(y>=PMap[i]->p_y) && (y<=PMap[i]->p_y+PMap[i]->p_h))return i;
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

PMap[0]=new NPrim;      //�����
PMap[0]->type=0;
PMap[0]->bcolor=clWhite;
PMap[0]->pcolor=clBlack;
PMap[0]->p_x=0;
PMap[0]->p_y=0;
PMap[0]->p_w=Form1->Width;
PMap[0]->p_h=Form1->Height;

PMap[1]=new NPrim;     //������� ��� ��������������
PMap[1]->type=0;
PMap[1]->bcolor=clWhite;
PMap[1]->pcolor=clBlue;
PMap[1]->p_x=0;
PMap[1]->p_y=0;
PMap[1]->p_w=0;
PMap[1]->p_h=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
PDraw();  //������������ �����
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
for (unsigned int i = 0; i<PMap.size(); i++) delete PMap[i];
PMap.clear();             //������� ������
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
mode = 0;     //�������������
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
mode = 1;    //������
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
mode = 2;    // �����
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&&(protect==true)) //���� ������� ����� ���������
	{
	p_cur=p_count;
	PMap[p_cur]=new NPrim;   //������� ����� ��������
	PMap[p_cur]->type=mode;
	PMap[p_cur]->bcolor=clWhite;
	PMap[p_cur]->pcolor=clBlack;
	PMap[p_cur]->p_x=X;
	PMap[p_cur]->p_y=Y;
	PMap[p_cur]->p_w=0;
	PMap[p_cur]->p_h=0;
	p_count++;
	protect=false;
	}
else
{
switch (mode) //������������ ��� ���������� ���������
	{
	case 100: //���� ������������ ������� � "������" ������
		{
		if (PickP(X,Y) >= 2) // ���� ������������ ������ ������ ��� ��������������
			{
			p_cur=PickP(X,Y);
			PMap[1]->p_x=PMap[p_cur]->p_x-5;
			PMap[1]->p_y=PMap[p_cur]->p_y-5;
			PMap[1]->p_w=PMap[p_cur]->p_w+10;
			PMap[1]->p_h=PMap[p_cur]->p_h+10;    //������������ �������� ��������������
			PDraw();
			mode=101; //�������� ����� ��������� �������� ��������������
			}
		}
		break;
	case 101: //���� ������������ ������� � ������ ��������� �������� ��������������
		{
		if (dragstate==1)dragstate=2;
		else mode = 100;
		}
        break;
	}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //����� ���������
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;       //������������ �������� ��������
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	}
else
{
switch (mode) //������������ ��� ���������� ���������
	{
	case 100: //���� ������������ ������� � "������" ������
		{
		}
		break;
	case 101: //���� ������������ ������� � ������ ��������� �������� ��������������
		{
	if ((dragstate==0)||(dragstate==1))
		{
		if (((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y)) || ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h)))
		{   //����� �������������� �����  (������ ������)
		Form1->Cursor=-7;
		dragstate=1;  //����� ����������
		}
		else if (((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x)) || ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w)))
		{  //����� ������������ ����� (������ ������)
		Form1->Cursor=-9;
		dragstate=1;
		}
		else
		{
		Form1->Cursor=0; //���� �� ������ ����� - ��������� ������
		dragstate=0;
		}
	}
	else if (dragstate==2)      //!!!���
		{
		PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
		PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
		if (PMap[p_cur]->p_w>0)
			{
			PMap[1]->p_x=PMap[p_cur]->p_x-5;
			PMap[1]->p_w=PMap[p_cur]->p_w+10;
			}
		else
			{
			PMap[1]->p_x=PMap[p_cur]->p_x+5;
			PMap[1]->p_w=PMap[p_cur]->p_w-10;
			}
		if (PMap[p_cur]->p_h>0)
			{
			PMap[1]->p_y=PMap[p_cur]->p_y-5;
			PMap[1]->p_h=PMap[p_cur]->p_h+10;
			}
		else
			{
			PMap[1]->p_y=PMap[p_cur]->p_y+5;
			PMap[1]->p_h=PMap[p_cur]->p_h-10;
			}
		PDraw();
		}
	break;
	default:;
		}
	}
}
Memo1->Clear();
Memo1->Lines->Add("mode  " + IntToStr(mode));
Memo1->Lines->Add("p_cur  " + IntToStr(p_cur));
Memo1->Lines->Add("drags  " + IntToStr(dragstate));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //���� ������� ����� ���������
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;   //����������� �������� ��������
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	p_cur=-1;
	mode=100;
	protect=true;
	}
else
{
switch (mode) //������������ ��� ���������� ���������
{
	case 100: //���� ������������ ������� � "������" ������
		{
        PMap[1]->p_x=0;
		PMap[1]->p_y=0;
		PMap[1]->p_w=0;
		PMap[1]->p_h=0;
		p_cur=-1;
		mode=100;
		PDraw();
		Form1->Cursor=0;
		dragstate=0;
		}
		break;
	case 101: //���� ������������ ������� � ������ ��������� �������� ��������������
	{
        if (dragstate==2)
		{
		PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
		PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
		if (PMap[p_cur]->p_w>0)
			{
			PMap[1]->p_x=PMap[p_cur]->p_x-5;
			PMap[1]->p_w=PMap[p_cur]->p_w+10;
			}
		else
			{
			PMap[1]->p_x=PMap[p_cur]->p_x+5;
			PMap[1]->p_w=PMap[p_cur]->p_w-10;
			}
		if (PMap[p_cur]->p_h>0)
			{
			PMap[1]->p_y=PMap[p_cur]->p_y-5;
			PMap[1]->p_h=PMap[p_cur]->p_h+10;
			}
		else
			{
			PMap[1]->p_y=PMap[p_cur]->p_y+5;
			PMap[1]->p_h=PMap[p_cur]->p_h-10;
			}
		PMap[1]->p_x=0;
		PMap[1]->p_y=0;
		PMap[1]->p_w=0;
		PMap[1]->p_h=0;
		p_cur=-1;
		mode=100;
		PDraw();
		Form1->Cursor=0;
		dragstate=0;
		}
	}
}
}
}
//---------------------------------------------------------------------------


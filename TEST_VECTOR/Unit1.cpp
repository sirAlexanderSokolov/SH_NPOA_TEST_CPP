//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//������� ��������
//��������� ������� ������� ���������
//���� ������ ������ ������ ����� �����

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
int dragstate=0; //��������� ��������������m
int tmp_X=0; //���������� ��� ����������� ��������
int tmp_Y=0;
//---------------------------------------------------------------------------
void PDraw()  //������� ��������� ����������
{
for (int i = 0; i < PMap.size(); i++)
	{
	Form1->Canvas->Brush->Color=PMap[i]->bcolor;
	Form1->Canvas->Pen->Color=PMap[i]->pcolor;;
		switch (PMap[i]->type)
		{
		case 0: Form1->Canvas->Rectangle(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;//�������
		case 1: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;  //������
		case 2:
			{   //���
			Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+4),(PMap[i]->p_y+4));
			PMap[i]->p_w=4;
            PMap[i]->p_h=4;
			}
		break;
		default:;
		}
	}
}
//---------------------------------------------------------------------------
int PickP(int x, int y)//��������� ��������� �� ������ ��� �������������� - ����� ��� �������
	{
	for(int i=PMap.size()-1; i>=1;i--) //����� �������������� - ������� � ������� �����
		{
		if (i==1) return -1;
		else if ((x>=PMap[i]->p_x) && (x<=PMap[i]->p_x+PMap[i]->p_w) &&	(y>=PMap[i]->p_y) && (y<=PMap[i]->p_y+PMap[i]->p_h))return i;
		}
	}
//---------------------------------------------------------------------------
void BSet(bool Default)  //���������� ���������� �����
{
if (Default==true)
{
	PMap[1]->p_x=0;
	PMap[1]->p_y=0;
	PMap[1]->p_w=0;
	PMap[1]->p_h=0;
}
else
{
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
Form1->DoubleBuffered=true;   //����������� �������

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
BSet(true);   //��������� ��������� ����� �������������� �������
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
			BSet(false);  //������������ �������� ��������������
			PDraw();      //---/---
			mode=101; //�������� ����� ��������� �������� ��������������
			}
		}
		break;
	case 101: //���� ������������ ������� � ������ ��������� �������� ��������������
		{
		if (dragstate==1)    //���� ������ �� �������� ��������������
		{
		if ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y))
			{  //�����-����
			dragstate=2;  //����� ���������� � ������ ���
			}
		else if ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h))
			{  //�����-���
			dragstate=3;  //����� ���������� � ������ ���
			}
		else if ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w))
			{  //����-�����
			dragstate=4;  //����� ���������� � ������ ���
			}
		else if ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x))
			{  //����-����
			dragstate=5;  //����� ���������� � ������ ���
			}
		else if ((X > ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x-10)))
		&& (X < ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x+10)))
		&& (Y > ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y-10)))
		&& (Y < ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y+10))))
			{
			dragstate=6;  //����� ���������� � ������ ���
			tmp_X=X;
			tmp_Y=Y;
			}
		}
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
	break;
	case 101: //���� ������������ ����� ���� � ������ ��������� �������� ��������������
	{
	switch (dragstate)
	{
	case 0: case 1:  //���� ���� �������� �� ������� ��������������
	{
	if (((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y))
	   || ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h)))
		{   //������ �� �������������� �����
		Form1->Cursor=-15; //������ ������
		dragstate=1;  //��������� ����������
		}
	else if (((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x))
	   || ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w)))
		{  //������ �� ������������ �����
		Form1->Cursor=-14; //������ ������
		dragstate=1;   //��������� ����������
		}
	else if ((X > ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x-10)))
		&& (X < ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x+10)))
		&& (Y > ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y-10)))
		&& (Y < ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y+10))))
		{      //�����������
		Form1->Cursor=-22;  //������ ������
		dragstate=1;   //��������� ����������
		}
	else
		{
		Form1->Cursor=0; //���� �� ������ ����� - ��������� ������
		dragstate=0;  //������ ����������
		}
	}
	break;
    case 2:
		{      //����� �����
		PMap[p_cur]->p_h=(PMap[p_cur]->p_h-(Y-PMap[p_cur]->p_y));
		PMap[p_cur]->p_y=Y;
		BSet(false);
		PDraw();
		}
	break;
	case 3:    //����
		{
		PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
		BSet(false);
		PDraw();
		}
	break;
	case 4:    //������
		{
		PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
		BSet(false);
		PDraw();
		}
	break;
	case 5:   //�����
		{
		PMap[p_cur]->p_w=(PMap[p_cur]->p_w-(X-PMap[p_cur]->p_x));
		PMap[p_cur]->p_x=X;
		BSet(false);
		PDraw();
		}
	break;
	case 6:   //����������
		{
		PMap[p_cur]->p_x+=X-tmp_X;
		PMap[p_cur]->p_y+=Y-tmp_Y;
		tmp_X=X;
		tmp_Y=Y;
		BSet(false);
		PDraw();
		}
	break;
	default:;
	}
	break;
	default:;
	}
	}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //���� ������� ����� ���������
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;   //����������� �������� ��������
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	protect=true;
    p_cur=-1;
	mode=100;
	}
else if (((dragstate>=2)&&(mode==101))||(mode==100))
{
BSet(true);
dragstate=0;
Form1->Cursor=0;
p_cur=-1;
mode=100;
}
PDraw();
}
//---------------------------------------------------------------------------


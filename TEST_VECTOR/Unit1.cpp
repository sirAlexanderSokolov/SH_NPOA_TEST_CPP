//---------------------------------------------------------------------------
#define PRIM1 canv1->PMap
#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

template <class T> void paint(T *Prim_cl)
	{
		Form1->Canvas->Brush->Color=Prim_cl->bcolor;
		switch (Prim_cl->type)
			{
			case 0:
			{
			Form1->Canvas->Rectangle(Prim_cl->p_x,Prim_cl->p_y,(Prim_cl->p_x+Prim_cl->p_w),(Prim_cl->p_y+Prim_cl->p_h));
			//Form1->Canvas->Rectangle(Prim_cl->p_x,Prim_cl->p_y,Prim_cl->p_w,Prim_cl->p_h);
			break;  }
			case 1: Form1->Canvas->Ellipse(Prim_cl->p_x,Prim_cl->p_y,(Prim_cl->p_x+Prim_cl->p_w),(Prim_cl->p_y+Prim_cl->p_h));
			break;
			case 2: Form1->Canvas->Ellipse(Prim_cl->p_x,Prim_cl->p_y,(Prim_cl->p_x+1),(Prim_cl->p_y+1));
			break;
		default:
			;
			}
	}
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

void paintXX(NPrim Prim_cl)
	{
		Form1->Canvas->Brush->Color=Prim_cl.bcolor;
		switch (Prim_cl.type)
			{
			case 0:
			{
			Form1->Canvas->Rectangle(Prim_cl.p_x,Prim_cl.p_y,(Prim_cl.p_x+Prim_cl.p_w),(Prim_cl.p_y+Prim_cl.p_h));

			Form1->Memo1->Lines->Add(Prim_cl.p_x);
			Form1->Memo1->Lines->Add(Prim_cl.p_y);
			Form1->Memo1->Lines->Add(Prim_cl.p_x+Prim_cl.p_w);
			Form1->Memo1->Lines->Add(Prim_cl.p_y+Prim_cl.p_h);

			break;  }
			case 1: Form1->Canvas->Ellipse(Prim_cl.p_x,Prim_cl.p_y,(Prim_cl.p_x+Prim_cl.p_w),(Prim_cl.p_y+Prim_cl.p_h));
			break;
			case 2: Form1->Canvas->Ellipse(Prim_cl.p_x,Prim_cl.p_y,(Prim_cl.p_x+1),(Prim_cl.p_y+1));
			break;
		default:
			;
			}
	}

//-------NCanvas
//����� ������
//������ ������ �� ��������-���������� ������������ �� ���
class NCanvas : public NPrim {
public:

	int p_count; //����� ����� ���������� �� �������
	map<int, NPrim> PMap; //��������� ��� �������� � ��������� � ���������� ����: ������ - ��������

NCanvas()
	{
	this->p_x=0;
	this->p_y=0;
	this->p_w=Form1->Width;
	this->p_h=Form1->Height;
	this->type=0;
	this->bcolor = clWhite;
	paint(this); //�������������� = ������� �����

	this->p_count = 0;
	}
~NCanvas()
	{
	//for (int i=0; i<PMap.size(); i++) delete PMap[i]; //������� ���������, ����������� ������
	//PMap.clear;
	}
void Draw_Pic()
	{
	//paint(this); //�������������� = ������� �����
   //	for (int i=0; i<(PMap.size()-1); i++) paintXX(PMap[i]); //�������������� �������
	for (int i=0; i<(PMap.size()-1); i++) paint(&PMap[i]); //�������������� �������
	};
int PickP(int x, int y) //��������� ��������� �� ������ ��� �������������� - ����� ��� �������
	{
	for(int i=PMap.size(); i>=0;) //����� �������������� - ������� � ������� �����
		{
		if (i<0) return -1;
		else if ((x>=PMap[i].p_x)&&(x<=PMap[i].p_x+PMap[i].p_w)&&(y>=PMap[i].p_y)&&(y<=PMap[i].p_y+PMap[i].p_h)) return i;
		else i--;
		}
	}
};
//-------NCanvas

const clr=9; //kolichestvo knopok
TShape *Shape[clr];

NCanvas *canv1; //�������� ������ ��� �����
NPrim *prim1; //�������� ������ ��� ���������  */

int mode=100; //����������� ��������� �����
int pcur=-1; //��������� ������������� ��� ������ ��������

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

Form1->Color=clGray;

for (int i=0;i<clr;i++)  //������� �������
	{
	 Shape[i] = new TShape(this);
	 Shape[i]->Parent=Form1->Panel1;
	 Shape[i]->Width=18;
	 Shape[i]->Height=18;
	 Shape[i]->Left=65;
	 Shape[i]->Top=(i+1)*23;
	 Shape[i]->OnMouseDown=Shape1->OnMouseDown;
	}
Shape[0]->Brush->Color=clWhite;
Shape[1]->Brush->Color=clBlack;
Shape[2]->Brush->Color=clRed;
Shape[3]->Brush->Color=clGreen;
Shape[4]->Brush->Color=clBlue;
Shape[5]->Brush->Color=clYellow;
Shape[6]->Brush->Color=clFuchsia;
Shape[7]->Brush->Color=clGray;
Shape[8]->Brush->Color=clAqua;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
Form1->DoubleBuffered=true;
canv1 = new NCanvas;
canv1->Draw_Pic();
Label1->Caption=canv1->PMap.size();
test=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
delete canv1;
for (int i=0;i<clr;i++)delete Shape[i];
}
//---------------------------------------------------------------------------
void PalColorPick(TObject *Sender)
{
Form1->Shape1->Brush->Color=((TShape*)Sender)->Brush->Color;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
mode = 0;
test=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
mode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
mode = 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{          /*
if ((mode >= 0)	&& (mode <100)) //���� ������� ����� ���������
{
			prim1 = new NPrim; //������� ��������-������
			pcur = canv1->p_count; //����� ������ ����� ������� ��� �������
			PRIM1[pcur].type=mode; //���������� ��� ����� ��������
			PRIM1[pcur]=*prim1; //���������� �������� � ���������
			PRIM1[pcur].p_x=X; //���������� ������
			PRIM1[pcur].p_y=Y;
			PRIM1[pcur].bcolor=Form1->Shape1->Brush->Color; //�������
			Label1->Caption=canv1->PMap.size();

}   */
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{    /*
if ((mode >= 0)	&& (mode <100)) //����� ���������
{
	PRIM1[pcur].p_w=PRIM1[pcur].p_x+X; //�������� ��������� �������
	PRIM1[pcur].p_h=PRIM1[pcur].p_y+Y;
	canv1->Draw_Pic();	//�������������� �����
}    */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{   /*
if ((mode >= 0)	&& (mode <100)) //����� ���������
{
	Form1->Image1MouseMove((TImage *)Sender, Shift, PRIM1[pcur].p_x, PRIM1[pcur].p_y);
	canv1->Draw_Pic();
	canv1->p_count++;
	pcur=-1;
	mode=100;
} */
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
if ((mode >= 0)	&& (mode <100)&& (test==false)) //����� ���������
{
	PRIM1[pcur].p_w=X-PRIM1[pcur].p_x; //�������� ��������� �������
	PRIM1[pcur].p_h=Y-PRIM1[pcur].p_y;
	canv1->Draw_Pic();	//�������������� �����
		   /*	Memo1->Clear();
			Memo1->Lines->Add(canv1->PMap.size());
			Memo1->Lines->Add(X);
			Memo1->Lines->Add(Y);
			Memo1->Lines->Add(PRIM1[pcur].p_w);
			Memo1->Lines->Add(PRIM1[pcur].p_h);
			Memo1->Lines->Add(mode);*/
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)) //���� ������� ����� ���������
{
if (test==true) {


			prim1 = new NPrim; //������� ��������-������
			pcur = canv1->p_count; //����� ������ ����� ������� ��� �������
			PRIM1[pcur]=*prim1; //���������� �������� � ���������
			PRIM1[pcur].type=mode; //���������� ��� ����� ��������
			PRIM1[pcur].p_x=X; //���������� ������
			PRIM1[pcur].p_y=Y;
			PRIM1[pcur].bcolor=Form1->Shape1->Brush->Color; //�������

			Memo1->Clear();
			Memo1->Lines->Add(canv1->PMap.size());
			Memo1->Lines->Add(PRIM1[pcur].p_x);
			Memo1->Lines->Add(PRIM1[pcur].p_y);
			Memo1->Lines->Add(PRIM1[pcur].p_w);
			Memo1->Lines->Add(PRIM1[pcur].p_h);
			Memo1->Lines->Add(mode);

			test=false;
}
else
{

	PRIM1[pcur].p_w=X-PRIM1[pcur].p_x; //�������� ��������� �������
	PRIM1[pcur].p_h=Y-PRIM1[pcur].p_y;
	canv1->Draw_Pic();	//�������������� �����
	//Form1->Image1MouseMove((TImage *)Sender, Shift, PRIM1[pcur].p_x, PRIM1[pcur].p_y);
	//Form1->Canvas->Rectangle(PRIM1[pcur].p_x,PRIM1[pcur].p_y,(PRIM1[pcur].p_x+PRIM1[pcur].p_w),(PRIM1[pcur].p_y+PRIM1[pcur].p_h));
	//for (int i=0; i<(canv1->PMap.size()-1); i++) paint(PRIM1[pcur]);

		   //	Memo1->Clear();
		  //	Memo1->Lines->Add(canv1->PMap.size());
		  //	Memo1->Lines->Add(pcur);
		  //	Memo1->Lines->Add(mode);

	canv1->p_count++;
	pcur=-1;
	mode=100;
	test=false;
}
}
}
//---------------------------------------------------------------------------


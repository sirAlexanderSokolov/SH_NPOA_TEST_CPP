//---------------------------------------------------------------------------
#define PRIM1 canv1->PMap
#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//функции поворота

TForm1 *Form1;

//-------NPrim
class NPrim {//класс примитива
public:
int type; //вид примитива
	//0 - прямоугольник
	//1 - окружность
	//2 - точка
TColor bcolor, pcolor; //условно цвет заливки
int p_x, p_y, p_w, p_h; //координаты примитива х, у, ширина и высота прямоугольника в который вписан примитив
};
//-------NPrim

int p_count=2; //общее число примитивов на рисунке
map<int, NPrim*> PMap; //контейнер для хранения и обращения к примитивам вида: индекс - примитив
int mode=100; //модификатор рисования фигур
int p_cur=-1; //выбранный пользователем для работы примитив
bool protect=false; //чтобы не спамились объекты при зажатии лкм
int dragstate=0;
int aaa;

void PDraw()
{
for (int i = 0; i < PMap.size(); i++)
	{
	aaa=i;
	Form1->Canvas->Brush->Color=PMap[i]->bcolor;
	Form1->Canvas->Pen->Color=PMap[i]->pcolor;;
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

int PickP(int x, int y) //выделение примитива на холсте для редактирования - выбор его индекса
	{
	for(int i=PMap.size()-1; i>=1;i--) //можно оптимизировать - вынести в базовый класс
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

PMap[0]=new NPrim;      //канва
PMap[0]->type=0;
PMap[0]->bcolor=clWhite;
PMap[0]->pcolor=clBlack;
PMap[0]->p_x=0;
PMap[0]->p_y=0;
PMap[0]->p_w=Form1->Width;
PMap[0]->p_h=Form1->Height;

PMap[1]=new NPrim;     //элемент для редактирования
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
mode = 2;
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&&(protect==true)) //если активен режим рисования
	{
	p_cur=p_count;
	PMap[p_cur]=new NPrim;
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
switch (mode) //пространство для дальнейших изменений
	{
	case 100: //если пользователь кликнул в "пустом" режиме
		{

		p_cur=PickP(X,Y);
		if (p_cur >= 2) // если пользователь выбрал объект для редактирования
			{
			PMap[1]->p_x=PMap[p_cur]->p_x-5;
			PMap[1]->p_y=PMap[p_cur]->p_y-5;
			PMap[1]->p_w=PMap[p_cur]->p_w+10;
			PMap[1]->p_h=PMap[p_cur]->p_h+10;

		Form1->Memo1->Clear();
		Form1->Memo1->Lines->Add(PMap[p_cur]->p_x);
		Form1->Memo1->Lines->Add(PMap[p_cur]->p_y);
		Form1->Memo1->Lines->Add(PMap[p_cur]->p_w);
		Form1->Memo1->Lines->Add(PMap[p_cur]->p_h);// */

		Form1->Memo1->Lines->Add(PMap[1]->p_x);
		Form1->Memo1->Lines->Add(PMap[1]->p_y);
		Form1->Memo1->Lines->Add(PMap[1]->p_w);
		Form1->Memo1->Lines->Add(PMap[1]->p_h); // */
			PDraw();
			}
			mode=101; //включаем режим активного элемента редактирования
			}
		break;
	case 101: //если пользователь кликнул в режиме активного элемента редактирования
		{
		if (dragstate==1)dragstate=2;
		else mode = 100;
		}
	}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //режим рисования
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	}
else
{
switch (mode) //пространство для дальнейших изменений
	{
	case 100: //если пользователь кликнул в "пустом" режиме
		{
		}
		break;
	case 101: //если пользователь кликнул в режиме активного элемента редактирования
		{
	if (dragstate==0) {


		if (((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y)) || ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h)))
		{
		Form1->Cursor=-7;
		dragstate=1;
		}
		else if (((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x)) || ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w)))
		{
		Form1->Cursor=-9;
		dragstate=1;
		}
		else
		{
		Form1->Cursor=0;
		dragstate=0;
		}
	}
	else if (dragstate==2){
			PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
			PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
			PMap[1]->p_x=PMap[p_cur]->p_x-5;
			PMap[1]->p_y=PMap[p_cur]->p_y-5;
			PMap[1]->p_w=PMap[p_cur]->p_w+10;
			PMap[1]->p_h=PMap[p_cur]->p_h+10;

			PDraw();
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
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //если активен режим рисования
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	p_cur=-1;
	mode=100;
	protect=true;
	}

if (dragstate==2)dragstate=1;
}
//---------------------------------------------------------------------------


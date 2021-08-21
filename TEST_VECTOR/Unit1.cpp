//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//функции поворота
//увеличить область захвата примитива
//если рисуют справа налево снизу вверх

TForm1 *Form1;

//-------NPrim
class NPrim {//класс примитива
public:
int type; //вид примитива
	//0 - прямоугольник
	//1 - окружность
	//2 - точка
//можно сделать bool enabled
TColor bcolor, pcolor; //условно цвет заливки
int p_x, p_y, p_w, p_h; //координаты примитива х, у, ширина и высота прямоугольника в который вписан примитив
};
//-------NPrim

int p_count=2; //общее число примитивов на рисунке
map<int, NPrim*> PMap; //контейнер для хранения и обращения к примитивам вида: индекс - примитив
int mode=100; //модификатор рисования фигур
int p_cur=-1; //выбранный пользователем для работы примитив
bool protect=false; //чтобы не спамились объекты при зажатии лкм
int dragstate=0; //состояние редактированияm
int tmp_X=0; //координаты для перемещения объектов
int tmp_Y=0;
//---------------------------------------------------------------------------
void PDraw()  //функция отрисовки примитивов
{
for (int i = 0; i < PMap.size(); i++)
	{
	Form1->Canvas->Brush->Color=PMap[i]->bcolor;
	Form1->Canvas->Pen->Color=PMap[i]->pcolor;;
		switch (PMap[i]->type)
		{
		case 0: Form1->Canvas->Rectangle(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;//прямоуг
		case 1: Form1->Canvas->Ellipse(PMap[i]->p_x,PMap[i]->p_y,(PMap[i]->p_x+PMap[i]->p_w),(PMap[i]->p_y+PMap[i]->p_h));
		break;  //эллипс
		case 2:
			{   //тчк
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
int PickP(int x, int y)//выделение примитива на холсте для редактирования - выбор его индекса
	{
	for(int i=PMap.size()-1; i>=1;i--) //можно оптимизировать - вынести в базовый класс
		{
		if (i==1) return -1;
		else if ((x>=PMap[i]->p_x) && (x<=PMap[i]->p_x+PMap[i]->p_w) &&	(y>=PMap[i]->p_y) && (y<=PMap[i]->p_y+PMap[i]->p_h))return i;
		}
	}
//---------------------------------------------------------------------------
void BSet(bool Default)  //вычисление параметров рамки
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
Form1->DoubleBuffered=true;   //буферизация графики

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
BSet(true);   //дефолтные параметры рамки редактирования объекта
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
PDraw();  //отрисовываем холст
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
for (unsigned int i = 0; i<PMap.size(); i++) delete PMap[i];
PMap.clear();             //очищаем память
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
mode = 0;     //прямоугольник
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
mode = 1;    //эллипс
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
mode = 2;    // точка
protect=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
if ((mode >= 0)	&& (mode <100)&&(protect==true)) //если активен режим рисования
	{
	p_cur=p_count;
	PMap[p_cur]=new NPrim;   //создаем новый примитив
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
		if (PickP(X,Y) >= 2) // если пользователь выбрал объект для редактирования
			{
			p_cur=PickP(X,Y);
			BSet(false);  //отрисовываем элементы редактирования
			PDraw();      //---/---
			mode=101; //включаем режим активного элемента редактирования
			}
		}
		break;
	case 101: //если пользователь кликнул в режиме активного элемента редактирования
		{
		if (dragstate==1)    //если курсор на элементе редактирования
		{
		if ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y))
			{  //гориз-верх
			dragstate=2;  //можно растягвать и зажата ЛКМ
			}
		else if ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h))
			{  //гориз-низ
			dragstate=3;  //можно растягвать и зажата ЛКМ
			}
		else if ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w))
			{  //верт-право
			dragstate=4;  //можно растягвать и зажата ЛКМ
			}
		else if ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x))
			{  //верт-лево
			dragstate=5;  //можно растягвать и зажата ЛКМ
			}
		else if ((X > ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x-10)))
		&& (X < ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x+10)))
		&& (Y > ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y-10)))
		&& (Y < ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y+10))))
			{
			dragstate=6;  //можно растягвать и зажата ЛКМ
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
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //режим рисования
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;       //отрисовываем будующий примитив
	PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
	PDraw();
	}
else
{
switch (mode) //пространство для дальнейших изменений
	{
	case 100: //если пользователь кликнул в "пустом" режиме
	break;
	case 101: //если пользователь навел мышь в режиме активного элемента редактирования
	{
	switch (dragstate)
	{
	case 0: case 1:  //если мышь наведена на элемент редактирования
	{
	if (((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y))
	   || ((X>PMap[1]->p_x)&&(X<PMap[1]->p_x+PMap[1]->p_w)&&(Y==PMap[1]->p_y+PMap[1]->p_h)))
		{   //навели на горизонтальную линии
		Form1->Cursor=-15; //меняем курсор
		dragstate=1;  //разрешаем растягвать
		}
	else if (((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x))
	   || ((Y>PMap[1]->p_y)&&(Y<PMap[1]->p_y+PMap[1]->p_h)&&(X==PMap[1]->p_x+PMap[1]->p_w)))
		{  //навели на вертикальную линии
		Form1->Cursor=-14; //меняем курсор
		dragstate=1;   //разрешаем растягвать
		}
	else if ((X > ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x-10)))
		&& (X < ::ceil(float(PMap[1]->p_w/2 + PMap[1]->p_x+10)))
		&& (Y > ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y-10)))
		&& (Y < ::ceil(float(PMap[1]->p_h/2 + PMap[1]->p_y+10))))
		{      //перемещение
		Form1->Cursor=-22;  //меняем курсор
		dragstate=1;   //разрешаем перемещать
		}
	else
		{
		Form1->Cursor=0; //ушли от нужной линии - дефолтный курсор
		dragstate=0;  //нельзя растягвать
		}
	}
	break;
    case 2:
		{      //тянем вверх
		PMap[p_cur]->p_h=(PMap[p_cur]->p_h-(Y-PMap[p_cur]->p_y));
		PMap[p_cur]->p_y=Y;
		BSet(false);
		PDraw();
		}
	break;
	case 3:    //вниз
		{
		PMap[p_cur]->p_h=Y-PMap[p_cur]->p_y;
		BSet(false);
		PDraw();
		}
	break;
	case 4:    //вправо
		{
		PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;
		BSet(false);
		PDraw();
		}
	break;
	case 5:   //влево
		{
		PMap[p_cur]->p_w=(PMap[p_cur]->p_w-(X-PMap[p_cur]->p_x));
		PMap[p_cur]->p_x=X;
		BSet(false);
		PDraw();
		}
	break;
	case 6:   //перемещаем
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
if ((mode >= 0)	&& (mode <100)&& (protect==false)) //если активен режим рисования
	{
	PMap[p_cur]->p_w=X-PMap[p_cur]->p_x;   //заканчиваем рисовать примитив
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


//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ColorGrd.hpp>
#include <map>
#include <math.h>

using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:	// User declarations

int dragstate, tmp_X, tmp_Y;

public:		// User declarations

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

bool protect; //чтобы не спамились объекты при зажатии лкм
int p_count, p_cur, mode;
map<int, NPrim*> PMap; //контейнер для хранения и обращения к примитивам вида: индекс - примитив
void __fastcall PDraw();   //функция отрисовки всех элементов на холсте
void __fastcall BSet(bool Default);  //определение границ рамки редактирования примитива
int __fastcall BSel (NPrim *PR, int X, int Y);  //функция выбора границы редактирования примитива
int __fastcall PickP(int x, int y);  // функция выбора примитива для редактирования

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

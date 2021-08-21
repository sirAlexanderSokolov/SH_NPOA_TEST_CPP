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

bool protect; //����� �� ��������� ������� ��� ������� ���
int p_count, p_cur, mode;
map<int, NPrim*> PMap; //��������� ��� �������� � ��������� � ���������� ����: ������ - ��������
void __fastcall PDraw();   //������� ��������� ���� ��������� �� ������
void __fastcall BSet(bool Default);  //����������� ������ ����� �������������� ���������
int __fastcall BSel (NPrim *PR, int X, int Y);  //������� ������ ������� �������������� ���������
int __fastcall PickP(int x, int y);  // ������� ������ ��������� ��� ��������������

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

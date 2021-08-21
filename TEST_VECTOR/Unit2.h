//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ColorGrd.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TColorGrid *ColorGrid1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

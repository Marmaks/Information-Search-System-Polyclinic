//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid;
	TButton *ButtonAdd;
	TEdit *EditSecondName;
	TEdit *EditFirstName;
	TEdit *EditHeight;
	TEdit *EditWeight;
	TButton *ButtonUpdate;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EditThirdName;
	TLabel *Label2;
	TLabel *Label6;
	TButton *ButtonDelete;
	TButton *ButtonApplyChanges;
	TMainMenu *MainMenu;
	TMenuItem *N1Info;
	TMenuItem *N2About;
	TStatusBar *StatusBar;
	TRadioGroup *RadioGroup;
	TButton *ButtonSearch;
	TEdit *EditSearchValue;
	TLabel *Label7;
	TButton *ButtonDone;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TMenuItem *N7;
	TMenuItem *N8;
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonUpdateClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall StringGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall StringGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall StringGridSetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);
	void __fastcall ButtonApplyChangesClick(TObject *Sender);
	void __fastcall ButtonSearchClick(TObject *Sender);
	void __fastcall ButtonDoneClick(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall N2AboutClick(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall EditSecondNameKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditHeightKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall EditWeightKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StringGridKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StringGridExit(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

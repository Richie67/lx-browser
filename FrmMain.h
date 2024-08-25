//---------------------------------------------------------------------------

#ifndef FrmMainH
#define FrmMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Menus.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.MagnifierGlass.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include "DlgSelectMandantAndYear.h"
#include "Kostenstellen.h"
#include "ModelMainForm.h"
#include "Filter.h"
#include <FMX.Memo.Types.hpp>
#include <FMX.ComboEdit.hpp>


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TButton *BttnLoad;
	TToolBar *ToolBar1;
	TStatusBar *StatusBar1;
	TMenuItem *MnuItmFile;
	TMenuItem *MnuItmHelp;
	TMemo *Memo1;
	TStringGrid *StringGrid1;
	TComboBox *ComboBox1;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TStringColumn *StringColumn8;
	TStringColumn *StringColumn9;
	TCheckColumn *CheckColumn1;
	TLabel *Label1;
	TLabel *Label2;
	TPanel *Panel1;
	TLabel *Label3;
	TEdit *EdBuchungsText;
	TEdit *EdSollKtoName;
	TEdit *EdHabenKtoName;
	TEdit *EdBuchungsNr;
	TEdit *EdSollKtoNr;
	TEdit *EdHabenKtoNr;
	TButton *BttnLogKonten;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EdDatumBuchung;
	TEdit *EdBetragNetto;
	TEdit *EdKostenstelle1;
	TEdit *EdKostenstelle2;
	TLabel *LblBetrag;
	TButton *BttnJournal;
	TButton *BttnKostenstellen;
	TButton *BttnDatum;
	TComboBox *ComboKst1;
	TComboBox *ComboKst2;
	TButton *BttnSave;
	TButton *BttnClear;
	TButton *BttnDelete;
	TComboBox *ComboKtoSoll;
	TComboBox *ComboKtoHaben;
	TEdit *EdDatumBeleg;
	TLabel *Label6;
	TButton *BttnMissingKSt;
	TButton *BttnKtoChk;
	TButton *BttnExport;
	TSaveDialog *SaveDialog1;
	TStringColumn *StringColumn10;
	TMenuItem *MenuItemFileExit;
	TPanel *Panel2;
	TButton *BttnFilterClear;
	TLabel *Label7;
	TEdit *EdFilter;
	TButton *BttenFilterKonten;
	TButton *BttnFilterCostUnit;
	TButton *BttnAmount;
	TButton *BttnBudget;
	TMenuItem *MenuItemReports;
	TMenuItem *MenuItemReportsBudget;
	void __fastcall BttnLoadClick(TObject *Sender);
	void __fastcall StringGrid1CellClick(TColumn * const Column, const int Row);
	void __fastcall BttnLogKontenClick(TObject *Sender);
	void __fastcall StringGrid1SelChanged(TObject *Sender);
	void __fastcall BttnDatumClick(TObject *Sender);
	void __fastcall BttnKostenstellenClick(TObject *Sender);
	void __fastcall BttnSaveClick(TObject *Sender);
	void __fastcall ComboKst1Change(TObject *Sender);
	void __fastcall ComboKst2Change(TObject *Sender);
	void __fastcall BttnClearClick(TObject *Sender);
	void __fastcall BttnDeleteClick(TObject *Sender);
	void __fastcall ComboKtoSollChange(TObject *Sender);
	void __fastcall ComboKtoHabenChange(TObject *Sender);
	void __fastcall BttnMissingKStClick(TObject *Sender);
	void __fastcall updateKostenstellenEdit(TEdit *pEdit, Kostenstellen &kostenstellen, int idKst);
	void __fastcall BttnKtoChkClick(TObject *Sender);
	void __fastcall BttnExportClick(TObject *Sender);
	void __fastcall MenuItemFileExitClick(TObject *Sender);
	void __fastcall BttnFilterClearClick(TObject *Sender);
	void __fastcall BttenFilterKontenClick(TObject *Sender);
	void __fastcall BttnFilterCostUnitClick(TObject *Sender);
	void __fastcall BttnAmountClick(TObject *Sender);
	void __fastcall BttnBudgetClick(TObject *Sender);
	void __fastcall MenuItemReportsBudgetClick(TObject *Sender);
private:	// User declarations
    bool ignoreOnClick;
	ModelJournal model;
    ::Filter filter;
	void __fastcall fillStringGrid();
	void __fastcall fillDetailView(int row);
	void __fastcall update();
	void __fastcall disableControls();
	void __fastcall enableControls();
	void __fastcall lockControls(bool enabled);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

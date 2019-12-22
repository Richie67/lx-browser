//---------------------------------------------------------------------------

#ifndef FormBudgetH
#define FormBudgetH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Budget.h"
//---------------------------------------------------------------------------

class TFrmBudget : public TForm
{
__published:	// IDE-managed Components
	TEdit *Ed01BdgtPraesidium;
	TEdit *Ed02BdgtRKAllg;
	TEdit *Ed03BdgtRKSachk;
	TEdit *Ed04BdgtRKPerso;
	TEdit *Ed05BdgtIFSAllg;
	TEdit *Ed06BdgtIFSSachk;
	TEdit *Ed07BdgtIFSPerso;
	TEdit *Ed08BdgtRHAllg;
	TEdit *Ed09BdgtIHAllg;
	TEdit *Ed10BdgtSLBAllg;
	TEdit *Ed11BdgtIADAllg;
	TEdit *Ed12BdgtISHAllg;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *Ed13BdgtRDAllg;
	TLabel *Label9;
	TEdit *Ed15EgnlPraesidium;
	TEdit *Ed16EgnlRKAllg;
	TEdit *Ed17EgnlRKSachk;
	TEdit *Ed18EgnlRKPerso;
	TEdit *Ed19EgnlIFSAllg;
	TEdit *Ed20EgnlIFSSachk;
	TEdit *Ed21EgnlIFSPerso;
	TEdit *Ed22EgnlRHAllg;
	TEdit *Ed23EgnlIHAllg;
	TEdit *Ed24EgnlSLBAllg;
	TEdit *Ed25EgnlIADAllg;
	TEdit *Ed26EgnlISHAllg;
	TEdit *Ed27EgnlRDAllg;
	TLabel *Label10;
	TLabel *Label11;
	TPanel *Panel1;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TButton *Button1;
	TLabel *Label17;
	TEdit *Ed14BdgtJugAllg;
	TEdit *Ed28EgnlJugAllg;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Ed01BdgtPraesidiumExit(TObject *Sender);
	void __fastcall Ed02BdgtRKAllgExit(TObject *Sender);
	void __fastcall Ed03BdgtRKSachkExit(TObject *Sender);
	void __fastcall Ed04BdgtRKPersoExit(TObject *Sender);
	void __fastcall Ed05BdgtIFSAllgExit(TObject *Sender);
	void __fastcall Ed06BdgtIFSSachkExit(TObject *Sender);
	void __fastcall Ed07BdgtIFSPersoExit(TObject *Sender);
	void __fastcall Ed08BdgtRHAllgExit(TObject *Sender);
	void __fastcall Ed09BdgtIHAllgExit(TObject *Sender);
	void __fastcall Ed10BdgtSLBAllgExit(TObject *Sender);
	void __fastcall Ed11BdgtIADAllgExit(TObject *Sender);
	void __fastcall Ed12BdgtISHAllgExit(TObject *Sender);
	void __fastcall Ed13BdgtRDAllgExit(TObject *Sender);
	void __fastcall Ed15EgnlPraesidiumExit(TObject *Sender);
	void __fastcall Ed16EgnlRKAllgExit(TObject *Sender);
	void __fastcall Ed17EgnlRKSachkExit(TObject *Sender);
	void __fastcall Ed18EgnlRKPersoExit(TObject *Sender);
	void __fastcall Ed19EgnlIFSAllgExit(TObject *Sender);
	void __fastcall Ed20EgnlIFSSachkExit(TObject *Sender);
	void __fastcall Ed21EgnlIFSPersoExit(TObject *Sender);
	void __fastcall Ed22EgnlRHAllgExit(TObject *Sender);
	void __fastcall Ed23EgnlIHAllgExit(TObject *Sender);
	void __fastcall Ed24EgnlSLBAllgExit(TObject *Sender);
	void __fastcall Ed25EgnlIADAllgExit(TObject *Sender);
	void __fastcall Ed26EgnlISHAllgExit(TObject *Sender);
	void __fastcall Ed27EgnlRDAllgExit(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Ed14BdgtJugAllgExit(TObject *Sender);
	void __fastcall Ed28EgnlJugAllgExit(TObject *Sender);
private:	// User declarations
	tcBudget    Budget;
	__fastcall double convertDouble(TObject *Sender) {
		TEdit *pEdit = dynamic_cast<TEdit*> (Sender);
		UnicodeString us = pEdit->Text;
		double result = 0.0;
		if (us.Length() > 0) {
			try {
			 result = us.ToDouble();
			} catch (EConvertError &E) {
				ShowMessage(E.Message);
			}
		}
		return result;
	}
public:		// User declarations
	__fastcall TFrmBudget(TComponent* Owner);
	void __fastcall saveToRegistry();
	void __fastcall loadFromRegistry();
	void __fastcall fillForm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmBudget *FrmBudget;
//---------------------------------------------------------------------------
#endif

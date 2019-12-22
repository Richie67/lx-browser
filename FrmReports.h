//---------------------------------------------------------------------------

#ifndef FrmReportsH
#define FrmReportsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <Data.DbxSqlite.hpp>
#include <FMX.frxClass.hpp>
#include <FMX.frxDBSet.hpp>
//---------------------------------------------------------------------------
class TFormReports : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLQuery *SQLQuery1;
	TButton *BttnExecute;
	TMemo *Memo1;
	TfrxReport *frxReport1;
	TfrxDBDataset *frxDBDataset1;
	TButton *BttnKostenstellen;
	TSQLQuery *SQLQuery2;
	TfrxDBDataset *frxDBDataset2;
	TfrxReport *frxReport2;
	TButton *BttnFinanzstatus;
	TSQLQuery *SQLQuery3;
	TfrxDBDataset *frxDBDataset3;
	TfrxReport *frxReport3;
	TButton *BttnLeistungssport;
	TSQLQuery *SQLQuery4;
	TfrxDBDataset *frxDBDataset4;
	TfrxReport *frxReport4;
	TButton *BttnSKKosten;
	TSQLQuery *SQLQuery5;
	TfrxDBDataset *frxDBDataset5;
	TfrxReport *frxReport5;
	void __fastcall BttnConnectClick(TObject *Sender);
	void __fastcall BttnExecuteClick(TObject *Sender);
	void __fastcall BttnKostenstellenClick(TObject *Sender);
	void __fastcall BttnFinanzstatusClick(TObject *Sender);
	void __fastcall BttnLeistungssportClick(TObject *Sender);
	void __fastcall BttnSKKostenClick(TObject *Sender);
private:	// User declarations
	void __fastcall ShowSelectResults();
	UnicodeString   databaseFileName;
public:		// User declarations
	__fastcall TFormReports(TComponent* Owner);
	void __fastcall setDatabaseFileName(UnicodeString fina);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormReports *FormReports;
//---------------------------------------------------------------------------
#endif

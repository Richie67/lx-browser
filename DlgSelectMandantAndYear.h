//---------------------------------------------------------------------------

#ifndef DlgSelectMandantAndYearH
#define DlgSelectMandantAndYearH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <string>
//---------------------------------------------------------------------------
class TFrmDlgSelectMandantAndYear : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *BttnOK;
	TButton *BttnCancel;
	TGroupBox *GroupBox1;
	TRadioButton *RdBttn2021;
	TRadioButton *RdBttn2020;
	TRadioButton *RdBttn2019;
private:	// User declarations
public:		// User declarations
	__fastcall TFrmDlgSelectMandantAndYear(TComponent* Owner);
	std::string getMandant();
    int getYearOfBooking();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDlgSelectMandantAndYear *FrmDlgSelectMandantAndYear;
//---------------------------------------------------------------------------
#endif

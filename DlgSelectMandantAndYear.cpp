//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DlgSelectMandantAndYear.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrmDlgSelectMandantAndYear *FrmDlgSelectMandantAndYear;
//---------------------------------------------------------------------------
__fastcall TFrmDlgSelectMandantAndYear::TFrmDlgSelectMandantAndYear(TComponent* Owner)
	: TForm(Owner)
{
}

std::string TFrmDlgSelectMandantAndYear::getMandant() {
	return "00000001";
}


int TFrmDlgSelectMandantAndYear::getYearOfBooking() {
	if (this->RdBttn2021->IsChecked) {
		return 2021;
	}
	if (this->RdBttn2020->IsChecked) {
		return 2020;
	}
	if (this->RdBttn2019->IsChecked) {
		return 2019;
	}
    return 2018;
}

//---------------------------------------------------------------------------

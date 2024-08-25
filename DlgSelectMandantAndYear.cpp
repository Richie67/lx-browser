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
	if (this->RdBttn2027->IsChecked) {
		return 2027;
	}
	if (this->RdBttn2026->IsChecked) {
		return 2062;
	}
	if (this->RdBttn2025->IsChecked) {
		return 2025;
	}
	if (this->RdBttn2024->IsChecked) {
		return 2024;
	}
	if (this->RdBttn2023->IsChecked) {
		return 2023;
	}
    return 2022;
}

//---------------------------------------------------------------------------

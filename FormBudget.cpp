//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FormBudget.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrmBudget *FrmBudget;
//---------------------------------------------------------------------------
__fastcall TFrmBudget::TFrmBudget(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmBudget::Button1Click(TObject *Sender)
{
	this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------





void __fastcall TFrmBudget::saveToRegistry() {
	Budget.saveIntoRegistry();
}


void __fastcall TFrmBudget::loadFromRegistry() {
	Budget.loadFromRegistry();
}

void __fastcall TFrmBudget::Ed01BdgtPraesidiumExit(TObject *Sender)
{
	Budget.bdgt_Praesidium = convertDouble(Sender);
	// MessageBox(0, L"Exit", L"Exit", MB_OK);
}
//---------------------------------------------------------------------------


void __fastcall TFrmBudget::Ed02BdgtRKAllgExit(TObject *Sender)
{
	Budget.bdgt_RK_Allgemein = convertDouble(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed03BdgtRKSachkExit(TObject *Sender)
{
	Budget.bdgt_RK_Sachkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed04BdgtRKPersoExit(TObject *Sender)
{
	Budget.bdgt_RK_Personalkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed05BdgtIFSAllgExit(TObject *Sender)
{
	Budget.bdgt_IFS_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed06BdgtIFSSachkExit(TObject *Sender)
{
	Budget.bdgt_IFS_Sachkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed07BdgtIFSPersoExit(TObject *Sender)
{
	Budget.bdgt_IFS_Personalkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed08BdgtRHAllgExit(TObject *Sender)
{
	Budget.bdgt_RH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed09BdgtIHAllgExit(TObject *Sender)
{
	Budget.bdgt_IH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed10BdgtSLBAllgExit(TObject *Sender)
{
	Budget.bdgt_SLB_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed11BdgtIADAllgExit(TObject *Sender)
{
	Budget.bdgt_IAD_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed12BdgtISHAllgExit(TObject *Sender)
{
	Budget.bdgt_ISH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed13BdgtRDAllgExit(TObject *Sender)
{
	Budget.bdgt_RD_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed15EgnlPraesidiumExit(TObject *Sender)
{
	Budget.egnl_Praesidium = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed16EgnlRKAllgExit(TObject *Sender)
{
	Budget.egnl_RK_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed17EgnlRKSachkExit(TObject *Sender)
{
	Budget.egnl_RK_Sachkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed18EgnlRKPersoExit(TObject *Sender)
{
	Budget.egnl_RK_Personalkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed19EgnlIFSAllgExit(TObject *Sender)
{
	Budget.egnl_IFS_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed20EgnlIFSSachkExit(TObject *Sender)
{
	Budget.egnl_IFS_Sachkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed21EgnlIFSPersoExit(TObject *Sender)
{
	Budget.egnl_IFS_Personalkosten = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed22EgnlRHAllgExit(TObject *Sender)
{
	Budget.egnl_RH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed23EgnlIHAllgExit(TObject *Sender)
{
	Budget.egnl_IH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed24EgnlSLBAllgExit(TObject *Sender)
{
	Budget.egnl_SLB_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed25EgnlIADAllgExit(TObject *Sender)
{
	Budget.egnl_IAD_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed26EgnlISHAllgExit(TObject *Sender)
{
	Budget.egnl_ISH_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed27EgnlRDAllgExit(TObject *Sender)
{
	Budget.egnl_RD_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

inline UnicodeString ff(double d) {
	return UnicodeString::FormatFloat("####0.00", d);
}


void __fastcall TFrmBudget::fillForm() {
	// hello
	this->Ed01BdgtPraesidium->Text = ff(this->Budget.bdgt_Praesidium);
	this->Ed02BdgtRKAllg->Text = ff(this->Budget.bdgt_RK_Allgemein);
	this->Ed03BdgtRKSachk->Text = ff(this->Budget.bdgt_RK_Sachkosten);
	this->Ed04BdgtRKPerso->Text = ff(this->Budget.bdgt_RK_Personalkosten);
	this->Ed05BdgtIFSAllg->Text = ff(this->Budget.bdgt_IFS_Allgemein);
	this->Ed06BdgtIFSSachk->Text = ff(this->Budget.bdgt_IFS_Sachkosten);
	this->Ed07BdgtIFSPerso->Text = ff(this->Budget.bdgt_IFS_Personalkosten);
	this->Ed08BdgtRHAllg->Text = ff(this->Budget.bdgt_RH_Allgemein);
	this->Ed09BdgtIHAllg->Text = ff(this->Budget.bdgt_IH_Allgemein);
	this->Ed10BdgtSLBAllg->Text = ff(this->Budget.bdgt_SLB_Allgemein);
	this->Ed11BdgtIADAllg->Text = ff(this->Budget.bdgt_IAD_Allgemein);
	this->Ed12BdgtISHAllg->Text = ff(this->Budget.bdgt_ISH_Allgemein);
	this->Ed13BdgtRDAllg->Text = ff(this->Budget.bdgt_RD_Allgemein);
	this->Ed14BdgtJugAllg->Text = ff(this->Budget.bdgt_Jugend_Allgemein);
	/* */
	this->Ed15EgnlPraesidium->Text = ff(this->Budget.egnl_Praesidium);
	this->Ed16EgnlRKAllg->Text = ff(this->Budget.egnl_RK_Allgemein);
	this->Ed17EgnlRKSachk->Text = ff(this->Budget.egnl_RK_Sachkosten);
	this->Ed18EgnlRKPerso->Text = ff(this->Budget.egnl_RK_Personalkosten);
	this->Ed19EgnlIFSAllg->Text = ff(this->Budget.egnl_IFS_Allgemein);
	this->Ed20EgnlIFSSachk->Text = ff(this->Budget.egnl_IFS_Sachkosten);
	this->Ed21EgnlIFSPerso->Text = ff(this->Budget.egnl_IFS_Personalkosten);
	this->Ed22EgnlRHAllg->Text = ff(this->Budget.egnl_RH_Allgemein);
	this->Ed23EgnlIHAllg->Text = ff(this->Budget.egnl_IH_Allgemein);
	this->Ed24EgnlSLBAllg->Text = ff(this->Budget.egnl_SLB_Allgemein);
	this->Ed25EgnlIADAllg->Text = ff(this->Budget.egnl_IAD_Allgemein);
	this->Ed26EgnlISHAllg->Text = ff(this->Budget.egnl_ISH_Allgemein);
	this->Ed27EgnlRDAllg->Text = ff(this->Budget.egnl_RD_Allgemein);
	this->Ed28EgnlJugAllg->Text = ff(this->Budget.egnl_Jugend_Allgemein);
}

void __fastcall TFrmBudget::FormShow(TObject *Sender)
{
	this->fillForm();
}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed14BdgtJugAllgExit(TObject *Sender)
{
	//
	Budget.bdgt_Jugend_Allgemein = convertDouble(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFrmBudget::Ed28EgnlJugAllgExit(TObject *Sender)
{
 	Budget.egnl_Jugend_Allgemein = convertDouble(Sender);
}
//---------------------------------------------------------------------------


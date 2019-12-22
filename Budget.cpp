//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <FMX.Dialogs.hpp>
/*
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
*/
#include <System.Win.Registry.hpp>
#pragma hdrstop


#include "Budget.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void RetrieveOrUpdateKeys(tcBudget *pBudget, bool doRead)
{
	TRegistry *Reg = new TRegistry();
	AnsiString temp;

	Reg->RootKey = HKEY_CURRENT_USER;
	try {
		bool canAccess = false;
		if(Reg->KeyExists("SOFTWARE\\LexwareBrowser"))
		{
			if(Reg->OpenKey("Software\\LexwareBrowser", true))
			{
				canAccess = true;
			}
		} else {
			if(Reg->CreateKey("Software\\LexwareBrowser"))
			{
				canAccess = true;
			}
		}
		if (canAccess) {

			if (doRead) {
				pBudget->bdgt_Praesidium = Reg->ReadFloat("BudgetPraesidium");
				pBudget->bdgt_RK_Allgemein = Reg->ReadFloat("BudgetRKAllgemein");
				pBudget->bdgt_RK_Sachkosten = Reg->ReadFloat("BudgetRKSachkosten");
				pBudget->bdgt_RK_Personalkosten = Reg->ReadFloat("BudgetRKPersonalkosten");
				pBudget->bdgt_IFS_Allgemein = Reg->ReadFloat("BudgetIFSAllgemein");
				pBudget->bdgt_IFS_Sachkosten = Reg->ReadFloat("BudgetIFSSachkosten");
				pBudget->bdgt_IFS_Personalkosten = Reg->ReadFloat("BudgetIFSPersonalkosten");
				pBudget->bdgt_RH_Allgemein = Reg->ReadFloat("BudgetRHAllgemein");
				pBudget->bdgt_IH_Allgemein = Reg->ReadFloat("BudgetIHAllgemein");
				pBudget->bdgt_SLB_Allgemein = Reg->ReadFloat("BudgetSLBAllgemein");
				pBudget->bdgt_IAD_Allgemein = Reg->ReadFloat("BudgetIADAllgemein");
				pBudget->bdgt_ISH_Allgemein = Reg->ReadFloat("BudgetISHAllgemein");
				pBudget->bdgt_RD_Allgemein = Reg->ReadFloat("BudgetRDAllgemein");
				pBudget->bdgt_Jugend_Allgemein = Reg->ReadFloat("BudgetJugendAllgemein");

				pBudget->egnl_Praesidium = Reg->ReadFloat("EigenleistungPraesidium");
				pBudget->egnl_RK_Allgemein = Reg->ReadFloat("EigenleistungRKAllgemein");
				pBudget->egnl_RK_Sachkosten = Reg->ReadFloat("EigenleistungRKSachkosten");
				pBudget->egnl_RK_Personalkosten = Reg->ReadFloat("EigenleistungRKPersonalkosten");
				pBudget->egnl_IFS_Allgemein = Reg->ReadFloat("EigenleistungIFSAllgemein");
				pBudget->egnl_IFS_Sachkosten = Reg->ReadFloat("EigenleistungIFSSachkosten");
				pBudget->egnl_IFS_Personalkosten = Reg->ReadFloat("EigenleistungIFSPersonalkosten");
				pBudget->egnl_RH_Allgemein = Reg->ReadFloat("EigenleistungRHAllgemein");
				pBudget->egnl_IH_Allgemein = Reg->ReadFloat("EigenleistungIHAllgemein");
				pBudget->egnl_SLB_Allgemein = Reg->ReadFloat("EigenleistungSLBAllgemein");
				pBudget->egnl_IAD_Allgemein = Reg->ReadFloat("EigenleistungIADAllgemein");
				pBudget->egnl_ISH_Allgemein = Reg->ReadFloat("EigenleistungISHAllgemein");
				pBudget->egnl_RD_Allgemein = Reg->ReadFloat("EigenleistungRDAllgemein");
				pBudget->egnl_Jugend_Allgemein = Reg->ReadFloat("EigenleistungJugendAllgemein");

			} else {
				Reg->WriteFloat("BudgetPraesidium",        pBudget->bdgt_Praesidium);
				Reg->WriteFloat("BudgetRKAllgemein",       pBudget->bdgt_RK_Allgemein);
				Reg->WriteFloat("BudgetRKSachkosten",      pBudget->bdgt_RK_Sachkosten);
				Reg->WriteFloat("BudgetRKPersonalkosten",  pBudget->bdgt_RK_Personalkosten);
				Reg->WriteFloat("BudgetIFSAllgemein",      pBudget->bdgt_IFS_Allgemein);
				Reg->WriteFloat("BudgetIFSSachkosten",     pBudget->bdgt_IFS_Sachkosten);
				Reg->WriteFloat("BudgetIFSPersonalkosten", pBudget->bdgt_IFS_Personalkosten);
				Reg->WriteFloat("BudgetRHAllgemein",       pBudget->bdgt_RH_Allgemein);
				Reg->WriteFloat("BudgetIHAllgemein",       pBudget->bdgt_IH_Allgemein);
				Reg->WriteFloat("BudgetSLBAllgemein",      pBudget->bdgt_SLB_Allgemein);
				Reg->WriteFloat("BudgetIADAllgemein",      pBudget->bdgt_IAD_Allgemein);
				Reg->WriteFloat("BudgetISHAllgemein",      pBudget->bdgt_ISH_Allgemein);
				Reg->WriteFloat("BudgetRDAllgemein",       pBudget->bdgt_RD_Allgemein);
				Reg->WriteFloat("BudgetJugendAllgemein",   pBudget->bdgt_Jugend_Allgemein);

				Reg->WriteFloat("EigenleistungPraesidium",        pBudget->egnl_Praesidium);
				Reg->WriteFloat("EigenleistungRKAllgemein",       pBudget->egnl_RK_Allgemein);
				Reg->WriteFloat("EigenleistungRKSachkosten",      pBudget->egnl_RK_Sachkosten);
				Reg->WriteFloat("EigenleistungRKPersonalkosten",  pBudget->egnl_RK_Personalkosten);
				Reg->WriteFloat("EigenleistungIFSAllgemein",      pBudget->egnl_IFS_Allgemein);
				Reg->WriteFloat("EigenleistungIFSSachkosten",     pBudget->egnl_IFS_Sachkosten);
				Reg->WriteFloat("EigenleistungIFSPersonalkosten", pBudget->egnl_IFS_Personalkosten);
				Reg->WriteFloat("EigenleistungRHAllgemein",       pBudget->egnl_RH_Allgemein);
				Reg->WriteFloat("EigenleistungIHAllgemein",       pBudget->egnl_IH_Allgemein);
				Reg->WriteFloat("EigenleistungSLBAllgemein",      pBudget->egnl_SLB_Allgemein);
				Reg->WriteFloat("EigenleistungIADAllgemein",      pBudget->egnl_IAD_Allgemein);
				Reg->WriteFloat("EigenleistungISHAllgemein",      pBudget->egnl_ISH_Allgemein);
				Reg->WriteFloat("EigenleistungRDAllgemein",       pBudget->egnl_RD_Allgemein);
				Reg->WriteFloat("EigenleistungJugendAllgemein",   pBudget->egnl_Jugend_Allgemein);

			}
			Reg->CloseKey();
		}
	} catch(ERegistryException &E) {
		ShowMessage(E.Message);
		delete Reg;
		return;
	}
	delete Reg;
}



void __fastcall tcBudget::loadFromRegistry(void) {
	RetrieveOrUpdateKeys(this, true);
}


void __fastcall tcBudget::saveIntoRegistry() {
	RetrieveOrUpdateKeys(this, false);
}

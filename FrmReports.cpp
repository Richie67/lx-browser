//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FrmReports.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX.frxClass"
#pragma link "FMX.frxDBSet"
#pragma resource "*.fmx"


TFormReports *FormReports;
//---------------------------------------------------------------------------
__fastcall TFormReports::TFormReports(TComponent* Owner)
	: TForm(Owner)
{
	this->SQLConnection1->Connected = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormReports::BttnConnectClick(TObject *Sender)
{
 // Use double backslash in Windows Paths as the backslash character (\) must be escaped with another one to be treated literally.
	SQLConnection1->Params->Add("Database=" + this->databaseFileName);
	try
	{
		// Establish the connection.
		SQLConnection1->Connected = true;
		BttnExecute->Enabled = true;
		Memo1->Text = "Connection established!";
	}
	catch (EDatabaseError& E)
	{
	   ShowMessage("Exception raised with message" + E.Message);
	}    //
}
//---------------------------------------------------------------------------
void __fastcall TFormReports::BttnExecuteClick(TObject *Sender)
{
	//
   	String query;

	Memo1->ClearSelection();
	// A random query
	query = "SELECT * FROM CostUnit;";
	try
	{
		// Assign the query to the object SQLQuery1.
		 SQLQuery1->SQL->Text = query;
		 SQLQuery1->Active = true;
	}
	catch (Exception& E)
	{
		Memo1->Text = "Exception raised with message" + E.Message;
	 }
	// Show the results of the query in a TMemo control.
	 ShowSelectResults();
}
//---------------------------------------------------------------------------
void __fastcall TFormReports::ShowSelectResults() {

	TStringList* names;
	TField* currentField;
	String currentLine;

	if (!SQLQuery1->IsEmpty()) {
	  SQLQuery1->First();
	  names = new TStringList();
	  __try{
		SQLQuery1->GetFieldNames(names);
		while (!SQLQuery1->Eof) {
		  currentLine = "";
		  for (int i = 0; i < names->Count; ++i) {
			currentField = SQLQuery1->FieldByName(names->Strings[i]);
			currentLine = currentLine + " " + currentField->AsString;
		  }
		   Memo1->Lines->Add(currentLine);
		   SQLQuery1->Next();
		}
	  }
	  __finally {
		names->Free();
	  }
	}
}
void __fastcall TFormReports::BttnKostenstellenClick(TObject *Sender)
{
	this->frxReport1->ShowReport();

}
//---------------------------------------------------------------------------

void __fastcall TFormReports::BttnFinanzstatusClick(TObject *Sender)
{
	this->frxReport2->ShowReport();

}
//---------------------------------------------------------------------------

void __fastcall TFormReports::BttnLeistungssportClick(TObject *Sender)
{
	this->frxReport4->ShowReport();
}
//---------------------------------------------------------------------------

void __fastcall TFormReports::setDatabaseFileName(UnicodeString fina) {
	this->databaseFileName = fina;
	SQLConnection1->Params->Add("Database=" + this->databaseFileName);
	try
	{
		// Establish the connection.
		SQLConnection1->Connected = true;
		BttnExecute->Enabled = true;
		Memo1->Text = "Connection established!";
	}
	catch (EDatabaseError& E)
	{
	   ShowMessage("Exception raised with message" + E.Message);
	}    //

}

void __fastcall TFormReports::BttnSKKostenClick(TObject *Sender)
{
	//
	this->frxReport5->ShowReport();
}
//---------------------------------------------------------------------------

void __fastcall TFormReports::BttnPraesidiumClick(TObject *Sender)
{
	// to be done
    this->frxReport6->ShowReport();
}
//---------------------------------------------------------------------------


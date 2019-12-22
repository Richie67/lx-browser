//---------------------------------------------------------------------------

#include <fmx.h>
#include <string>
#include <System.IOUtils.hpp>
#include <SysUtils.hpp>
#pragma hdrstop

#include "FrmMain.h"
#include "FormBudget.h"
#include "FrmReports.h"
#include "LexwareDecoder.h"
#include "Journal.h"
#include "KontoDefinition.h"
#include "Kostenstellen.h"
#include "juldat.h"
#include "JournalExporter.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    this->ignoreOnClick = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnLoadClick(TObject *Sender)
{
	//
	this->Memo1->Lines->Clear();
	doGenerateDataStructures(this->Memo1, this->ComboBox1);
	doGenerateJournal(this->Memo1);
	doGenerateKontenRahmen(this->Memo1);
	AllMatcher matcher;
	filter.doFiler(matcher);
	fillStringGrid();
	Kostenstellen &kostenstellen = Kostenstellen::instance();
	kostenstellen.fillComboBox(this->ComboKst1);
	kostenstellen.fillComboBox(this->ComboKst2);
	KontenRahmen &konten = KontenRahmen::instance();
	konten.fillComboBox(this->ComboKtoSoll);
    konten.fillComboBox(this->ComboKtoHaben);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::fillStringGrid() {
	// this->StringGrid1->Row = 5;
	// this->StringGrid1->Col = 5;

	Journal &journal = Journal::instance();
	// int count = journal.getCount();
	int count = filter.getCount();
	StringGrid1->RowCount = count;
	StringGrid1->Columns[0]->Header = "Nr";
	StringGrid1->Columns[1]->Header = "Soll";
	StringGrid1->Columns[2]->Header = "Haben";
	StringGrid1->Columns[3]->Header = "Text";
	StringGrid1->Columns[4]->Header = "Kst 1";
	StringGrid1->Columns[5]->Header = "Kst 2";
	StringGrid1->Columns[6]->Header = "Betrag";
	StringGrid1->Columns[7]->Header = "Datum";
	StringGrid1->Columns[8]->Header = "idx";
	StringGrid1->Columns[9]->Header = "Beleg";
	for (int i = 0; i < count; i++) {
		try {
			// JournalItem &item = journal.getItem(i);
            JournalItem &item = filter.getItem(i);
			AnsiString us;
			int lNr = item.getLNr();
			us.printf("%d", lNr);
			StringGrid1->Cells[0][i] = us;
			us.printf("%04d", item.getLSoll());
			StringGrid1->Cells[1][i] = us;
			us.printf("%04d", item.getLHaben());
			StringGrid1->Cells[2][i] = us;
			std::string strText = item.getStrText();
			us.printf("%s", strText.c_str());
			StringGrid1->Cells[3][i] = us;
			us.printf("%04d", item.getLKost1());
			StringGrid1->Cells[4][i] = us;
			us.printf("%04d", item.getLKost2());
			StringGrid1->Cells[5][i] = us;
			us.printf("%5.2f", item.getDftNetto());
			StringGrid1->Cells[6][i] = us;
			std::string date = convertToDate(item.getDatBeleg());
			us.printf("%s", date.c_str());
			StringGrid1->Cells[7][i] = us;
			int iZaehler = item.getIZaehler();
			us.printf("%d", iZaehler);
			StringGrid1->Cells[8][i] = us;
			us.printf("%d-%d-%s", item.getLBelegNr(), item.getIBelegKreis(), item.getStrBelegNr().c_str());
			// int iBelegNo = item.getLBelegNr();
			// us.printf("%d", iBelegNo);
            StringGrid1->Cells[9][i] = us;
		} catch (std::invalid_argument &e) {

		}
	}
}

void __fastcall TForm1::updateKostenstellenEdit(TEdit *pEdit, Kostenstellen &kostenstellen, int idKst) {
	std::string strKost = kostenstellen.findName(idKst);
	pEdit->Text = strKost.c_str();
}


void __fastcall TForm1::fillDetailView(int row) {
	//
	Journal &journal = Journal::instance();
	KontenRahmen &konten = KontenRahmen::instance();
	Kostenstellen &kostenstellen = Kostenstellen::instance();
	int count = journal.getCount();
	this->ignoreOnClick = true;
	if (row >= 0 && row < count) {

		try {
			// JournalItem &item = journal.getItem(row);
			JournalItem &item = filter.getItem(row);
			//
			int lNr = item.getLNr();
			UnicodeString us;
			us.printf(L"%d", lNr);
			this->EdBuchungsNr->Text = us;
			//
			std::string strText = item.getStrText();
			this->EdBuchungsText->Text = strText.c_str();
			//
			int lSoll = item.getLSoll();
			us.printf(L"%d", lSoll);
			this->EdSollKtoNr->Text = us;
			//
			int lHaben = item.getLHaben();
			us.printf(L"%d", lHaben);
			this->EdHabenKtoNr->Text = us;
			//
			Konto &kontoSoll = konten.findKonto(lSoll);
			std::string strSoll = kontoSoll.getStrName();
			this->EdSollKtoName->Text = strSoll.c_str();
			//
			Konto &kontoHaben = konten.findKonto(lHaben);
			std::string strHaben = kontoHaben.getStrName();
			this->EdHabenKtoName->Text = strHaben.c_str();
			//
			int datBuchung = item.getDatBuchung();
			us.printf(L"%d", datBuchung);
			this->EdDatumBuchung->Text = us;
			//
			double betragNetto = item.getDftNetto();
			us.printf(L"%5.2f", betragNetto);
			this->EdBetragNetto->Text = us;
			//
			int idKst1 = item.getLKost1();
			updateKostenstellenEdit(this->EdKostenstelle1, kostenstellen, idKst1);
			// std::string strKost1 = kostenstellen.findName(idKst1);
			// this->EdKostenstelle1->Text = strKost1.c_str();
			int idKst2 = item.getLKost2();
			updateKostenstellenEdit(this->EdKostenstelle2, kostenstellen, idKst2);
			// std::string strKost2 = kostenstellen.findName(idKst2);
			// this->EdKostenstelle2->Text = strKost2.c_str();

			// mark the checkboxes (returns -1 if not found)
			this->ComboKst1->ItemIndex = kostenstellen.findIndex(idKst1);
			this->ComboKst2->ItemIndex = kostenstellen.findIndex(idKst2);
			//
			//
			this->ComboKtoSoll->ItemIndex = konten.findIndex(kontoSoll);
			this->ComboKtoHaben->ItemIndex = konten.findIndex(kontoHaben);
			//
			std::string date = convertToDate(item.getDatBuchung());
			this->EdDatumBuchung->Text = date.c_str();
			//
			std::string date2 = convertToDate(item.getDatBeleg());
			this->EdDatumBeleg->Text = date2.c_str();

			// fill the model
			model.clear();
			model.setId(item.getLNr());
			// TODO
			model.setIdx(item.getIZaehler());
			model.setKostenstelle1(item.getLKost1());
			model.setKostenstelle2(item.getLKost2());
			model.setKontoSoll(item.getLSoll());
			model.setKontoHaben(item.getLHaben());
		} catch (std::invalid_argument &e) {
			throw new ERangeError(e.what());
		}
	}
	this->ignoreOnClick = false;
	update();
}

void __fastcall TForm1::StringGrid1CellClick(TColumn * const Column, const int Row)

{
	this->BttnSave->Enabled = false;
	fillDetailView(Row);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnLogKontenClick(TObject *Sender)
{
	//
	KontenRahmen &konten = KontenRahmen::instance();
	this->Memo1->Lines->Clear();
	konten.dumpIntoMemo(this->Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1SelChanged(TObject *Sender)
{
	//
	int row = this->StringGrid1->Row;
	if (row >= 0) {
		this->BttnSave->Enabled = false;
		fillDetailView(row);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnDatumClick(TObject *Sender)
{
	//
	// long number = 132188163;
	// double dblNumber = number;
	// double dblJuldat;
	// int iYear = 2017;
	// int iMonth = 8;
	// int iDay = 2;
	// GregorianDateToJulianDate(iYear, iMonth, iDay, &dblJuldat);
	// double result = dblNumber - dblJuldat;
	// long lResult = floor(result);
	// long lJuldat = floor(dblJuldat);
	// char st[256];
	// snprintf(st, 255, "%10.3f %10.3f %10.3f", dblNumber, dblJuldat, result);
	// this->Memo1->Lines->Add(st);

	// snprintf(st, 255, "%10ld  %10ld  %10ld", number, lJuldat, number - lJuldat);
	// this->Memo1->Lines->Add(st);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnKostenstellenClick(TObject *Sender)
{
	//
	Kostenstellen &kostenstellen = Kostenstellen::instance();
	this->Memo1->Lines->Clear();
	kostenstellen.dumpIntoMemo(this->Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnSaveClick(TObject *Sender)
{
	// do the save here ...
	int no = model.getId();
    int idx = model.getIdx();
	int idKst1 = model.getKostenstelle1();
	int idKst2 = model.getKostenstelle2();
	Kostenstellen &kostenstellen = Kostenstellen::instance();
	if (idKst1 >= 0 && idKst2 >= 0) {
		updateKostenstellen(no, idx, idKst1, idKst2, this->Memo1);
	} else {
		ShowMessage("Kostenstellen wurden nicht geändert!");
	}
	int ktoSoll = model.getKontoSoll();
	int ktoHaben = model.getKontoHaben();
	if (ktoSoll > 0 || ktoHaben > 0) {
		updateJournalRecordKonto(no, idx, ktoSoll, ktoHaben, this->Memo1);
	} else {
		ShowMessage("Kontenzuordnung wurde nicht geändert!");
	}
	model.setChanged(false);
	// update the journal
	Journal &journal = Journal::instance();
	try {
		JournalItem &item = journal.find(no, idx);
		item.setLSoll(ktoSoll);
		item.setLHaben(ktoHaben);
		item.setLKost1(idKst1);
		item.setLKost2(idKst2);
	}
	catch (std::invalid_argument &e) {
        // do nothing
    }
    fillStringGrid();
	update();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboKst1Change(TObject *Sender)
{
	//
	if (!this->ignoreOnClick) {
		this->Memo1->Lines->Add("ComboKst1Changed");
		int sel = this->ComboKst1->ItemIndex;
		if (sel >= 0) {
			Kostenstellen &kostenstellen = Kostenstellen::instance();
			int kst = kostenstellen.findKostenstelle(sel);
			int idKst = kostenstellen.findKostenstellenKey(kst);
			if (idKst >= 0) {
				this->model.setKostenstelle1(idKst);
				this->model.setChanged(true);
				updateKostenstellenEdit(this->EdKostenstelle1, kostenstellen, idKst);
				update();
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboKst2Change(TObject *Sender)
{
	if (!this->ignoreOnClick) {
		this->Memo1->Lines->Add("ComboKst2Changed");
		int sel = this->ComboKst2->ItemIndex;
		if (sel >= 0) {
			Kostenstellen &kostenstellen = Kostenstellen::instance();
			this->model.setKostenstelle2(kostenstellen.findKostenstelle(sel));
			this->model.setChanged(true);
			update();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnClearClick(TObject *Sender)
{
	//
	this->Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::update() {
	this->BttnSave->Enabled = model.isChanged();
}


void __fastcall TForm1::BttnDeleteClick(TObject *Sender)
{
	// TOBEDONE
	int no = model.getId();

	deleteJournalRecord(no, this->Memo1);

	model.setChanged(false);
	update();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboKtoSollChange(TObject *Sender)
{
	//
	if (!this->ignoreOnClick) {
		this->Memo1->Lines->Add("ComboKontoSollChanged");
		int sel = this->ComboKtoSoll->ItemIndex;
		if (sel >= 0) {
			KontenRahmen &konten = KontenRahmen::instance();
			int ktoNr = konten.findKontoByListPosition(sel);
			Konto &konto = konten.findKonto(ktoNr);
			this->model.setKontoSoll(konto.getLNr());
			this->model.setChanged(true);
			UnicodeString us;
			int lkto = konto.getLNr();
			us.printf(L"%d", lkto);
			this->EdSollKtoNr->Text = us;
			std::string strKto = konto.getStrName();
			this->EdSollKtoName->Text = strKto.c_str();
			update();
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboKtoHabenChange(TObject *Sender)
{
	//
	if (!this->ignoreOnClick) {
		this->Memo1->Lines->Add("ComboKontoHabenChanged");
		int sel = this->ComboKtoHaben->ItemIndex;
		if (sel >= 0) {
			KontenRahmen &konten = KontenRahmen::instance();
			int KtoNr = konten.findKontoByListPosition(sel);
			Konto &konto = konten.findKonto(KtoNr);
			this->model.setKontoHaben(konto.getLNr());
			this->model.setChanged(true);
			UnicodeString us;
			int lkto = konto.getLNr();
			us.printf(L"%d", lkto);
			this->EdHabenKtoNr->Text = us;
			std::string strKto = konto.getStrName();
			this->EdHabenKtoName->Text = strKto.c_str();
			update();
		}
	}
}
//---------------------------------------------------------------------------

static bool isBestandskonto(long kto) {
	if ((kto >= 0 && kto <= 1999) || (kto >= 9000 && kto <= 9999)) {
		return true;
	}
	return false;
}


static bool isErfolgskonto(long kto) {
	if (kto >= 2000 && kto <= 8999) {
		return true;
	}
	return false;
}


static bool isKontokorrentKonto(long kto) {
	if (kto >= 10000 && kto <= 99999) {
		return true;
	}
	return false;
}

void __fastcall TForm1::BttnMissingKStClick(TObject *Sender)
{
	// TODO
	Journal &journal = Journal::instance();
	KontenRahmen &konten = KontenRahmen::instance();
	int count = journal.getCount();
	for (int i = 0; i < count; i++) {
		try {
			JournalItem &item = journal.getItem(i);
			Kostenstellen &kostenstellen = Kostenstellen::instance();
			long ktoSoll = item.getLSoll();
			long ktoHaben = item.getLHaben();
			long kst1 = item.getLKost1();
			long kst2 = item.getLKost2();
			bool isOk = false;
			if (isBestandskonto(ktoSoll) && isErfolgskonto(ktoHaben)) {
				if (kst1 != 0 && kst2 == 0) {
					// if (kostenstellen.indexExists(kst1)) {
						isOk = true;
					// }
				}
			}
			if (isErfolgskonto(ktoSoll) && isBestandskonto(ktoHaben)) {
				if (kst1 != 0 && kst2 == 0) {
					// if (kostenstellen.indexExists(kst1)) {
						isOk = true;
					// }
				}
			}
			if (isBestandskonto(ktoSoll) && isBestandskonto(ktoHaben)) {
				if (kst1 == 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (isErfolgskonto(ktoSoll) && isErfolgskonto(ktoHaben)) {
				if (kst1 == 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (isKontokorrentKonto(ktoSoll) && isBestandskonto(ktoHaben)) {
				if (kst1 == 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (isBestandskonto(ktoSoll) && isKontokorrentKonto(ktoHaben)) {
				if (kst1 == 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (isKontokorrentKonto(ktoSoll) && isErfolgskonto(ktoHaben)) {
				if (kst1 != 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (isErfolgskonto(ktoSoll) && isKontokorrentKonto(ktoHaben)) {
				if (kst1 != 0 && kst2 == 0) {
					isOk = true;
				}
			}
			if (!isOk) {
				int stop = i;
				i = count;
                this->StringGrid1->Selected = stop;
            }
		} catch (std::invalid_argument &e) {

		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnKtoChkClick(TObject *Sender)
{
	//
	KontenRahmen &konten = KontenRahmen::instance();
	konten.clearStateUsed();
	Journal &journal = Journal::instance();
	int count = journal.getCount();
	for (int i = 0; i < count; i++) {
        JournalItem item = journal.getItem(i);
		long ktoSoll = item.getLSoll();
		long ktoHaben = item.getLHaben();
		konten.setStateUsed(ktoSoll, true);
		konten.setStateUsed(ktoHaben, true);
	}
	this->Memo1->Lines->Clear();
	konten.dumpAccountState(this->Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnExportClick(TObject *Sender)
{
	// TODO
	if (this->SaveDialog1->Execute()) {
		ShowMessage("Execute the save command: " + this->SaveDialog1->FileName);
		Journal &journal = Journal::instance();
		KontenRahmen &konten = KontenRahmen::instance();
		Kostenstellen &kostenstellen = Kostenstellen::instance();
		// Batch &batch = Batch::instance();
		// this->SaveDialog1->FileName;
		exportJournalToDatabase(this->SaveDialog1->FileName, journal, konten, kostenstellen, this->Memo1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItemFileClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnFilterClearClick(TObject *Sender)
{
	AllMatcher matcher;
	filter.doFiler(matcher);
	fillStringGrid();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BttenFilterKontenClick(TObject *Sender)
{
	int x = 956;
	String s = this->EdFilter->Text;
	if (s.Length() > 0) {
		x = StrToInt(s);
		AccountMatcher matcher;
		matcher.setAccount(x);
		filter.doFiler(matcher);
		fillStringGrid();
	} else {
		ShowMessage("Bitte Kontonummer angeben");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnFilterCostUnitClick(TObject *Sender)
{
	int x = 956;
	String s = this->EdFilter->Text;
	if (s.Length() > 0) {
		x = StrToInt(s);
		Kostenstellen &kostenstellen = Kostenstellen::instance();
		int costUnitKey = kostenstellen.findKostenstellenKey(x);
		CostUnitMatcher matcher;
		matcher.setCostUnit(costUnitKey);
		filter.doFiler(matcher);
		fillStringGrid();
	} else {
		ShowMessage("Bitte Kontonummer angeben");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnAmountClick(TObject *Sender)
{
	double x = 0.0;
	String s = this->EdFilter->Text;
	if (s.Length() > 0) {
		x = StrToFloat(s);
		Kostenstellen &kostenstellen = Kostenstellen::instance();
		AmountMatcher matcher;
		matcher.setAmount(x);
		filter.doFiler(matcher);
		fillStringGrid();
	} else {
		ShowMessage("Bitte Betrag angeben");
	}


}
//---------------------------------------------------------------------------

void __fastcall TForm1::BttnBudgetClick(TObject *Sender)
{
	FrmBudget->loadFromRegistry();
	if (FrmBudget->ShowModal() == mrOk) {
		// MessageBox(0, L"Hello", L"Hello", MB_OK);
		FrmBudget->saveToRegistry();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuItem2Click(TObject *Sender)
{
	UnicodeString tempFile = System::Ioutils::TPath::GetTempFileName();
	disableControls();

	this->Memo1->Lines->Add("Output file is " + tempFile);

	Journal &journal = Journal::instance();
	KontenRahmen &konten = KontenRahmen::instance();
	Kostenstellen &kostenstellen = Kostenstellen::instance();

	exportJournalToDatabase(tempFile, journal, konten, kostenstellen, this->Memo1);

    FormReports->setDatabaseFileName(tempFile);
	FormReports->Show();

	enableControls();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::disableControls() {
    lockControls(false);
}

void __fastcall TForm1::enableControls() {
	lockControls(true);
}


void __fastcall TForm1::lockControls(bool enabled) {
	this->BttnAmount->Enabled = enabled;
	this->BttnBudget->Enabled = enabled;
	this->BttnClear->Enabled = enabled;
	this->BttnDatum->Enabled = enabled;
	this->BttnDelete->Enabled = enabled;
	this->BttnExport->Enabled = enabled;
	this->BttnFilterClear->Enabled = enabled;
	this->BttnFilterCostUnit->Enabled = enabled;
	this->BttnJournal->Enabled = enabled;
	this->BttnKostenstellen->Enabled = enabled;
	this->BttnKtoChk->Enabled = enabled;
	this->BttnLoad->Enabled = enabled;
	this->BttnLogKonten->Enabled = enabled;
	this->BttnMissingKSt->Enabled = enabled;
	this->BttnSave->Enabled = enabled;
}


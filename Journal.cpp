//---------------------------------------------------------------------------

#pragma hdrstop

#include "Journal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void Journal::clear() {
	this->journal.clear();
}


void Journal::add(const JournalItem &journalItem) {
	this->journal.push_back(journalItem);
}

void Journal::dumpIntoMemo(TMemo *pMemo) {
	for (std::vector<JournalItem>::iterator it = journal.begin(); it != journal.end(); ++it) {
		pMemo->Lines->Add(it->toAnsiString());
	}
}


int  Journal::getCount() {
	return journal.size();
}




JournalItem &Journal::getItem(int i) {
	if (i >= 0 && i < journal.size()) {
		return journal.at(i);
	}
	throw std::invalid_argument("Journal::getItem");
}


JournalItem &Journal::find(int no, int idx) {
	for (std::vector<JournalItem>::iterator it = journal.begin(); it != journal.end(); ++it) {
		if (it->getLNr() == no && it->getIZaehler() == idx) {
			return *it;
		}
	}
	throw std::invalid_argument("Journal::find");
}


void Journal::saveChanges() {

}


bool Journal::isModified() {
	bool modified = false;
	for (std::vector<JournalItem>::iterator it = journal.begin(); it != journal.end(); ++it) {
		if (it->isModified()) {
			modified = true;
			break;
		}
	}
	return modified;
}


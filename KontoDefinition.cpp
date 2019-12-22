//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "KontoDefinition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void KontenRahmen::clear() {
	this->konten.clear();
}


void KontenRahmen::add(const Konto &konto) {
	this->konten.push_back(konto);
}


void KontenRahmen::dumpIntoMemo(TMemo *pMemo) {
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		pMemo->Lines->Add(it->toString());
	}
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		pMemo->Lines->Add(it->toCSVString());
	}
}

Konto &KontenRahmen::findKonto(int no) {
	// for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
	//	if (it->getLNr() == no) {
	//		return *it;
	//	}
	// }
	for (int i = 0; i < konten.size(); i++) {
		Konto &konto = konten.at(i);
		if (konto.getLNr() == no) {
			return konto;
		}
	}
	char st[256];
	memset(st, 0, sizeof(st));
	snprintf(st, 255, "Konto %d kann nicht gefunden werden!", no);
	throw std::invalid_argument(st);
}



int KontenRahmen::findIndex(int no) {
	int result = -1;
	int i = 0;
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {

		if ((*it).getLNr() == no) {
			result = i;
			break;
		}
		i++;
	}
	return result;

}


int KontenRahmen::findIndex(Konto &konto) {
	return findIndex(konto.getLNr());
}


void KontenRahmen::fillComboBox(TComboBox *pComboBox) {
	pComboBox->Items->Clear();
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		pComboBox->Items->Add(it->toString());
	}
}


int KontenRahmen::findKontoByListPosition(int sel) {
	std::vector<Konto>::iterator it = konten.begin();
	for (int i = 0; i < sel; i++) {
		++it;
	}
	if (it != konten.end()) {
		return (*it).getLNr();
	}
	return -1;
}


void KontenRahmen::clearStateUsed() {
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		it->setUsed(false);
	}
}


void KontenRahmen::setStateUsed(int kto, bool used) {
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		if (it->getLNr() == kto) {
			it->setUsed(used);
			break;
		}
	}
}


void KontenRahmen::dumpAccountState(TMemo *pMemo) {
	for (std::vector<Konto>::iterator it = konten.begin(); it != konten.end(); ++it) {
		bool u1 = it->isFBebucht();
		bool u2 = it->isUsed();
		if (u1 != u2) {
			pMemo->Lines->Add(it->toString());
		}

	}
}


int  KontenRahmen::getCount() {
    return this->konten.size();
}


Konto &KontenRahmen::getItem(int i) {
	if (i >= 0 && i < konten.size()) {
		return konten.at(i);
	}
	throw std::invalid_argument("KostenRahmen::getItem");

}


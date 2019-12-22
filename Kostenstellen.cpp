//---------------------------------------------------------------------------

#pragma hdrstop

#include "Kostenstellen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void Kostenstellen::clear() {
	this->kostenstellen.clear();
}


void Kostenstellen::add(const Kostenstelle &kostenstelle) {
	this->kostenstellen.push_back(kostenstelle);
}


void Kostenstellen::fillComboBox(TComboBox *pComboBox) {
	pComboBox->Items->Clear();
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {
		pComboBox->Items->Add(it->toString());
	}
}


void Kostenstellen::dumpIntoMemo(TMemo *pMemo) {
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {
		pMemo->Lines->Add(it->toString());
	}
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {
		pMemo->Lines->Add(it->toCSVString());
	}

}


Kostenstelle &Kostenstellen::find(int id) {
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {
		if ((*it).getIIndex() == id) {
			return *it;
		}
	}
	char st[256];
	memset(st, 0, sizeof(st));
	snprintf(st, 255, "Kostenstelle %d kann nicht gefunden werden!", id);
	throw std::invalid_argument(st);
}


std::string Kostenstellen::findName(int id) {
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {
		if ((*it).getIIndex() == id) {
			return it->getName();
		}
	}
	char st[256];
	memset(st, 0, sizeof(st));
	snprintf(st, 255, "keine Kst [%d]", id);
	return std::string(st);
}

int Kostenstellen::findIndex(int kst) {
	int result = -1;
	int i = 0;
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {

		if ((*it).getIIndex() == kst) {
			result = i;
			break;
		}
		i++;
	}
	return result;
}


int Kostenstellen::findKostenstelle(int index) {
	int i = index;
	int n = kostenstellen[i].getNo();
	return n;
}


int Kostenstellen::findKostenstellenKey(int kst) {
	int result = -1;
	int i = 0;
	for (std::vector<Kostenstelle>::iterator it = kostenstellen.begin(); it != kostenstellen.end(); ++it) {

		if ((*it).getNo() == kst) {
			result = (*it).getIIndex();
			break;
		}
		i++;
	}
	return result;
}


bool Kostenstellen::exists(int kst) {
	bool result = false;
	if (findKostenstellenKey(kst) >= 0) {
		result = true;
	}
	return result;
}



int  Kostenstellen::getCount() {
	return kostenstellen.size();
}




Kostenstelle &Kostenstellen::getItem(int i) {
	if (i >= 0 && i < kostenstellen.size()) {
		return kostenstellen.at(i);
	}
	throw std::invalid_argument("Kostenstellen::getItem");
}



//---------------------------------------------------------------------------

#include <stdlib.h>
#pragma hdrstop

#include "ModelMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


	void ModelJournal::clear() {
		this->id = 0;
		this->idx = 0;
		this->kostenstelle1 = 0;
		this->kostenstelle2 = 0;
		this->kontoSoll = 0;
		this->kontoHaben = 0;
		this->changed = false;
	}


	void ModelJournal::setId(int id) {
		this->id = id;
	}


	int ModelJournal::getId() {
		return this->id;
	}


	void ModelJournal::getId(int *id) {
		if (id != NULL) {
			*id = this->id;
		}
	}


	void ModelJournal::getId(int &id) {
		id = this->id;
	}


	void ModelJournal::setIdx(int idx) {
		this->idx = idx;
	}


	int ModelJournal::getIdx() {
		return this->idx;
	}

	void ModelJournal::getIdx(int *idx) {
		if (idx != NULL) {
			*idx = this->idx;
		}
	}


	void ModelJournal::getIdx(int &idx) {
		idx = this->idx;
	}

	//
	void ModelJournal::setKostenstelle1(int kst1) {
		this->kostenstelle1 = kst1;
	}


	int ModelJournal::getKostenstelle1() {
		return this->kostenstelle1;
	}


	void ModelJournal::getKostenstelle1(int *kst1) {
		if (kst1 != NULL) {
			*kst1 = this->kostenstelle1;
		}
	}


	void ModelJournal::getKostenstelle1(int &kst1) {
		kst1 = this->kostenstelle1;
	}


	//
	void ModelJournal::setKostenstelle2(int kst2) {
		this->kostenstelle2 = kst2;
	}


	int ModelJournal::getKostenstelle2() {
		return this->kostenstelle2;
	}


	void ModelJournal::getKostenstelle2(int *kst2) {
		if (kst2 != NULL) {
			*kst2 = this->kostenstelle2;
		}
	}


	void ModelJournal::getKostenstelle2(int &kst2) {
		kst2 = this->kostenstelle2;
	}


	void ModelJournal::setKontoSoll(int soll) {
		this->kontoSoll = soll;
	}


	int ModelJournal::getKontoSoll() {
		return this->kontoSoll;
	}


	void ModelJournal::getKontoSoll(int *soll) {
		if (soll != NULL) {
            *soll = this->kontoSoll;
        }
	}


	void ModelJournal::getKontoSoll(int &soll) {
		soll = this->kontoSoll;
	}


	//
	void ModelJournal::setKontoHaben(int haben) {
		this->kontoHaben = haben;
	}


	int ModelJournal::getKontoHaben() {
		return this->kontoHaben;
	}


	void ModelJournal::getKontoHaben(int *haben) {
		if (haben != NULL) {
			*haben = this->kontoHaben;
		}
	}


	void ModelJournal::getKontoHaben(int &haben) {
		haben = this->kontoHaben;
	}


	//
	void ModelJournal::setChanged(bool changed) {
		this->changed = changed;
	}


	bool ModelJournal::isChanged() {
		return this->changed;
	}


	void ModelJournal::isChanged(bool *pChanged) {
		if (pChanged != NULL) {
			*pChanged = this->changed;
		}
	}


	void ModelJournal::isChanged(bool &changed) {
		changed = this->changed;
	}




	//
	void ModelJournal::save() {

	}


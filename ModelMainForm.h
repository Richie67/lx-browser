//---------------------------------------------------------------------------

#ifndef ModelMainFormH
#define ModelMainFormH
//---------------------------------------------------------------------------

class ModelJournal {
private :
	int id;
	int idx;
	int kostenstelle1;
	int kostenstelle2;
	int kontoSoll;
	int kontoHaben;
	bool changed;
public :
	void clear();
	//
	void setId(int id);
	int getId();
	void getId(int *id);
	void getId(int &id);
	//
	void setIdx(int idx);
	int getIdx();
	void getIdx(int *idx);
	void getIdx(int &idx);
	//
	void setKostenstelle1(int kst1);
	int getKostenstelle1();
	void getKostenstelle1(int *kst1);
	void getKostenstelle1(int &kst1);
	//
	void setKostenstelle2(int kst2);
	int getKostenstelle2();
	void getKostenstelle2(int *kst2);
	void getKostenstelle2(int &kst2);
	//
	void setKontoSoll(int soll);
	int getKontoSoll();
	void getKontoSoll(int *soll);
	void getKontoSoll(int &soll);
	//
	void setKontoHaben(int haben);
	int getKontoHaben();
	void getKontoHaben(int *haben);
    void getKontoHaben(int &haben);
	//
	void setChanged(bool changed);
	bool isChanged();
	void isChanged(bool *pChanged);
	void isChanged(bool &changed);
	//
    void save();
};

#endif

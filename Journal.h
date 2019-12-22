//---------------------------------------------------------------------------

#ifndef JournalH
#define JournalH
#include <fmx.h>
#include <vector>
#include <string>
#include <stdint.h>

//---------------------------------------------------------------------------

class JournalItem {
private:
	int32_t     lNr;
	int32_t		datBuchung;
	int32_t	   	datBeleg;
	int16_t		iBelegKreis;
	int32_t		lBelegNr;
	std::string strBelegNr;
	int16_t		iZaehler;
	int16_t		iStatus;
	std::string strText;
	int32_t		lSoll;
	int32_t		lHaben;
	int32_t		lUst;
	int16_t		iWaehrung;
	double		dftTageskurs;
	double		dftNetto;
	double		dftUst;
	int32_t		lUstNr;
	int32_t		lBezug;
	double		dftUstProz;
	int16_t		iUstArt;
	int32_t		lKost1;
	int32_t		lKost2;
	int16_t		iOPJahr;
	int16_t		iStatusSperre;
	int16_t		iStatusAbschluss;
	int16_t		iStatusAbgleich;
	int32_t		lTaxCase;
	bool        modified;

public:

	JournalItem() {
    		this->lNr = 0;
		this->datBuchung = 0;
		this->datBeleg = 0;
		this->iBelegKreis = 0;
		this->lBelegNr = 0;
		this->strBelegNr = "";
		this->iZaehler = 0;
		this->iStatus = 0;
		this->strText = "";
		this->lSoll = 0;
		this->lHaben = 0;
		this->lUst = 0;
		this->iWaehrung = 0;
		this->dftTageskurs = 0.0;
		this->dftNetto = 0.0;
		this->dftUst = 0.0;
		this->lUstNr = 0;
		this->lBezug = 0;
		this->dftUstProz = 0.0;
		this->iUstArt = 0;
		this->lKost1 = 0;
		this->lKost2 = 0;
		this->iOPJahr = 0;
		this->iStatusSperre = 0;
		this->iStatusAbschluss = 0;
		this->iStatusAbgleich = 0;
		this->lTaxCase = 0;
        this->modified = false;
	}


	void setLNr(int32_t lNr) {
		this->lNr = lNr;
	}

	void setDatBuchung(int32_t datBuchung) {
		this->datBuchung = datBuchung;
	}

	void setDatBeleg(int32_t datBeleg) {
		this->datBeleg = datBeleg;
	}

	void setIBelegKreis(int16_t iBelegKreis) {
		this->iBelegKreis = iBelegKreis;
	}


	void setLBelegNr(int32_t lBelegNr) {
		this->lBelegNr = lBelegNr;
	}

	void setStrBelegNr(std::string strBelegNr) {
		this->strBelegNr = strBelegNr;
	}

	void setIZaehler(int16_t iZaehler) {
		this->iZaehler = iZaehler;
	}

    void setIStatus(int16_t		iStatus) {
		this->iStatus = iStatus;
	}

	void setStrText(std::string strText) {
		this->strText = strText;
	}

	void setLSoll(int32_t		lSoll) {
		this->lSoll = lSoll;
		this->modified = true;
	}

	void setLHaben(int32_t		lHaben) {
		this->lHaben = lHaben;
		this->modified = true;
	}

	void setLUst(int32_t		lUst) {
		this->lUst = lUst;
	}


	void setIWaehrung(int16_t		iWaehrung) {
		this->iWaehrung = iWaehrung;
	}

	void setDftTageskurs(double		dftTageskurs) {
		this->dftTageskurs = dftTageskurs;
	}

	void setDftNetto(double		dftNetto) {
		this->dftNetto = dftNetto;
	}

	void setDftUst(double		dftUst) {
		this->dftUst = dftUst;
	}

	void setLUstNr(int32_t		lUstNr) {
		this->lUstNr = lUstNr;
	}


	void setLBezug(int32_t		lBezug) {
		this->lBezug = lBezug;
	}

	void setDftUstProz(double		dftUstProz) {
		this->dftUstProz = dftUstProz;
	}


	void setIUstArt(int16_t		iUstArt) {
		this->iUstArt = iUstArt;
	}


	void setLKost1(int32_t		lKost1) {
		this->lKost1 = lKost1;
		this->modified = true;
	}

	void setLKost2(int32_t		lKost2) {
		this->lKost2 = lKost2;
        this->modified = true;
	}

	void setIOPJahr(int16_t		iOPJahr) {
		this->iOPJahr = iOPJahr;
	}


	void setIStatusSperre(int16_t		iStatusSperre) {
		this->iStatusSperre = iStatusSperre;
	}


	void setIStatusAbschluss(int16_t		iStatusAbschluss) {
		this->iStatusAbschluss = iStatusAbschluss;
	}


	void setIStatusAbgleich(int16_t		iStatusAbgleich) {
        this->iStatusAbgleich = iStatusAbgleich;
    }


	void setLTaxCase(int32_t		lTaxCase) {
        this->lTaxCase= lTaxCase;
    }


	int32_t     getLNr() {
		return this->lNr;
	}


	int32_t		getDatBuchung() {
		return this->datBuchung;
	}


	int32_t	   	getDatBeleg() {
		return this->datBeleg;
	}


	int16_t		getIBelegKreis() {
		return this->iBelegKreis;
	}


	int32_t		getLBelegNr() {
		return this->lBelegNr;
	}

	std::string getStrBelegNr() {
		return this->strBelegNr;
	}

	int16_t		getIZaehler() {
		return this->iZaehler;
	}

	int16_t		getIStatus() {
		return this->iStatus;
	}

	std::string getStrText() {
		return this->strText;
	}

	int32_t		getLSoll() {
		return this->lSoll;
	}

	int32_t		getLHaben() {
		return this->lHaben;
	}

	int32_t		getLUst() {
		return this->lUst;
	}

	int16_t		getIWaehrung();

	double		getDftTageskurs();

	double		getDftNetto() {
		return this->dftNetto;
	}

	double		getDftUst();
	int32_t		getLUstNr();
	int32_t		getLBezug();
	double		getDftUstProz();
	int16_t		getIUstArt();

	int32_t		getLKost1() {
		return this->lKost1;
	}


	int32_t		getLKost2() {
		return this->lKost2;
	}


	int16_t		getIOPJahr() {
		return this->iOPJahr;
	}


	int16_t		getIStatusSperre() {
		return this->iStatusSperre;
	}


	int16_t		getIStatusAbschluss() {
		return this->iStatusAbschluss;
	}


	int16_t		getIStatusAbgleich() {
		return this->iStatusAbgleich;
	}


	int32_t		getLTaxCase() {
		return this->lTaxCase;
	}


	bool        isModified() {
		return this->modified;
	}

	void        setModified(bool modified) {
		this->modified = modified;
	}


	AnsiString toAnsiString() {
		AnsiString as;
		as.printf("lNr=%4d strText=%-30s strBelegNr=%-11s lSoll=%4d lHaben=%4d lUst=%4d lKost1=%4d lKost2=%4d dftNetto=%4.2f modified=%s",
			lNr,
			strText.c_str(),
			strBelegNr.c_str(),
			lSoll,
			lHaben,
            lUst,
			lKost1,
			lKost2,
			dftNetto,
			(modified ? "true" : "false"));
		return as;
	}


 };


class Journal {
private:
	std::vector<JournalItem> journal;

public:
	static Journal& instance() {
	   static Journal _instance;
	   return _instance;
	}
	~Journal() {}
	void xyz();
	void clear();
	void add(const JournalItem &journalItem);
	void dumpIntoMemo(TMemo *pMemo);
	int  getCount();
	JournalItem &getItem(int i);
	JournalItem &find(int no, int idx);
	void saveChanges();
    bool isModified();
 private:
	Journal() {}           // verhindert, dass ein Objekt von außerhalb von N erzeugt wird.
					// protected, wenn man von der Klasse noch erben möchte
	Journal( const Journal& ); /* verhindert, dass eine weitere Instanz via
 Kopier-Konstruktor erstellt werden kann */
	Journal & operator = (const Journal &); //Verhindert weitere Instanz durch Kopie
 };






#endif

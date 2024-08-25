//---------------------------------------------------------------------------

#ifndef KontoDefinitionH
#define KontoDefinitionH

#include <string>
#include <vector>
#include <stdint.h>
#include <fmx.h>
#include <FMX.ComboEdit.hpp>
//---------------------------------------------------------------------------


class Konto {
	int32_t     	lNr;
	std::string 	strName;
	float           ulArt;
	float           ulTyp;
	int16_t         iAuswert_EU;
	int16_t         iAuswert_Aktiva;
	int16_t         iAuswert_Passiva;
	int16_t         iAuswert_GuV;
	int16_t         bUserKonto;
	int16_t         iUstPosNeuV4;
	int16_t         UpdateVersion;
	int16_t         iAuswert_EUR;
	double          dftParamEUR;
	int16_t         fChecked;
	int16_t         bGesperrt;
	int16_t         iAuswert_BaselII;
	int32_t         lNr_Datev;
	int16_t         fDatevAutomatik;
	int16_t         fBebucht;
	int16_t         fNegativ;
	double          dftParamDM;
	int32_t         lParam;
	int32_t         lGuVStdBilrug;

	bool            used;

public:

	Konto() {
		lNr = 0;
		strName = "";
		ulArt = 0.0f;
		ulTyp = 0.0f;
		iAuswert_EU = 0;
		iAuswert_Aktiva = 0;
		iAuswert_Passiva = 0;
		iAuswert_GuV = 0;
		bUserKonto = 0;
		iUstPosNeuV4 = 0;
		UpdateVersion = 0;
		iAuswert_EUR = 0;
		dftParamEUR = 0.0;
		fChecked = 0;
		bGesperrt = 0;
		iAuswert_BaselII = 0;
		lNr_Datev = 0;
		fDatevAutomatik = 0;
		fBebucht = 0;
		fNegativ = 0;
		dftParamDM = 0.0;
		lParam = 0;
		lGuVStdBilrug = 0;

		used = false;
	};

	void setLNr(long lNr) {
		this->lNr = lNr;
	}

	void setStrName(std::string strName) {
		this->strName = strName;
	}

	long getLNr() {
		return this->lNr;
	}

	std::string getStrName() {
		return this->strName;
	}

	void setFBebucht(short bebucht) {
		this->fBebucht = bebucht;
	}

	bool isFBebucht() {
		return this->fBebucht > 0;
	}

	int getFBebucht() {
		return this->fBebucht;
	}


	bool isUsed() {
		return this->used;
	}


	void setUsed(bool used) {
		this->used = used;
	}


	AnsiString toString() {
		AnsiString as;
		as.printf("%04d %-35s %-10s", this->lNr, this->strName.c_str(), (this->fBebucht > 0 ? "bebucht" : "nicht bebucht"));
		return as;
	}

	AnsiString toCSVString() {
		AnsiString as;
		as.printf("%d;%s;%f;%f;%d;%d;%d;%d;%d", this->lNr, this->strName.c_str(), this->ulArt, this->ulTyp, this->iAuswert_EU, this->iAuswert_Aktiva, this->iAuswert_Passiva, this->iAuswert_GuV, this->fBebucht);
		return as;

	}
};


class KontenRahmen {
private:
	std::vector<Konto> konten;

public:
	static KontenRahmen& instance() {
	   static KontenRahmen _instance;
	   return _instance;
	}
	~KontenRahmen() {}
	void xyz();
	void clear();
	void add(const Konto &konto);
	void dumpIntoMemo(TMemo *pMemo);
	Konto &findKonto(int no);
	void fillComboBox(TComboBox *pComboBox);
    void fillComboEdit(TComboEdit *pComboEdit);
	int findIndex(int no);
	int findIndex(Konto &konto);
	int findKontoByListPosition(int sel);
	void clearStateUsed();
	void setStateUsed(int kto, bool used);
	void dumpAccountState(TMemo *pMemo);
	int  getCount();
	Konto &getItem(int i);
 private:
	KontenRahmen() {}           // verhindert, dass ein Objekt von außerhalb von N erzeugt wird.
					// protected, wenn man von der Klasse noch erben möchte
	KontenRahmen( const KontenRahmen& ); /* verhindert, dass eine weitere Instanz via
 Kopier-Konstruktor erstellt werden kann */
	KontenRahmen & operator = (const KontenRahmen &); //Verhindert weitere Instanz durch Kopie
 };



/*

"lNr"	"int32"		"BH_Konto"	"col0"	"-1"
"szName"	"char(80)"		"BH_Konto"	"col1"	"-1"
"ulArt"	"float32"		"BH_Konto"	"col2"	"-1"
"ulTyp"	"float32"		"BH_Konto"	"col3"	"-1"
"iAuswert_EU"	"int16"		"BH_Konto"	"col4"	"-1"
"iAuswert_Aktiva"	"int16"		"BH_Konto"	"col5"	"-1"
"iAuswert_Passiva"	"int16"		"BH_Konto"	"col6"	"-1"
"iAuswert_GuV"	"int16"		"BH_Konto"	"col7"	"-1"
"bUserKonto"	"int16"		"BH_Konto"	"col8"	"-1"
"iUStPosNeuV4"	"int16"		"BH_Konto"	"col9"	"-1"
"iUpdateVersion"	"int16"		"BH_Konto"	"data10"	"0"
"iAuswert_EUR"	"int16"		"BH_Konto"	"data10"	"2"
"dftParamEUR"	"float64"		"BH_Konto"	"data10"	"4"
"fChecked"	"int16"		"BH_Konto"	"data10"	"12"
"bGesperrt"	"int16"		"BH_Konto"	"data10"	"14"
"iAuswert_BaselII"	"int16"		"BH_Konto"	"data10"	"16"
"lNr_Datev"	"int32"		"BH_Konto"	"data11"	"0"
"fDatevAutomatik"	"int16"		"BH_Konto"	"data11"	"4"
"fBebucht"	"int16"		"BH_Konto"	"data11"	"6"
"fNegativ"	"int16"		"BH_Konto"	"data11"	"8"
"dftParamDM"	"float64"		"BH_Konto"	"data11"	"10"
"lParam"	"int32"		"BH_Konto"	"data11"	"18"
"lGuVStdBilrug"	"int32"		"BH_Konto"	"lGuVStdBilrug"	"-1"
*/


#endif

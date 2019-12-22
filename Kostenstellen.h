//---------------------------------------------------------------------------

#ifndef KostenstellenH
#define KostenstellenH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <fmx.h>

class Kostenstelle {

	std::string name;
	std::string kurz;
	int         no;
	int         iIndex;

public:

	Kostenstelle(const char * pszName, const char * pszkurz, int no, int iIndex) {
		this->name = pszName;
		this->kurz = pszkurz;
		this->no = no;
		this->iIndex = iIndex;
	}

	AnsiString toString() {
		AnsiString as;
		as.printf("%s %s %d %d", name.c_str(), kurz.c_str(), no, iIndex);
		return as;
	}

	AnsiString toCSVString() {
		AnsiString as;
		as.printf("%d;%d;%s;%s", iIndex, no, name.c_str(), kurz.c_str());
		return as;
	}


	int getNo() {
		return this->no;
	}

	std::string getName() {
		return this->name;
	}

	std::string getKurz() {
		return this->kurz;
	}

	int getIIndex() {
        return this->iIndex;
    }
 };


class Kostenstellen {
private:
	std::vector<Kostenstelle> kostenstellen;

public:
	static Kostenstellen& instance() {
	   static Kostenstellen _instance;
	   return _instance;
	}
	~Kostenstellen() {}
	void xyz();

	void clear();
	void add(const Kostenstelle &kostenstelle);
	void fillComboBox(TComboBox *pComboBox);
	void dumpIntoMemo(TMemo *pMemo);
	Kostenstelle &find(int id);
	std::string findName(int id);
	int findIndex(int kst);
	int findKostenstelle(int index);
	int findKostenstellenKey(int index);
	bool exists(int kst);
	int  getCount();
	Kostenstelle &getItem(int i);

 private:
	Kostenstellen() {}           // verhindert, dass ein Objekt von außerhalb von N erzeugt wird.
					// protected, wenn man von der Klasse noch erben möchte
	Kostenstellen( const Kostenstellen& ); /* verhindert, dass eine weitere Instanz via
 Kopier-Konstruktor erstellt werden kann */
	Kostenstellen & operator = (const Kostenstellen &); //Verhindert weitere Instanz durch Kopie
 };



#endif

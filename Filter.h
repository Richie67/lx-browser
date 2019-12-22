//---------------------------------------------------------------------------

#ifndef FilterH
#define FilterH
//---------------------------------------------------------------------------

#include "Journal.h"

class Matcher {
public:
    bool virtual match(JournalItem &item) = 0;
};

class AllMatcher : public Matcher {
public:
	bool virtual match(JournalItem &item) {
		return true;
	}
};


class AccountMatcher : public Matcher {

	int account;

public:

	void setAccount(int acc) {
		this->account = acc;
	}

	bool virtual match(JournalItem &item) {
		if (item.getLHaben() == account || item.getLSoll() == account) {
			return true;
		}
        return false;
    }
};

class CostUnitMatcher : public Matcher {

	int costUnit;

public:

	void setCostUnit(int cunit) {
		this->costUnit = cunit;
	}

	bool virtual match(JournalItem &item) {
		if (item.getLKost1() == costUnit) {
			return true;
		}
		return false;
	}
};


class AmountMatcher : public Matcher {

	double amount;

public:

	void setAmount(double a) {
		this->amount = a;
	}

	bool virtual match(JournalItem &item) {
		if (abs(item.getDftNetto() - amount) < 0.01) {
			return true;
		}
		return false;
	}
};





class Filter {
private:
	std::vector<int> vec;

public:
	~Filter() {}
	void doFiler(Matcher &matcher);
	int  getCount();
	JournalItem &getItem(int i);

 	Filter() {}           // verhindert, dass ein Objekt von außerhalb von N erzeugt wird.
					// protected, wenn man von der Klasse noch erben möchte
	Filter( const Filter& ); /* verhindert, dass eine weitere Instanz via
 Kopier-Konstruktor erstellt werden kann */
	Filter & operator = (const Filter &); //Verhindert weitere Instanz durch Kopie
 };




#endif

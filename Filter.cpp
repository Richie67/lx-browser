//---------------------------------------------------------------------------

#pragma hdrstop

#include "Filter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)




JournalItem &::Filter::getItem(int i) {
	Journal &journal = Journal::instance();
	if (i >= 0 && i < vec.size()) {
		int x = vec.at(i);
		return journal.getItem(x);
	}
	throw std::invalid_argument("Filter::getItem");
}


int  ::Filter::getCount() {
	return vec.size();
}


void ::Filter::doFiler(Matcher &matcher) {
	Journal &journal = Journal::instance();
	int x = journal.getCount();
	this->vec.clear();
	for (int i = 0; i < x; i++) {
		JournalItem &item = journal.getItem(i);
		if (matcher.match(item)) {
            this->vec.push_back(i);
		}
	}
}

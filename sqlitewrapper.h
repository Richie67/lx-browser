//---------------------------------------------------------------------------

#ifndef sqlitewrapperH
#define sqlitewrapperH

#include <string>
#include "sqlite3.h"

//---------------------------------------------------------------------------

class sqlitewrapper {
private:
	std::string name;

public:
	sqlitewrapper(std::string const &name) {
    	this->name = name;
	}



};


#endif

//---------------------------------------------------------------------------

#pragma hdrstop

#include "Sqlite3Helper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

typedef unsigned char byte;

union float_as_bytes {
	float	f;
	byte	b[sizeof(float)];
};

union double_as_bytes {
	double	d;
	byte	b[sizeof(double)];
};


union int32_t_as_bytes {
	int32_t	i;
	byte	b[sizeof(int32_t)];
};

union int16_t_as_bytes {
	int16_t i;
	byte    b[sizeof(int16_t)];
};

#pragma pack(1)
union int32_t_as_date {
	int32_t i;
	byte    b[sizeof(int32_t)];
	struct {
		int8_t  month;
		int8_t  day;
		int16_t year;
	} date;
};
#pragma pack()

int32_t SqliteHelper::extractInt32FromBytes(const byte * valBlob, int offset, int sizeBlob) {
	// check
	if (offset + sizeof(int32_t) > sizeBlob) {
		throw std::invalid_argument("extractInt32FromBytes...");
	}
	union int32_t_as_bytes *p = (int32_t_as_bytes *) (valBlob + offset);
	return p->i;
}


int16_t SqliteHelper::extractInt16FromBytes(const byte * valBlob, int offset, int sizeBlob) {
	// check
	if (offset + sizeof(int16_t) > sizeBlob) {
		throw std::invalid_argument("extractInt16FromBytes...");
	}
	union int16_t_as_bytes *p = (int16_t_as_bytes *) (valBlob + offset);
	return p->i;
}


double SqliteHelper::extractDoubleFromBytes(const byte *valBlob, int offset, int sizeBlob) {
	// check
	if (offset + sizeof(double) > sizeBlob) {
		throw std::invalid_argument("extractDoubleFromBytes...");
	}
	union double_as_bytes *p = (double_as_bytes *) (valBlob + offset);
	return p->d;
}


std::string SqliteHelper::extractStringFromBytes(const byte *valBlob, int offset, int sizeBlob, int sizeStr) {
	if (offset + sizeStr > sizeBlob) {
		throw std::invalid_argument("extractStringFromBytes...");
	}
	char * p = (char *) (valBlob + offset);
	std::string str;
	str.append(p, sizeBlob);
	return str;
}


int SqliteHelper::extractInt(int colIndex, sqlite3_stmt *stmt) {

	const char * columnName = sqlite3_column_name(stmt, colIndex);
	int type = sqlite3_column_type(stmt, colIndex);

	if (type == SQLITE_INTEGER) {
		int valInt = sqlite3_column_int(stmt, colIndex);
		return valInt;
	}
	throw std::invalid_argument("extractInt...");
}


std::string SqliteHelper::extractString(int colIndex, sqlite3_stmt *stmt) {
	const char * columnName = sqlite3_column_name(stmt, colIndex);
	int type = sqlite3_column_type(stmt, colIndex);
	if (type == SQLITE_TEXT) {
		const char * valChar = sqlite3_column_text(stmt, colIndex);
		std::string str;
		str.append(valChar);
		return str;
	}
	throw std::invalid_argument("extractString...");
}


void SqliteHelper::patchInt32IntoBytes(const byte *data, int offset, int32_t val, int sizeBlob) {
	// check
	if (offset + sizeof(int32_t) > sizeBlob) {
		throw std::invalid_argument("patchInt32IntoBytes...");
	}
	union int32_t_as_bytes *p = (int32_t_as_bytes *) (data + offset);
	p->i = val;
}




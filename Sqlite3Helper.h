//---------------------------------------------------------------------------

#ifndef Sqlite3HelperH
#define Sqlite3HelperH

#include <cstddef>
#include <stdint.h>
#include <string>
#include "sqlite3.h"
//---------------------------------------------------------------------------

class SqliteHelper {

typedef unsigned char byte;

public:

static int32_t extractInt32FromBytes(const byte * valBlob, int offset, int sizeBlob);


static int16_t extractInt16FromBytes(const byte * valBlob, int offset, int sizeBlob);


static double extractDoubleFromBytes(const byte *valBlob, int offset, int sizeBlob);


static std::string extractStringFromBytes(const byte *valBlob, int offset, int sizeBlob, int sizeStr);


static int extractInt(int colIndex, sqlite3_stmt *stmt);

static std::string extractString(int colIndex, sqlite3_stmt *stmt);

static double extractDouble(int colIndex, sqlite3_stmt *stmt);

static void patchInt32IntoBytes(const byte *data, int offset, int32_t val, int sizeBlob);



public:


};

#endif

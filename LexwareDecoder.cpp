//---------------------------------------------------------------------------

#include <vector>
#include <string>
#pragma hdrstop

#include "LexwareDecoder.h"
#include "Kostenstellen.h"
#include "Journal.h"
#include "KontoDefinition.h"
#include "sqlite3.h"
#include "Sqlite3Helper.h"
#include "juldat.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


// static char *pszFilenameDetails  = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\00000001\\2019\\BHStdYear.dbs";
static char *pszFilenameDetailsPrefix = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\";
static char *pszFilenameDetailsSuffix = "BHStdYear.dbs";
// static char *pszFilenameDetails  = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\00000001\\2020\\BHStdYear.dbs";
// static char *pszFilenameDetails  = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\00000001\\2018\\BHStdYear.dbs";
static char *pszFilenameCompany  = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\00000001\\BHStdCompany.dbs";
static char *pszFilenameAccounts = "C:\\ProgramData\\Lexware\\buchhalter\\Daten\\00000001\\BHStdAccountList.dbs";

static void buildFilename(char *pOut, size_t size, std::string mandant, int year) {
	memset(pOut, 0, size);
	snprintf(pOut, size, "%s\\%s\\%i\\%s", pszFilenameDetailsPrefix, mandant.c_str(), year, pszFilenameDetailsSuffix);
}

int extractKostenstellen(sqlite3 *db, TMemo *Memo1) {

	char *pszSql = "select col0, col2, col3 from lx_verwa where  col1 = 75 and col4 = 0";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("%s", sqlite3_errmsg(db));
		Memo1->Lines->Add(as);
		return rc;
	}

	Kostenstellen &kostenstellen = Kostenstellen::instance();

	Kostenstelle kstNull("0000 - keine Kostenstelle", "0000", 0, 0);
    kostenstellen.add(kstNull);

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 1);
		if (type == SQLITE_TEXT) {
			int iIndex = SqliteHelper::extractInt(0, stmt);
			const char * pszName = sqlite3_column_text(stmt, 1);
			const char * pszKurz = sqlite3_column_text(stmt, 2);
			long l = atol(pszKurz);
			Kostenstelle kst(pszName, pszKurz, l, iIndex);

			kostenstellen.add(kst);
			Memo1->Lines->Add(kst.toString());
				// free(valChar);
		}



		rc = sqlite3_step(stmt);
	}

	rc = sqlite3_finalize(stmt);

	return rc;
}


int extractCompanyTables(std::vector<std::string> &tables, sqlite3 *db, TMemo *Memo1) {

	char *pszSql = "select distinct rtable from __mapping";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
		return rc;

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);
		const char * columnName = sqlite3_column_name(stmt, 0);
		if (type == SQLITE_TEXT) {
			const unsigned char * valChar = sqlite3_column_text(stmt, 0);
			AnsiString as;
			std::string tableName;
			tableName = (char *) valChar;
			tables.push_back(tableName);
			as.printf("colIndex = %d, columnName = %s,Text val = %s", 0, columnName, valChar);
			Memo1->Lines->Add(as);
				// free(valChar);
		}
		AnsiString as;
		as.printf("Line %d, rowCount = %d", rowCount, 0);
		Memo1->Lines->Add(as);



		rc = sqlite3_step(stmt);
	}

	rc = sqlite3_finalize(stmt);

	return rc;
}



int zstring_compare(void *, int, const void * a, int , const void * b) {
	return stricmp((const char *)a, (const char *)b);
}

int doGenerateDataStructures(TMemo *Memo1, TComboBox *ComboBox1) {

	std::vector<std::string> tables;

// 	char *pszSql = "select distinct rtable from __mapping";


	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(pszFilenameCompany, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	extractCompanyTables(tables, db, Memo1);
	extractKostenstellen(db, Memo1);

	rc = sqlite3_close(db);

	for(std::vector<std::string>::iterator it = tables.begin(); it != tables.end(); ++it)  {
		AnsiString as;
		as.printf("%s", (*it).c_str());
		Memo1->Lines->Add(it->c_str());
		/* std::cout << *it; ... */
	}


   	Kostenstellen &kostenstellen = Kostenstellen::instance();
	kostenstellen.fillComboBox(ComboBox1);
	kostenstellen.dumpIntoMemo(Memo1);

	return rc;
}




int extractJournal(Journal &journal, sqlite3 *db, TMemo *Memo1) {

	char *pszSql = "select col0, col1, col2, col3, col4, col5, col6, data6, data7, data8 from bh_jour4 order by col0";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("%s", sqlite3_errmsg(db));
		Memo1->Lines->Add(as);
		return rc;
	}

	journal.clear();

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);

		JournalItem jour;

		jour.setLNr(SqliteHelper::extractInt(0, stmt));
		jour.setDatBuchung(SqliteHelper::extractInt(1, stmt));
		jour.setDatBeleg(SqliteHelper::extractInt(2, stmt));
		jour.setIBelegKreis(SqliteHelper::extractInt(3, stmt));
		jour.setLBelegNr(SqliteHelper::extractInt(4, stmt));
		jour.setStrBelegNr(SqliteHelper::extractString(5, stmt));
		jour.setIZaehler(SqliteHelper::extractInt(6, stmt));

		type = sqlite3_column_type(stmt, 7);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 7);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 7);

			jour.setIStatus(SqliteHelper::extractInt16FromBytes( valBlob,  0, size));
			jour.setStrText(SqliteHelper::extractStringFromBytes(valBlob,  2, size, 80));
			jour.setLSoll(  SqliteHelper::extractInt32FromBytes( valBlob, 82, size));
			jour.setLHaben( SqliteHelper::extractInt32FromBytes( valBlob, 86, size));
			jour.setLUst(   SqliteHelper::extractInt32FromBytes( valBlob, 90, size));
			jour.setIWaehrung(SqliteHelper::extractInt16FromBytes( valBlob, 94, size));
			jour.setDftTageskurs(SqliteHelper::extractDoubleFromBytes( valBlob, 96, size));
			jour.setDftNetto(    SqliteHelper::extractDoubleFromBytes( valBlob, 104, size));
			jour.setDftUst(      SqliteHelper::extractDoubleFromBytes( valBlob, 112, size));
		}
		type = sqlite3_column_type(stmt, 8);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 8);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 8);

			jour.setLUst(SqliteHelper::extractInt32FromBytes( valBlob, 0, size));
			jour.setLBezug(SqliteHelper::extractInt32FromBytes( valBlob, 4, size));
			jour.setDftUstProz(SqliteHelper::extractDoubleFromBytes (valBlob, 8, size));
			jour.setIUstArt(SqliteHelper::extractInt16FromBytes( valBlob, 16, size));
			jour.setLKost1(SqliteHelper::extractInt32FromBytes( valBlob, 18, size));
			jour.setLKost2(SqliteHelper::extractInt32FromBytes( valBlob, 22, size));
			jour.setIOPJahr(SqliteHelper::extractInt16FromBytes( valBlob, 26, size));
			jour.setIStatusSperre(SqliteHelper::extractInt16FromBytes( valBlob, 28, size));
			jour.setIStatusAbschluss(SqliteHelper::extractInt16FromBytes( valBlob, 30, size));
			jour.setIStatusAbgleich(SqliteHelper::extractInt16FromBytes( valBlob, 32, size));
		}
		type = sqlite3_column_type(stmt, 9);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 9);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 9);

			jour.setLTaxCase(SqliteHelper::extractInt32FromBytes( valBlob, 0, size));
		}

		journal.add(jour);

		rc = sqlite3_step(stmt);
	}

	rc = sqlite3_finalize(stmt);

	return rc;
}




int doGenerateJournal(TMemo *Memo1, const char *pszMandant, int year)
{

	Journal &journal = Journal::instance();

// 	char *pszSql = "select distinct rtable from __mapping";
	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	char szFilename[2048];
	buildFilename(szFilename, sizeof(szFilename), pszMandant, year);

	rc = sqlite3_open(szFilename, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	extractJournal(journal, db, Memo1);

	rc = sqlite3_close(db);

	journal.dumpIntoMemo(Memo1);

	return rc;
}


int extractKontenRahmen(KontenRahmen &konten, sqlite3 *db, TMemo *Memo1) {

	char *pszSql = "select col0, col1, col2, col3, col4, col5, col6, col7, col8, col9, data10, data11, lGuVStdBilrug from BH_Konto order by col0";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("%s", sqlite3_errmsg(db));
		Memo1->Lines->Add(as);
		return rc;
	}

	konten.clear();

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	while (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);

		Konto konto;

		konto.setLNr(SqliteHelper::extractInt(0, stmt));
		konto.setStrName(SqliteHelper::extractString(1, stmt));

		type = sqlite3_column_type(stmt, 11);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 11);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 11);
			konto.setFBebucht(SqliteHelper::extractInt16FromBytes(valBlob, 6, size));
		}
		/*
		type = sqlite3_column_type(stmt, 7);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 7);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 7);

			jour.setIStatus(SqliteHelper::extractInt16FromBytes( valBlob,  0, size));
			jour.setStrText(SqliteHelper::extractStringFromBytes(valBlob,  2, size, 80));
			jour.setLSoll(  SqliteHelper::extractInt32FromBytes( valBlob, 82, size));
			jour.setLHaben( SqliteHelper::extractInt32FromBytes( valBlob, 86, size));
			jour.setLUst(   SqliteHelper::extractInt32FromBytes( valBlob, 90, size));
			jour.setIWaehrung(SqliteHelper::extractInt16FromBytes( valBlob, 94, size));
			jour.setDftTageskurs(SqliteHelper::extractDoubleFromBytes( valBlob, 96, size));
			jour.setDftNetto(    SqliteHelper::extractDoubleFromBytes( valBlob, 104, size));
			jour.setDftUst(      SqliteHelper::extractDoubleFromBytes( valBlob, 112, size));
		}
		*/

		konten.add(konto);

		rc = sqlite3_step(stmt);
	}

	rc = sqlite3_finalize(stmt);

	return rc;
}


int doGenerateKontenRahmen(TMemo *pMemo) {

	KontenRahmen &konten = KontenRahmen::instance();

// 	char *pszSql = "select distinct rtable from __mapping";


	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(pszFilenameAccounts, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	extractKontenRahmen(konten, db, pMemo);

	rc = sqlite3_close(db);

	konten.dumpIntoMemo(pMemo);

	return rc;

}


const long magic = 129730194;

#pragma pack(1)
union int32_t_as_date {
	int32_t i;
	byte    b[sizeof(int32_t)];
	struct {
		int8_t  day;
		int8_t  month;
		int16_t year;
	} date;
};
#pragma pack()


std::string convertToDate(long numberDate) {
	// double dbl = numberDate - magic;
	int32_t_as_date date;
	date.i = numberDate;
	int year, month, day;
	// JulianDateToGregorianDate(dbl, &year, &month, &day);
	year = date.date.year;
	month = date.date.month;
	day = date.date.day;
	char sz[256];
	// snprintf(sz, 255, "%d.%d.%d", day, month, year);
	snprintf(sz, 255, "%02d.%02d.%d", day, month, year);
	std::string result;
	result = sz;
	return sz;
}


long convertToDateNumber(int year, int month, int day) {
	return 0;

}


static int updateJournalKostenstellen(int no, int idx, int kst1, int kst2, sqlite3 *db, TMemo *pMemo) {

	// char *pszSql1 = "select col0, data6 from bh_jour4 where col0 = ? and col6 = ?";

	char *pszSql1 = "select col0, data7 from bh_jour4 where col0 = ? and col6 = ?";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql1, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("Prepare Statement failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 1, no);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter (1, no) failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 2, idx);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter (2, idx) failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);

		int no = SqliteHelper::extractInt(0, stmt);
		// check no should be the same like in the where statement

		type = sqlite3_column_type(stmt, 1);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 1);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 1);

			// byte data[size + 1];
			byte *pData = new unsigned char [size + 1];

			memset(pData, 0, size + 1);
			memcpy(pData, valBlob, size);

			SqliteHelper::patchInt32IntoBytes( pData, 18, kst1, size);
			SqliteHelper::patchInt32IntoBytes( pData, 22, kst2, size);

			// do the update
			char *pszSql2 = "update bh_jour4 set data7=? where col0 = ? and col6 = ?";
			sqlite3_stmt *stmtUpd = NULL;

			rc = sqlite3_prepare(db, pszSql2, -1, &stmtUpd, 0);

			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Prepare for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_blob(stmtUpd, 1, pData, size, SQLITE_STATIC);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (1) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_int(stmtUpd, 2, no);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (2, no) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_int(stmtUpd, 3, idx);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (3, idx) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_step(stmtUpd);
			if (rc != SQLITE_DONE) {
				AnsiString as;
				as.printf("Step for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_finalize(stmtUpd);

			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Finalize for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			delete [](pData);
		}

	}

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Finalize failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	return rc;
}


int updateKostenstellen(int nr, int idx, int kst1, int kst2, TMemo *pMemo, const char *pszMandant, int year) {


	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	char szFilename[2048];
	buildFilename(szFilename, sizeof(szFilename), pszMandant, year);

	rc = sqlite3_open(szFilename, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	updateJournalKostenstellen(nr, idx, kst1, kst2, db, pMemo);

	rc = sqlite3_close(db);

	return rc;

}


static int deleteJournal(int no, sqlite3 *db, TMemo *pMemo, char *pszSql) {

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("Prepare Statement failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 1, no);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_OK)
	{

	}

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Finalize failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	return rc;
}



static int deleteJournal(int no, sqlite3 *db, TMemo *pMemo) {

	char *pszSql1 = "delete from bh_jour4 where col0 = ?";
	char *pszSql2 = "delete from bh_jourx where col0 = ?";
	// char *pszSql = "select col2, col3 from lx_verwa";

	int rc = 0;

	rc = deleteJournal(no, db, pMemo, pszSql1);
	rc = deleteJournal(no, db, pMemo, pszSql2);

	return rc;
}


int deleteJournalRecord(int nr, TMemo *pMemo, const char *pszMandant, int year) {

	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	char szFilename[2048];
	buildFilename(szFilename, sizeof(szFilename), pszMandant, year);

	rc = sqlite3_open(szFilename, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	deleteJournal(nr, db, pMemo);

	rc = sqlite3_close(db);

	return rc;

}

int updateJournalRecordKonten(int nr, int idx, int ktoSoll, int ktoHaben, sqlite3 *db, TMemo *pMemo) {

	char *pszSql1 = "select col0, data6 from bh_jour4 where col0 = ? and col6 = ?";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql1, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("Prepare Statement failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 1, nr);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 2, idx);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);

		int no = SqliteHelper::extractInt(0, stmt);
		// check no should be the same like in the where statement

		type = sqlite3_column_type(stmt, 1);
		if (type == SQLITE_BLOB) {
			int size = sqlite3_column_bytes(stmt, 1);
			const byte * valBlob = (const byte *) sqlite3_column_blob(stmt, 1);

			// byte data[size + 1];
			byte *pData = new unsigned char [size + 1];

			memset(pData, 0, size + 1);
			memcpy(pData, valBlob, size);

			SqliteHelper::patchInt32IntoBytes( pData, 82, ktoSoll, size);
			SqliteHelper::patchInt32IntoBytes( pData, 86, ktoHaben, size);

			// do the update
			char *pszSql2 = "update bh_jour4 set data6=? where col0 = ? and col6 = ?";
			sqlite3_stmt *stmtUpd = NULL;

			rc = sqlite3_prepare(db, pszSql2, -1, &stmtUpd, 0);

			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Prepare for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_blob(stmtUpd, 1, pData, size, SQLITE_STATIC);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (1) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_int(stmtUpd, 2, no);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (2) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_bind_int(stmtUpd, 3, idx);
			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (3) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_step(stmtUpd);
			if (rc != SQLITE_DONE) {
				AnsiString as;
				as.printf("Step for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			rc = sqlite3_finalize(stmtUpd);

			if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Finalize for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
			}

			delete [](pData);
		}

	}

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Finalize failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	return rc;

}


int updateJournalRecordKonto(int nr, int idx, int ktoSoll, int ktoHaben, TMemo *pMemo, const char *pszMandant, int year) {

	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	char szFilename[2048];
	buildFilename(szFilename, sizeof(szFilename), pszMandant, year);

	rc = sqlite3_open(szFilename, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	updateJournalRecordKonten(nr, idx, ktoSoll, ktoHaben, db, pMemo);

	rc = sqlite3_close(db);

	return rc;



}






int updateJournalRecordAll(int nr, int idx, int ktoSoll, int ktoHaben, int kst1, int kst2, sqlite3 *db, TMemo *pMemo) {

	char *pszSql1 = "select col0, data6, data7 from bh_jour4 where col0 = ? and col6 = ?";
	// char *pszSql = "select col2, col3 from lx_verwa";

	char *zErrMsg = 0;
	int rc;

	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare_v2(db, pszSql1, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		// sqlite3_extended_error();
		AnsiString as;
		as.printf("Prepare Statement failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 1, nr);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter (1, no) failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	rc = sqlite3_bind_int(stmt, 2, idx);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Bind parameter (2, idx) failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	int rowCount = 0;
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE && rc != SQLITE_OK)
	{
		rowCount++;
		int colCount = sqlite3_column_count(stmt);
		int type = sqlite3_column_type(stmt, 0);

		int no = SqliteHelper::extractInt(0, stmt);
		// check no should be the same like in the where statement

		type = sqlite3_column_type(stmt, 1);
		if (type != SQLITE_BLOB) {
			return SQLITE_ERROR;
		}

		type = sqlite3_column_type(stmt, 2);
		if (type != SQLITE_BLOB) {
			return SQLITE_ERROR;
		}

		int sizeData6 = sqlite3_column_bytes(stmt, 1);
		const byte * valBlobData6 = (const byte *) sqlite3_column_blob(stmt, 1);

		// byte data[size + 1];
		byte *pData6 = new unsigned char [sizeData6 + 1];

		memset(pData6, 0, sizeData6 + 1);
		memcpy(pData6, valBlobData6, sizeData6);

		int sizeData7 = sqlite3_column_bytes(stmt, 2);
		const byte * valBlobData7 = (const byte *) sqlite3_column_blob(stmt, 2);

		byte *pData7 = new unsigned char [sizeData7 + 1];

		memset(pData7, 0, sizeData7 + 1);
		memcpy(pData7, valBlobData7, sizeData7);

		SqliteHelper::patchInt32IntoBytes( pData6, 82, ktoSoll, sizeData6);
		SqliteHelper::patchInt32IntoBytes( pData6, 86, ktoHaben, sizeData6);

		SqliteHelper::patchInt32IntoBytes( pData7, 18, kst1, sizeData7);
		SqliteHelper::patchInt32IntoBytes( pData7, 22, kst2, sizeData7);

		// do the update
		char *pszSql2 = "update bh_jour4 set data6 = ?, data7 = ? where col0 = ? and col6 = ?";
		sqlite3_stmt *stmtUpd = NULL;

		rc = sqlite3_prepare(db, pszSql2, -1, &stmtUpd, 0);

		if (rc != SQLITE_OK) {
			AnsiString as;
			as.printf("Prepare for update failed: %s", sqlite3_errmsg(db));
			pMemo->Lines->Add(as);
			return rc;
		}

		rc = sqlite3_bind_blob(stmtUpd, 1, pData6, sizeData6, SQLITE_STATIC);
		if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (1) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
		}

		rc = sqlite3_bind_blob(stmtUpd, 2, pData7, sizeData7, SQLITE_STATIC);
		if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (2) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
		}

		rc = sqlite3_bind_int(stmtUpd, 3, no);
		if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (3, no) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
		}

		rc = sqlite3_bind_int(stmtUpd, 4, idx);
		if (rc != SQLITE_OK) {
				AnsiString as;
				as.printf("Bind parameter (4, idx) for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
		}

		rc = sqlite3_step(stmtUpd);
		if (rc != SQLITE_DONE) {
				AnsiString as;
				as.printf("Step for update failed: %s", sqlite3_errmsg(db));
				pMemo->Lines->Add(as);
				return rc;
		}

		rc = sqlite3_finalize(stmtUpd);

		if (rc != SQLITE_OK) {
			AnsiString as;
			as.printf("Finalize for update failed: %s", sqlite3_errmsg(db));
			pMemo->Lines->Add(as);
			return rc;
		}

		delete [](pData6);
		delete [](pData7);


	}

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) {
		AnsiString as;
		as.printf("Finalize failed: %s", sqlite3_errmsg(db));
		pMemo->Lines->Add(as);
		return rc;
	}

	return rc;

}


int updateJournalRecordAll(int nr, int idx, int ktoSoll, int ktoHaben, int kst1, int kst2, TMemo *pMemo, const char *pszMandant, int year) {

	sqlite3 *db;

	char *zErrMsg = 0;
	int rc;

	char szFilename[2048];
	buildFilename(szFilename, sizeof(szFilename), pszMandant, year);

	rc = sqlite3_open(szFilename, &db);

	rc = sqlite3_create_collation(db, "ZSTRING", SQLITE_UTF8, NULL, zstring_compare);

	updateJournalRecordAll(nr, idx, ktoSoll, ktoHaben, kst1, kst2, db, pMemo);

	rc = sqlite3_close(db);

	return rc;



}






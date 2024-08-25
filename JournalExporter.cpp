//---------------------------------------------------------------------------

#pragma hdrstop

#include "JournalExporter.h"
#include "LexwareDecoder.h"
#include "Budget.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


static void exportKostenstellen(sqlite3* pDb, Kostenstellen &kostenstellen, TMemo *pMemo);
static void exportAccounts(sqlite3* pDb, KontenRahmen &kontenRahmen, TMemo *pMemo);

static void createAndExportBudget(sqlite3* pDb, TMemo *pMemo);

static void createMissingCostUnits(sqlite3* pDb, TMemo *pMemo);

static void updateCostUnit(sqlite3* pDb, TMemo *pMemo, double valueDebit, double valueCredit, long idCostUnit);

static void executeStatement(sqlite3* pDb, TMemo *pMemo, char *stmt);

static void calculateBudget(sqlite3* pDb, TMemo *pMemo);

static void insertBudget1(sqlite3* pDb, TMemo *pMemo);
static void insertBudget2(sqlite3* pDb, TMemo *pMemo);
static void insertBudget3(sqlite3* pDb, TMemo *pMemo);

static void completeBudgetTable(sqlite3* pDb, TMemo *pMemo);

static void calculateBalance(sqlite3* pDb, TMemo *pMemo);

static void updateBudget(sqlite3* pDb, TMemo *pMemo);

static void updateBudgetFromCostUnit(sqlite3* pDb, TMemo *pMemo);

static void updateBudgetValueBudget(sqlite3* pDb, TMemo *pMemo);

static void updateBudgetValueRemainingBudget(sqlite3* pDb, TMemo *pMemo);

static void fillTableAccountValues(sqlite3 *pDb, TMemo *pMemo);

static void createViewReportBudget(sqlite3 *pDB, TMemo *pMemo);

static void createViewReportCompetitiveSport(sqlite3 *pDB, TMemo *pMemo);

static void createViewReportAllSports(sqlite3 *pDB, TMemo *pMemo);

static void createViewReportPraesidiumPlaning(sqlite3 *pDB, TMemo *pMemo);

static void createTableCostUnitReports(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo);

static void createTableCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo);

static void createIndexCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems1(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems2(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems3(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems4(sqlite3 *pDB, TMemo *pMemo);

static void fillTableCostUnitRprtItems5(sqlite3 *pDB, TMemo *pMemo);

static void createTableCostUnitSummery(sqlite3 *pDB, TMemo *pMemo);

static void insertTableCostUnitSummery3(sqlite3 *pDB, TMemo *pMemo);

static void insertTableCostUnitSummery2(sqlite3 *pDB, TMemo *pMemo);

static void insertTableCostUnitSummery5(sqlite3 *pDB, TMemo *pMemo);


extern void exportJournalToDatabase(UnicodeString filename, Journal &journal, KontenRahmen &konten, Kostenstellen &kostenstellen, TMemo *pMemo) {

	sqlite3* pDb = NULL;
	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{

		AnsiString as = filename;
		// open connection to a DB
		if (SQLITE_OK != (ret = sqlite3_open_v2(as.c_str(), &pDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)))
		{
			printf("Failed to open conn: %d\n", ret);
			break;
		}
		// prepare the statement
		char *strStmt =
		"CREATE TABLE Journal ( " \
		"LNR	INTEGER NOT NULL, " \
		"IZAEHLER	INTEGER NOT NULL, " \
		"DATBUCHUNG	TEXT, " \
		"BELEGKREIS	INTEGER, " \
		"BELEGNR	INTEGER, " \
		"STATUS	INTEGER, " \
		"BUCHUNGSTEXT	TEXT, " \
		"KTOSOLL	INTEGER, " \
		"KTOHABEN	INTEGER, " \
		"BETRAG		REAL, " \
		"KOSTENSTELLE	INTEGER, " \
		"KTOSOLLTEXT    TEXT, " \
		"KTOHABENTEXT   TEXT, " \
		"KSTTEXT        TEXT, " \
		"PRIMARY KEY(LNR,IZAEHLER) " \
		"); ";
		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

		int n = journal.getCount();

		if (n > 0) {
			char *strStmt2 =
			"INSERT INTO Journal (LNR, IZAEHLER, DATBUCHUNG, BELEGKREIS, BELEGNR, STATUS, BUCHUNGSTEXT, KTOSOLL, KTOHABEN, BETRAG, KOSTENSTELLE, KTOSOLLTEXT, KTOHABENTEXT, KSTTEXT) " \
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?); ";

			if (SQLITE_OK != (ret = sqlite3_prepare_v2(pDb, strStmt2, -1, &stmt, NULL)))
			{
				printf("Failed to prepare insert: %d, %s\n", ret, sqlite3_errmsg(pDb));
				break;
			}

			for (int i = 0; i < n; i++) {

				AnsiString as1;

				JournalItem &item = journal.getItem(i);

				as1.printf("Bearbeite record %d (%d, %d)", i, item.getLNr(), item.getIZaehler());
				pMemo->Lines->Add(as1);

				int val = item.getLNr();
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 1, val))) {
					AnsiString as;
					as.printf("Bind parameter (1) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				val = item.getIZaehler();
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 2, val))) {
					AnsiString as;
					as.printf("Bind parameter (2) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string date = convertToDate(item.getDatBeleg());
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 3, date.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (3) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 4, item.getIBelegKreis()))) {
					AnsiString as;
					as.printf("Bind parameter (4) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 5, item.getLBelegNr()))) {
					AnsiString as;
					as.printf("Bind parameter (5) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 6, item.getIStatus() ))) {
					AnsiString as;
					as.printf("Bind parameter (6) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string btext = item.getStrText();
				AnsiString as = btext.c_str();
				RawByteString rbs = AnsiToUtf8(as);
				std::string utf8text(rbs.c_str());
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 7, utf8text.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (7) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				int nr = item.getLSoll();
				int ktoNoSoll = 0;
				if (nr > 0) {
					Konto &kontoSoll = konten.findKonto(item.getLSoll());
					ktoNoSoll = kontoSoll.getLNr();
				}
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 8, ktoNoSoll))) {
					AnsiString as;
					as.printf("Bind parameter (8) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				nr = item.getLHaben();
				int ktoNoHaben = 0;
				if (nr > 0) {
					Konto &kontoHaben = konten.findKonto(item.getLHaben());
					ktoNoHaben = kontoHaben.getLNr();
				}
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 9, ktoNoHaben))) {
					AnsiString as;
					as.printf("Bind parameter (9) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				double d = 1.005;
				if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 10, item.getDftNetto()))) {
					AnsiString as;
					as.printf("Bind parameter (10) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				nr = item.getLKost1();
				if (nr > 0) {
					// nr = kostenstellen.findKostenstelle(nr);
					Kostenstelle &kst = kostenstellen.find(nr);
					nr = kst.getNo();
				}
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 11, nr))) {
					AnsiString as;
					as.printf("Bind parameter (11) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string solltext = item.getStrText();
				as = solltext.c_str();
				rbs = AnsiToUtf8(as);
				// utf8text = rbs.c_str();
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 12, rbs.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (12) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string habentext = item.getStrText();
				as = habentext.c_str();
				rbs = AnsiToUtf8(as);
				utf8text = rbs.c_str();
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 13, utf8text.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (13) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string ksttext = item.getStrText();
				as = ksttext.c_str();
				rbs = AnsiToUtf8(as);
				utf8text = rbs.c_str();
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 14, utf8text.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (14) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				// step to 1st row of data
				ret = sqlite3_step(stmt);
				if (ret != SQLITE_DONE && ret != SQLITE_OK) // see documentation, this can return more values as success
				{
					AnsiString as;
					as.printf("Failed to step: %d, %s", ret, sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
					break;
				}

				 sqlite3_reset(stmt);
				// ... and print the value of column 0 (expect 2012 here)
				// printf("Value from sqlite: %s", sqlite3_column_text(stmt, 0));
			}
		}

	} while (false);

	pMemo->Lines->Add("Start exporting cost units");
	exportKostenstellen(pDb, kostenstellen, pMemo);

	pMemo->Lines->Add("Start exporting accounts");
	exportAccounts(pDb, konten, pMemo);

	pMemo->Lines->Add("Export Budges");
	createAndExportBudget(pDb, pMemo);

	//
	pMemo->Lines->Add("createMissingCostUnits");
	createMissingCostUnits(pDb, pMemo);

	pMemo->Lines->Add("add budget values to cost units");


	// updateCostUnit(pDb, pMemo, valueDebit, valueCredit, idCostUnit);
	/* load the budget values and build the cost unit table */
	tcBudget budget;
	budget.loadFromRegistry();
	double valueDebit;
	double valueCredit;
	int account;
	double sumValueDebit = 0.0f;
	double sumValueCredit = 0.0f;
	valueDebit = budget.bdgt_Praesidium;
	valueCredit = budget.egnl_Praesidium;
	valueDebit += valueCredit;
	account = 100;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_RK_Allgemein;
	valueCredit = budget.egnl_RK_Allgemein;
	valueDebit += valueCredit;
	sumValueDebit += valueDebit;
	sumValueCredit += valueCredit;
	account = 401;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_RK_Sachkosten;
	valueCredit = budget.egnl_RK_Sachkosten;
	valueDebit += valueCredit;
	sumValueDebit += valueDebit;
	sumValueCredit += valueCredit;
	account = 402;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_RK_Personalkosten;
	valueCredit = budget.egnl_RK_Personalkosten;
	valueDebit += valueCredit;
	sumValueDebit += valueDebit;
	sumValueCredit += valueCredit;
	account = 403;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	account = 400;
	updateCostUnit(pDb, pMemo, sumValueDebit, sumValueCredit, account);

	sumValueDebit = 0.0f;
	sumValueCredit = 0.0f;

	valueDebit = budget.bdgt_IFS_Allgemein;
	valueCredit = budget.egnl_IFS_Allgemein;
	valueDebit += valueCredit;
	sumValueDebit += valueDebit;
	sumValueCredit += valueCredit;
	account = 421;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_IFS_Sachkosten;
	valueCredit = budget.egnl_IFS_Sachkosten;
	valueDebit += valueCredit;
	sumValueDebit += valueDebit;
	sumValueCredit += valueCredit;
	account = 422;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	account = 420;
	updateCostUnit(pDb, pMemo, sumValueDebit, sumValueCredit, account);

	valueDebit = budget.bdgt_RD_Allgemein;
	valueCredit = budget.egnl_RD_Allgemein;
	valueDebit += valueCredit;
	account = 410;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_IAD_Allgemein;
	valueCredit = budget.egnl_IAD_Allgemein;
	valueDebit += valueCredit;
	account = 440;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_ISH_Allgemein;
	valueCredit = budget.egnl_ISH_Allgemein;
	valueDebit += valueCredit;
	account = 460;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);

	valueDebit = budget.bdgt_SLB_Allgemein;
	valueCredit = budget.egnl_SLB_Allgemein;
	valueDebit += valueCredit;
	account = 470;
	updateCostUnit(pDb, pMemo, valueDebit, valueCredit, account);


	/*
	updateCostUnit(pDb, pMemo, 31965.0 , 43246.0 , 100);
	updateCostUnit(pDb, pMemo, 28583.0 , 23580.0 , 400);
	updateCostUnit(pDb, pMemo,  5003.0 ,     0.0 , 401);
	updateCostUnit(pDb, pMemo, 11080.0 , 11080.0 , 402);
	updateCostUnit(pDb, pMemo, 12500.0 , 12500.0 , 403);
	updateCostUnit(pDb, pMemo,   881.0 ,     0.0 , 410);
	updateCostUnit(pDb, pMemo, 18014.0 , 15000.0 , 420);
	updateCostUnit(pDb, pMemo,  3014.0 ,     0.0 , 421);
	updateCostUnit(pDb, pMemo, 15000.0 , 15000.0 , 422);

	updateCostUnit(pDb, pMemo,  1783.0 ,     0.0 , 440);
	updateCostUnit(pDb, pMemo,  3001.0 ,     0.0 , 460);
	updateCostUnit(pDb, pMemo,   916.0 ,     0.0 , 470);
	updateCostUnit(pDb, pMemo,     0.0 ,     0.0 , 480);
	*/

	pMemo->Lines->Add("calculate the budget");
	calculateBudget(pDb, pMemo);

	pMemo->Lines->Add("insert budget values one, two three");
	insertBudget1(pDb, pMemo);
	insertBudget2(pDb, pMemo);
	insertBudget3(pDb, pMemo);
	completeBudgetTable(pDb,pMemo);

	calculateBalance(pDb, pMemo);

	updateBudget(pDb, pMemo);

	updateBudgetFromCostUnit(pDb, pMemo);

	updateBudgetValueBudget(pDb, pMemo);

	updateBudgetValueRemainingBudget(pDb, pMemo);

    fillTableAccountValues(pDb, pMemo);

	pMemo->Lines->Add("Create report views");

	createViewReportBudget(pDb, pMemo);
	createViewReportCompetitiveSport(pDb, pMemo);
	createViewReportAllSports(pDb, pMemo);
    createViewReportPraesidiumPlaning(pDb, pMemo);

	pMemo->Lines->Add("Create cost unit reports");
	createTableCostUnitReports(pDb, pMemo);
	fillTableCostUnitRprtItems(pDb, pMemo);
	createTableCostUnitRprtItems(pDb, pMemo);
	createIndexCostUnitRprtItems(pDb, pMemo);
	fillTableCostUnitRprtItems1(pDb, pMemo);
	fillTableCostUnitRprtItems2(pDb, pMemo);
	fillTableCostUnitRprtItems3(pDb, pMemo);
	fillTableCostUnitRprtItems4(pDb, pMemo);
    fillTableCostUnitRprtItems5(pDb, pMemo);
	createTableCostUnitSummery(pDb, pMemo);
	insertTableCostUnitSummery3(pDb, pMemo);
	insertTableCostUnitSummery2(pDb, pMemo);
    insertTableCostUnitSummery5(pDb, pMemo);

    pMemo->Lines->Add("export completed");
	// cleanup
	if (NULL != stmt) sqlite3_finalize(stmt);
	if (NULL != pDb) sqlite3_close(pDb);
	// sqlite3_shutdown();
	pMemo->Lines->Add("cleanup completed");
	return;

}




static void exportKostenstellen(sqlite3* pDb, Kostenstellen &kostenstellen, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{

		// prepare the statement
		char *strStmt =
			"CREATE TABLE CostUnit ( " \
			"idCostUnit	INTEGER NOT NULL, " \
			"textCostUnit	TEXT NOT NULL, " \
			"idParentCostUnit	INTEGER NOT NULL, " \
			"valueDebit REAL, " \
			"valueCredit REAL, " \
			"valueBudget REAL, " \
			"PRIMARY KEY(idCostUnit) " \
			");";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

		int n = kostenstellen.getCount();

		if (n > 0) {
			char *strStmt2 =
			"INSERT INTO CostUnit (idCostUnit, textCostUnit, idParentCostUnit) " \
			"VALUES (?, ?, ?); ";

			if (SQLITE_OK != (ret = sqlite3_prepare_v2(pDb, strStmt2, -1, &stmt, NULL)))
			{
				printf("Failed to prepare insert: %d, %s\n", ret, sqlite3_errmsg(pDb));
				break;
			}

			for (int i = 0; i < n; i++) {

				AnsiString as1;

				Kostenstelle &item = kostenstellen.getItem(i);

				as1.printf("Bearbeite record %d (%d, %d)", i, item.getNo(), item.getIIndex());
				pMemo->Lines->Add(as1);

				int val = item.getNo();
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 1, val))) {
					AnsiString as;
					as.printf("Bind parameter (1) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}


				std::string btext = item.getName();
				AnsiString as = btext.c_str();
				RawByteString rbs = AnsiToUtf8(as);
				std::string utf8text(rbs.c_str());
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 2, utf8text.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (2) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				int parent = (item.getNo() / 10) * 10;
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 3, parent))) {
					AnsiString as;
					as.printf("Bind parameter (3) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				// step to 1st row of data
				ret = sqlite3_step(stmt);
				if (ret != SQLITE_DONE && ret != SQLITE_OK) // see documentation, this can return more values as success
				{
					AnsiString as;
					as.printf("Failed to step: %d, %s", ret, sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
					break;
				}

				 sqlite3_reset(stmt);
				// ... and print the value of column 0 (expect 2012 here)
				// printf("Value from sqlite: %s", sqlite3_column_text(stmt, 0));
			}
		}

	} while (false);
	// cleanup
	if (NULL != stmt) sqlite3_finalize(stmt);
	// if (NULL != pDb) sqlite3_close(pDb);
	// sqlite3_shutdown();
	return;

}



static void exportAccounts(sqlite3* pDb, KontenRahmen &accounts, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{

		// prepare the statement
		char *strStmt =
			"CREATE TABLE Account ( " \
			"idAccount INTEGER NOT NULL, " \
			"textAccount TEXT NOT NULL, " \
			"idParentAccount INTEGER NOT NULL, " \
			"PRIMARY KEY(idAccount) " \
			");";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

		int n = accounts.getCount();

		if (n > 0) {
			char *strStmt2 =
			"INSERT INTO Account (idAccount, textAccount, idParentAccount) " \
			"VALUES (?, ?, ?); ";

			if (SQLITE_OK != (ret = sqlite3_prepare_v2(pDb, strStmt2, -1, &stmt, NULL)))
			{
				printf("Failed to prepare insert: %d, %s\n", ret, sqlite3_errmsg(pDb));
				break;
			}

			for (int i = 0; i < n; i++) {

				AnsiString as1;

				Konto &item = accounts.getItem(i);

				as1.printf("Bearbeite record %d (%d, %d)", i, item.getLNr(), item.getLNr());
				pMemo->Lines->Add(as1);

				int val = item.getLNr();
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 1, val))) {
					AnsiString as;
					as.printf("Bind parameter (1) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				std::string btext = item.getStrName();
				AnsiString as = btext.c_str();
				RawByteString rbs = AnsiToUtf8(as);
				std::string utf8text(rbs.c_str());
				if (SQLITE_OK != (ret = sqlite3_bind_text(stmt, 2, utf8text.c_str(), -1, SQLITE_TRANSIENT))) {
					AnsiString as;
					as.printf("Bind parameter (2) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				int parent = (item.getLNr() / 1000) * 1000;
				if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 3, parent))) {
					AnsiString as;
					as.printf("Bind parameter (3) for insert failed: %s", sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
				}

				// step to 1st row of data
				ret = sqlite3_step(stmt);
				if (ret != SQLITE_DONE && ret != SQLITE_OK) // see documentation, this can return more values as success
				{
					AnsiString as;
					as.printf("Failed to step: %d, %s", ret, sqlite3_errmsg(pDb));
					pMemo->Lines->Add(as);
					break;
				}

				 sqlite3_reset(stmt);
				// ... and print the value of column 0 (expect 2012 here)
				// printf("Value from sqlite: %s", sqlite3_column_text(stmt, 0));
			}
		}

	} while (false);
	// cleanup
	if (NULL != stmt) sqlite3_finalize(stmt);
	// if (NULL != pDb) sqlite3_close(pDb);
	// sqlite3_shutdown();
	return;

}

static void createTableBudget(sqlite3* pDb, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{
		char *strStmt =
		"CREATE TABLE Budget ( " \
		"idCostUnit INTEGER NOT NULL, " \
		"valueDebit REAL, " \
		"valueCredit REAL, " \
		"valueBudget REAL, " \
		"valueRemainingBudget REAL, " \
		"valueDebitBudget REAL, " \
		"valueCreditBudget REAL, " \
		"valueBalance REAL, " \
		"PRIMARY KEY(idCostUnit) " \
		");";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

	} while (false);

	return;
}


static void createViewCreditCostUnit(sqlite3* pDb, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{
		char *strStmt =
		"CREATE VIEW creditCostUnit " \
		"as select " \
		" cu.idParentCostUnit, " \
		" sum(j.betrag) as valueCredit " \
		"from journal j, CostUnit cu, Account a " \
		"where j.KOSTENSTELLE = cu.idCostUnit " \
		" and j.ktohaben = a.idAccount " \
		" and j.ktohaben >= 2000 " \
		" and j.ktohaben < 9000 " \
		"group by cu.idParentCostUnit; ";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

	} while (false);

	return;
}



static void createViewDebitCostUnit(sqlite3* pDb, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{
		char *strStmt =
		"CREATE VIEW debitCostUnit " \
		"as select " \
		" cu.idParentCostUnit, " \
		" sum(j.betrag) as valueDebit " \
		"from journal j, CostUnit cu, Account a " \
		"where j.KOSTENSTELLE = cu.idCostUnit " \
		" and j.ktosoll = a.idAccount " \
		" and j.ktosoll >= 2000 " \
		" and j.ktosoll < 9000 " \
		"group by cu.idParentCostUnit; ";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

	} while (false);

	return;
}



static void createAndExportBudget(sqlite3* pDb, TMemo *pMemo) {

	createTableBudget(pDb, pMemo);
	createViewCreditCostUnit(pDb, pMemo);
	createViewDebitCostUnit(pDb, pMemo);

	return;
}


static void executeStatement(sqlite3* pDb, TMemo *pMemo, char *strStmt) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{
		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				char st[1024];
				memset(st, 0, sizeof(st));
				snprintf(st, 1023, "SQLite error: %s!", errmsg);
				pMemo->Lines->Add(st);
				sqlite3_free(errmsg);
				// throw std::runtime_error(st);
			}
		}

	} while (false);

	return;

}



static void createMissingCostUnits(sqlite3* pDb, TMemo *pMemo) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{
		char *strStmt =
		  "INSERT INTO CostUnit (idCostUnit, textCostUnit, idParentCostUnit) " \
		  "SELECT idparentCostUnit, textCostUnit, 0 " \
		  "FROM CostUnit " \
		  "WHERE idCostUnit = idParentCostUnit + 1; ";

		errmsg = NULL;
		if (SQLITE_OK != (ret = sqlite3_exec(pDb, strStmt, NULL, NULL, &errmsg))) {
			if (errmsg != NULL) {
				sqlite3_free(errmsg);
			}
		}

	} while (false);

	return;

}



static void updateCostUnit(sqlite3* pDb, TMemo *pMemo, double valueDebit, double valueCredit, long idCostUnit) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{

		// prepare the statement
		char *strStmt =
			"UPDATE CostUnit SET valueDebit = ?, valueCredit = ? WHERE idCostUnit = ?;";

		if (SQLITE_OK != (ret = sqlite3_prepare_v2(pDb, strStmt, -1, &stmt, NULL)))
		{
			printf("Failed to prepare update: %d, %s\n", ret, sqlite3_errmsg(pDb));
			break;
		}

		AnsiString as1;

		if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 1, valueDebit))) {
			AnsiString as;
			as.printf("Bind parameter (1) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 2, valueCredit))) {
			AnsiString as;
			as.printf("Bind parameter (2) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 3, idCostUnit))) {
			AnsiString as;
			as.printf("Bind parameter (3) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		// step to 1st row of data
		ret = sqlite3_step(stmt);
		if (ret != SQLITE_DONE && ret != SQLITE_OK) // see documentation, this can return more values as success
		{
			AnsiString as;
			as.printf("Failed to step: %d, %s", ret, sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
			break;
		}

		sqlite3_reset(stmt);

	} while (false);
	// cleanup
	if (NULL != stmt) sqlite3_finalize(stmt);
	// if (NULL != pDb) sqlite3_close(pDb);
	// sqlite3_shutdown();
	return;

}


static void calculateBudget(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"UPDATE CostUnit SET valueBudget = valueDebit - valueCredit " \
		"where valueDebit is not null and valueCredit is not null;";

	executeStatement(pDb, pMemo, strStmt);

}


static void insertBudget1(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"insert into budget  (idCostUnit, valueCredit, valueDebit) " \
		"select c.idParentCostUnit as costUnit, " \
			"c.valueCredit, " \
			"d.valueDebit " \
		"from creditCostUnit c, debitCostUnit d " \
		"where c.idParentCostUnit = d.idParentCostUnit " \
        "and c.idParentCostUnit <> 0;";

	executeStatement(pDb, pMemo, strStmt);

}


static void insertBudget2(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"insert into budget (idCostUnit, valueDebit) " \
		"select " \
			"cu.idParentCostUnit, " \
			"sum(j.betrag) as valueDebit " \
		"from journal j, CostUnit cu, Account a " \
		"where j.KOSTENSTELLE = cu.idCostUnit " \
			"and j.ktosoll = a.idAccount " \
			"and j.ktosoll >= 2000 " \
			"and j.ktosoll < 9000 " \
			" and cu.idParentCostUnit not in " \
				"(select distinct idCostUnit from budget) " \
		"group by cu.idParentCostUnit;";

	executeStatement(pDb, pMemo, strStmt);

}


static void insertBudget3(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"insert into budget (idCostUnit, valueCredit) " \
		"select " \
			"cu.idParentCostUnit, " \
			"sum(j.betrag) as valueCredit " \
		"from journal j, CostUnit cu, Account a " \
		"where j.KOSTENSTELLE = cu.idCostUnit " \
			"and j.ktohaben = a.idAccount " \
			"and j.ktohaben >= 2000 " \
			"and j.ktohaben < 9000 " \
			"and cu.idParentCostUnit not in " \
				"(select distinct idCostUnit from budget) " \
		"group by cu.idParentCostUnit;";

	executeStatement(pDb, pMemo, strStmt);

}

static void completeBudgetTable(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt = "update budget set valueDebit = 0.0 where valueDebit is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueCredit = 0.0 where valueCredit is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueBudget = 0.0 where valueBudget is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueRemainingBudget = 0.0 where valueRemainingBudget is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueDebitBudget = 0.0 where valueDebitBudget is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueCreditBudget = 0.0 where valueCreditBudget is null;";
	executeStatement(pDb, pMemo, strStmt);

	strStmt = "update budget set valueBalance = 0.0 where valueBalance is null;";
	executeStatement(pDb, pMemo, strStmt);

}


static void calculateBalance(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"update budget set valueBalance = valueCredit - valueDebit;";
	executeStatement(pDb, pMemo, strStmt);

}


static void updateBudget(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
		"UPDATE budget SET valueBalance = valueCredit - valueDebit " \
			"where valueDebit is not null and valueCredit is not null;";

	executeStatement(pDb, pMemo, strStmt);

}


static void updateBudgetFromCostUnit(sqlite3* pDb, TMemo *pMemo) {
	char *strStmt =
		"UPDATE budget " \
		"SET " \
		" valueCreditBudget = (SELECT c1.valueCredit " \
							"FROM CostUnit c1 " \
							"WHERE c1.idCostUnit = budget.idCostUnit) " \
		", valueDebitBudget = (SELECT c1.valueDebit " \
							"FROM CostUnit c1 " \
							"WHERE c1.idCostUnit = budget.idCostUnit ) " \
		"WHERE " \
			"EXISTS ( " \
				"SELECT * " \
				"FROM CostUnit c1 " \
				"WHERE c1.idCostUnit = budget.idCostUnit " \
			");";
	executeStatement(pDb, pMemo, strStmt);

}


static void updateBudgetValueBudget(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
	  "UPDATE budget SET valueBudget = valueDebitBudget - valueCreditBudget " \
	  "where valueDebitBudget is not null and valueCreditBudget is not null; ";

	executeStatement(pDb, pMemo, strStmt);
}


static void updateBudgetValueRemainingBudget(sqlite3* pDb, TMemo *pMemo) {

	char *strStmt =
	  "update budget set valueRemainingBudget = valueBudget + valueBalance " \
	  "where valueBudget is not null and valueBalance is not null; ";

	executeStatement(pDb, pMemo, strStmt);
}



static void createTableAccountValues(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"CREATE TABLE AccountValues " \
		"( " \
			"idAccount INTEGER NOT NULL, " \
			"idCostUnit INTEGER NOT NULL, " \
			"valueDebit REAL, " \
			"valueCredit REAL, " \
			"valueFinal REAL, " \
			"intType INTEGER, " \
			"PRIMARY KEY(idAccount, idCostUnit) " \
		");";

	executeStatement(pDB, pMemo, strStmt);

}


static void createViewReportBudget(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"CREATE VIEW reportbudget " \
		"as " \
		"select b.idCostUnit, " \
		"  b.valueBudget, " \
		"  b.valueRemainingBudget, " \
		"  b.valueBalance, " \
		"  cu.textCostUnit " \
		"from budget b, " \
		"  costUnit cu " \
		"where b.idCostUnit > 100 " \
		"  and b.idCostUnit = cu.idCostUnit";

	executeStatement(pDB, pMemo, strStmt);
}


static void createViewReportCompetitiveSport(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
"CREATE VIEW reportcompetitivesport " \
"as " \
"select cast('Soll' as text) as type, " \
"		  j.ktosoll as noAccount, " \
"		  a.textAccount, " \
"		  cu.idParentCostUnit, " \
"		  j.kostenstelle, " \
"		  cast(sum(j.betrag) as real) as betrag, " \
"		  cu.textCostUnit, " \
"		  cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktosoll = a.idAccount " \
"	and j.ktosoll >= 2000 " \
"	and j.ktosoll < 9000 " \
"	and j.KOSTENSTELLE in (401, 402, 403, 404, 405, 406, 407, 408, 409, 421, 422) " \
"   group by cu.idCostUnit, j.ktosoll " \
"union " \
"select cast('Haben' as text) as type, " \
"	j.ktohaben as noAccount, " \
"	a.textAccount, cu.idParentCostUnit, " \
"	j.Kostenstelle, " \
"	cast(sum(j.betrag) as real) as betrag, " \
"	cu.textCostUnit, cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktohaben = a.idAccount " \
"	and j.ktohaben >= 2000 " \
"	and j.ktohaben < 9000 " \
"	and j.KOSTENSTELLE in (401, 402, 403, 404, 405, 406, 407, 408, 409, 421, 422) " \
"	group by cu.idCostUnit, j.ktohaben " \
"order by 1, cu.idParentCostUnit, j.kostenstelle, j.ktohaben";

	executeStatement(pDB, pMemo, strStmt);
}

static void createViewReportAllSports(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
"CREATE VIEW reportallsports " \
"as " \
"select cast('Ausgaben' as text) as type, " \
"		  j.ktosoll as noAccount, " \
"		  a.textAccount, " \
"		  cu.idParentCostUnit, " \
"		  j.kostenstelle, " \
"		  cast(sum(j.betrag) as real) as betrag, " \
"		  cu.textCostUnit, " \
"		  cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktosoll = a.idAccount " \
"	and j.ktosoll >= 2000 " \
"	and j.ktosoll < 9000 " \
"	and j.KOSTENSTELLE in (select distinct idCostUnit from CostUnit where idParentCostUnit <> 0) " \
"group by cu.idCostUnit, j.ktosoll " \
"union " \
"select cast('Einnahmen' as text) as type, " \
"	j.ktohaben as noAccount, " \
"	a.textAccount, cu.idParentCostUnit, " \
"	j.Kostenstelle, " \
"	cast(sum(j.betrag) as real) as betrag, " \
"	cu.textCostUnit, cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktohaben = a.idAccount " \
"	and j.ktohaben >= 2000 " \
"	and j.ktohaben < 9000 " \
"	and j.KOSTENSTELLE in (select distinct idCostUnit from CostUnit where idParentCostUnit <> 0) " \
"	group by cu.idCostUnit, j.ktohaben " \
"order by 1, cu.idParentCostUnit, j.kostenstelle, j.ktohaben";

	executeStatement(pDB, pMemo, strStmt);
}


static void createViewReportPraesidiumPlaning(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
"CREATE VIEW reportpraesidiumforplaning as " \
"select cast('Soll' as text) as type, " \
"		  j.ktosoll as noAccount, " \
"		  a.textAccount, " \
"		  cu.idParentCostUnit, " \
"		  cast(sum(j.betrag) as real) as betrag, " \
"		  cu.textCostUnit, " \
"		  cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktosoll = a.idAccount " \
"	and j.ktosoll >= 2000 " \
"	and j.ktosoll < 9000 " \
"	and j.KOSTENSTELLE in (101, 102, 103, 104, 105, 106, 107, 108, 109) " \
"group by cu.idParentCostUnit, j.ktosoll " \
"union " \
"select cast('Haben' as text) as type, " \
"	j.ktohaben as noAccount, " \
"	a.textAccount, " \
"	cu.idParentCostUnit, " \
"	cast(sum(j.betrag) as real) as betrag, " \
"	cu.textCostUnit, " \
"	cu2.textCostUnit as parentCostUnit " \
"from journal j, CostUnit cu, Account a, CostUnit cu2 " \
"where j.KOSTENSTELLE = cu.idCostUnit " \
"	and cu.idParentCostUnit = cu2.idCostUnit " \
"	and j.ktohaben = a.idAccount " \
"	and j.ktohaben >= 2000 	and j.ktohaben < 9000 " \
"	and j.KOSTENSTELLE in (101, 102, 103, 104, 105, 106, 107, 108, 109) " \
"group by cu.idParentCostUnit, j.ktohaben " \
"order by 1, cu.idParentCostUnit, j.ktohaben ";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesStep1(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"INSERT INTO AccountValues (idAccount, idCostUnit, valueDebit, valueCredit, valueFinal, intType) " \
		"SELECT DISTINCT KTOSOLL AS KONTO, KOSTENSTELLE, 0.0, 0.0, 0.0, 0 from Journal " \
		"where KOSTENSTELLE <> 0 AND KTOSOLL <> 0 " \
		"AND KTOSOLL >= 2000 AND KTOSOLL < 9000 " \
		"UNION " \
		"SELECT DISTINCT KTOHABEN AS KONTO, KOSTENSTELLE, 0.0, 0.0, 0.0, 0 from Journal " \
		"where KOSTENSTELLE <> 0 AND KTOHABEN <> 0 " \
		"AND KTOHABEN >= 2000 AND KTOHABEN < 9000";

	executeStatement(pDB, pMemo, strStmt);

}

static void fillTableAccountValuesStep2(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"create view creditCostUnitWithAccount as " \
		"select " \
			"kostenstelle, " \
			"ktohaben, " \
			"sum(betrag) as valueCredit " \
		"from journal j " \
		"where ktohaben >= 2000 " \
		"and ktohaben < 9000 " \
		"group by kostenstelle, ktohaben";

	executeStatement(pDB, pMemo, strStmt);
}

static void fillTableAccountValuesStep3(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"create view debitCostUnitWithAccount as " \
		"select " \
			"kostenstelle, " \
			"ktosoll, " \
			"sum(betrag) as valueDebit " \
		"from journal j " \
		"where ktosoll >= 2000 " \
		"and ktosoll < 9000 " \
		"group by kostenstelle, ktosoll";

	executeStatement(pDB, pMemo, strStmt);
}

static void fillTableAccountValuesStep4(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =

		"update AccountValues " \
		"set valueCredit = ( " \
			"select valueCredit " \
			"from creditCostUnitWithAccount cuwa " \
			"where AccountValues.idAccount = cuwa.ktohaben " \
			"and AccountValues.idCostUnit = cuwa.kostenstelle " \
		"); ";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesStep5(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"update AccountValues " \
		"set valueCredit = 0.0 " \
		"where valueCredit is null;";

	executeStatement(pDB, pMemo, strStmt);

}

static void fillTableAccountValuesStep6(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"update AccountValues " \
		"set valueDebit= ( " \
			"select valueDebit " \
			"from debitCostUnitWithAccount cuwa " \
			"where AccountValues.idAccount = cuwa.ktosoll " \
			"and AccountValues.idCostUnit = cuwa.kostenstelle " \
		");";

	executeStatement(pDB, pMemo, strStmt);

}

static void fillTableAccountValuesStep7(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"update AccountValues " \
		"set valueDebit = 0.0 " \
		"where valueDebit is null;";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesStep8(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
		"update AccountValues " \
		"set valueFinal = valueCredit - valueDebit " \
		"where valueCredit is not null and valueDebit is not null;";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesStep9(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt = "update AccountValues set intType = 1 where valueFinal > 0.0; ";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesStep10(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt = "update AccountValues set intType = 2 where valueFinal < 0.0;";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableAccountValuesInsert(sqlite3* pDb, TMemo *pMemo,
	int idAccount, int idCostUnit, double valueDebit, double valueCredit, double valueFinal, int intType) {

	sqlite3_stmt *stmt = NULL;
	char *errmsg;
	int ret = 0;
	do // avoid nested if's
	{

		// prepare the statement
		char *strStmt =
			"insert into AccountValues " \
				"(idAccount, idCostUnit, valueDebit, valueCredit, valueFinal, intType) " \
				"values (?, ?, ?, ?, ?, ?)";

		if (SQLITE_OK != (ret = sqlite3_prepare_v2(pDb, strStmt, -1, &stmt, NULL)))
		{
			printf("Failed to prepare update: %d, %s\n", ret, sqlite3_errmsg(pDb));
			break;
		}

		AnsiString as1;

		if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 1, idAccount))) {
			AnsiString as;
			as.printf("Bind parameter (1, idAccount) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 2, idCostUnit))) {
			AnsiString as;
			as.printf("Bind parameter (2, idCostUnit) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 3, valueDebit))) {
			AnsiString as;
			as.printf("Bind parameter (3) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 4, valueCredit))) {
			AnsiString as;
			as.printf("Bind parameter (4) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_double(stmt, 5, valueFinal))) {
			AnsiString as;
			as.printf("Bind parameter (5) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		if (SQLITE_OK != (ret = sqlite3_bind_int(stmt, 6, intType))) {
			AnsiString as;
			as.printf("Bind parameter (6) for update failed: %s", sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
		}

		// step to 1st row of data
		ret = sqlite3_step(stmt);
		if (ret != SQLITE_DONE && ret != SQLITE_OK) // see documentation, this can return more values as success
		{
			AnsiString as;
			as.printf("Failed to step: %d, %s", ret, sqlite3_errmsg(pDb));
			pMemo->Lines->Add(as);
			break;
		}

		sqlite3_reset(stmt);

	} while (false);
	// cleanup
	if (NULL != stmt) sqlite3_finalize(stmt);
	// if (NULL != pDb) sqlite3_close(pDb);
	// sqlite3_shutdown();
	return;

}


static void fillTableAccountValuesInsertBudget(sqlite3* pDb, TMemo *pMemo,
	int idAccount, int idCostUnit, double valueCredit) {

	fillTableAccountValuesInsert(pDb, pMemo, idAccount, idCostUnit, 0.0f, valueCredit, valueCredit, 3);
	fillTableAccountValuesInsert(pDb, pMemo, idAccount,        101, valueCredit, 0.0f, -valueCredit, 3);

}


static void fillTableAccountValues(sqlite3 *pDb, TMemo *pMemo) {
	createTableAccountValues(pDb, pMemo);
	fillTableAccountValuesStep1(pDb, pMemo);
	fillTableAccountValuesStep2(pDb, pMemo);
	fillTableAccountValuesStep3(pDb, pMemo);
	fillTableAccountValuesStep4(pDb, pMemo);
	fillTableAccountValuesStep5(pDb, pMemo);
	fillTableAccountValuesStep6(pDb, pMemo);
	fillTableAccountValuesStep7(pDb, pMemo);
	fillTableAccountValuesStep8(pDb, pMemo);
	fillTableAccountValuesStep9(pDb, pMemo);
	fillTableAccountValuesStep10(pDb, pMemo);
}



static void createTableCostUnitReports(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"create table CostUnitReports ( " \
	"NO		INTEGER PRIMARY KEY AUTOINCREMENT, " \
	"NAME	TEXT NOT NULL " \
	")";

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitReports (NO, NAME) " \
	"values (1, 'Präsidium'), (2, 'Sportkommissionen'), (3, 'Leistungssport incl.'), (4, 'Leistungssport excl.'), (5, 'Praesidium full.');"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void createTableCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"create table CostUnitRprtItems ( " \
	"NO		    INTEGER PRIMARY KEY AUTOINCREMENT, " \
	"NORPRT 	    INTEGER NOT NULL, " \
	"NOCOSTUNIT  INTEGER NOT NULL " \
	");"
	;

	executeStatement(pDB, pMemo, strStmt);
}

static void createIndexCostUnitRprtItems(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"CREATE UNIQUE INDEX ICURI01 " \
	"ON CostUnitRprtItems (NORPRT, NOCOSTUNIT);"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableCostUnitRprtItems1(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitRprtItems (NORPRT, NOCOSTUNIT) " \
	"values (1, 101), (1, 102), (1, 103), (1, 104), (1, 105);"
	;

	executeStatement(pDB, pMemo, strStmt);
}

static void fillTableCostUnitRprtItems2(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitRprtItems (NORPRT, NOCOSTUNIT) " \
	"values (2, 401), (2, 402), (2, 403), (2, 404), (2, 405), " \
	"(2, 406), (2, 407), (2, 408), " \
	"(2, 411), (2, 421), (2, 422), " \
	"(2, 441), (2, 451), (2, 461), (2, 462), " \
	"(2, 471), (2, 481);"
	;

	executeStatement(pDB, pMemo, strStmt);
}

static void fillTableCostUnitRprtItems3(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitRprtItems (NORPRT, NOCOSTUNIT) " \
	"values (3, 401), (3, 402), (3, 403), (3, 404), " \
	"(3, 405), (3, 406), (3, 407), (3, 408);"
	;

	executeStatement(pDB, pMemo, strStmt);
}



static void fillTableCostUnitRprtItems4(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitRprtItems (NORPRT, NOCOSTUNIT) " \
	"values (4, 402), (4, 403), (4, 422);"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void fillTableCostUnitRprtItems5(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitRprtItems (NORPRT, NOCOSTUNIT) " \
	"values (5, 101), (5, 102), (5, 103), (5, 104), (5, 105), " \
	"(5, 106), (5, 107), (5, 108), (5, 109);"
	;

	executeStatement(pDB, pMemo, strStmt);
}




static void createTableCostUnitSummery(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"create table CostUnitSummery ( " \
	"NO			 INTEGER PRIMARY KEY AUTOINCREMENT, " \
	"NORPRT       INTEGER NOT NULL, " \
	"TYPE         TEXT NOT NULL, " \
	"ACCNO		 INTEGER NOT NULL, " \
	"ACCNAME		 TEXT NOT NULL, " \
	"COSTUNITNO   INTEGER NOT NULL, " \
	"COSTUNITTEXT TEXT NOT NULL, " \
	"VALUE        REAL NOT NULL, " \
	"PRNTCUNO	 INTEGER NOT NULL, " \
	"PRNTCUTEXT   TEXT NOT NULL " \
	");"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void insertTableCostUnitSummery3(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitSummery " \
	"(NORPRT, type, accno, accname, COSTUNITNO, PRNTCUNO, VALUE, COSTUNITTEXT, PRNTCUTEXT) " \
	"select 3, type, noAccount, textAccount, kostenstelle, idParentCostUnit, betrag, textCostUnit, parentCostUnit " \
	"from reportcompetitivesport;"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void insertTableCostUnitSummery2(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitSummery " \
	"(NORPRT, type, accno, accname, COSTUNITNO, PRNTCUNO, VALUE, COSTUNITTEXT, PRNTCUTEXT) " \
	"select 2, type, noAccount, textAccount, kostenstelle, idParentCostUnit, betrag, textCostUnit, parentCostUnit " \
	"from reportallsports;"
	;

	executeStatement(pDB, pMemo, strStmt);
}


static void insertTableCostUnitSummery5(sqlite3 *pDB, TMemo *pMemo) {

	char *strStmt =
	"insert into CostUnitSummery " \
	"(NORPRT, type, accno, accname, COSTUNITNO, PRNTCUNO, VALUE, COSTUNITTEXT, PRNTCUTEXT) " \
	"select 5, type, noAccount, textAccount, idParentCostUnit, idParentCostUnit, betrag, parentCostUnit, parentCostUnit " \
	"from reportpraesidiumforplaning;"
	;

	executeStatement(pDB, pMemo, strStmt);
}






/*
select av.idCostUnit, cu.idParentCostUnit, av.idAccount, ac.textAccount, cu.textCostUnit, av.valueDebit, av.valueCredit, av.valueFinal
from AccountValues av,
	Account ac,
	CostUnit cu
where av.idAccount = ac.idAccount
  and av.idCostUnit = cu.idCostUnit
order by av.idCostUnit, av.intType, av.idAccount
*/


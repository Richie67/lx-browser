//---------------------------------------------------------------------------

#ifndef LexwareDecoderH
#define LexwareDecoderH
#include <fmx.h>
#include <string>
//---------------------------------------------------------------------------

extern int doGenerateDataStructures(TMemo *pMemo, TComboBox *pComboBox);

extern int doGenerateJournal(TMemo *pMemo, const char *pszMandant, int year);

extern int doGenerateKontenRahmen(TMemo *pMemo);

extern std::string convertToDate(long numberDate);

extern long convertToDateNumber(int year, int month, int day);

extern int updateKostenstellen(int nr, int idx, int kst1, int kst2, TMemo *pMemo, const char *pszMandant, int year);

extern int deleteJournalRecord(int nr, TMemo *pMemo, const char *pszMandant, int year);

extern int updateJournalRecordKonto(int nr, int idx, int ktoSoll, int ktoHaben, TMemo *pMemo, const char *pszMandant, int year);

extern int updateJournalRecordAll(int nr, int idx, int ktoSoll, int ktoHaben, int kst1, int kst2, TMemo *pMemo);

#endif

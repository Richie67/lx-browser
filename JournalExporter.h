//---------------------------------------------------------------------------

#ifndef JournalExporterH
#define JournalExporterH

#include "Journal.h"
#include "KontoDefinition.h"
#include "Kostenstellen.h"
#include "sqlite3.h"
#include <fmx.h>

//---------------------------------------------------------------------------


extern void exportJournalToDatabase(UnicodeString filename, Journal &journal, KontenRahmen &konten, Kostenstellen &kostenstellen, TMemo *pMemo);

#endif

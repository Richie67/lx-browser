//---------------------------------------------------------------------------


#pragma hdrstop

#include <stdio.h>
#include "juldat.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


/*-------------------------- functions ------------------------------*/
/* Julianischer Tag (>=1):
 * Gegeben: tag, monat, jahr
 *
 * Die gregorianische Kalenderreform wird beruecksichtigt (der Tag, der
 * auf den 4. Oktober 1582 folgt ist der 15. October 1582
 * Tage nach dem 15. Oktober 1582 werden als "Gregorianischer Kalender"
 * bezeichnet. Der Julianische Tag beginnt um 12 Uhr GMT (Mittag).
 * Um beliebige Uhrzeiten beruecksichtigen zu koennen, werden die Tage
 * nicht als Integer- sondern als Gleitpunktzahlen angegeben.
 */

void GregorianDateToJulianDate(int iYear, int iMonth, int iDay, double *pdJD) {
   int atmp, btmp, monthp, yearp;
   double ctmp;
   if (iMonth > 2)
   {
	  monthp = iMonth + 1;
	  yearp = iYear;
   }
   else
   {
	  monthp = iMonth + 13;
	  yearp = iYear - 1;
   }
   if ((iYear > 1582) || (iYear == 1582 && iMonth >= 10)
	  || (iYear == 1582 && iMonth ==10 && iDay >= 15))
   {
	  atmp = iYear / 100;
      btmp = 2 - atmp + (atmp / 4);
   }
   else
      btmp = 0;
   atmp = 365.25 * yearp;
   ctmp = atmp;
   atmp = 30.6001 * monthp;
   ctmp =  ctmp + atmp;
   if (pdJD != NULL) {
		*pdJD = (ctmp + iDay + 1720994.5 + btmp);
   } /* if */

} /* GregorianDateToJulianDate */

/* gregorian_date: Umrechnung Julianischer Tag 
   in (Tag, Monat, Jahr) */

void JulianDateToGregorianDate(double dJD, int *piYear, int *piMonth, int *piDay) {
   int atmp, btmp, ctmp, dtmp, etmp, gtmp, ztmp;
   double ftmp;
   // datum_t dd;
   int iYear, iMonth, iDay;

   ztmp = dJD + 0.5;
   ftmp = (dJD + 0.5) - ztmp;
   if (ztmp >= 2299161)
   {
	  gtmp = (ztmp - 1867216.25) / 36524.25;
	  ctmp = gtmp / 4;
	  atmp = ztmp + 1 + gtmp - ctmp;
   }
   else
	  atmp = ztmp;
   btmp = atmp + 1524;
   ctmp = (btmp - 122.1) / 365.25;
   dtmp = 365.25 * ctmp;
   etmp = ((btmp - dtmp) / 30.6001);
   ztmp = 30.6001 * etmp;
   // dd.tag = btmp - dtmp - ztmp + ftmp;
   iDay = btmp - dtmp - ztmp + ftmp;
   if (etmp > 13.5)
	  // dd.monat = etmp - 13;
	  iMonth = etmp - 13;
   else
	  // dd.monat = etmp - 1;
	  iMonth = etmp - 1;
   if (iMonth > 2.5)
	  // dd.jahr = ctmp - 4716;
	  iYear = ctmp - 4716;
   else
	  // dd.jahr = ctmp - 4715;
	  iYear = ctmp - 4715;
   if (piYear != NULL) {
	   *piYear = iYear;
   } /* if */
	if (piMonth != NULL) {
		*piMonth = iMonth;
	} /* if */
	if (piDay != NULL) {
		*piDay = iDay;
	} /* if */
} /* JulianDateToGregorianDate */



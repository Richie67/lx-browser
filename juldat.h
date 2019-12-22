//---------------------------------------------------------------------------

#ifndef juldatH
#define juldatH
//---------------------------------------------------------------------------


void GregorianDateToJulianDate(int iYear, int iMonth, int iDay, double *pdJD);

void JulianDateToGregorianDate(double iJD, int *piYear, int *piMonth, int *piDay);


#endif

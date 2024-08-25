//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("FormBudget.cpp", FrmBudget);
USEFORM("DlgSelectMandantAndYear.cpp", FrmDlgSelectMandantAndYear);
USEFORM("FrmMain.cpp", Form1);
USEFORM("FrmReports.cpp", FormReports);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TFrmBudget), &FrmBudget);
		Application->CreateForm(__classid(TFormReports), &FormReports);
		Application->CreateForm(__classid(TFrmDlgSelectMandantAndYear), &FrmDlgSelectMandantAndYear);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

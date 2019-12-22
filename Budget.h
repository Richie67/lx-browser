//---------------------------------------------------------------------------

#ifndef BudgetH
#define BudgetH
//---------------------------------------------------------------------------


class tcBudget {
public:
	double bdgt_Praesidium;
	double bdgt_RK_Allgemein;
	double bdgt_RK_Sachkosten;
	double bdgt_RK_Personalkosten;
	double bdgt_IFS_Allgemein;
	double bdgt_IFS_Sachkosten;
	double bdgt_IFS_Personalkosten;
	double bdgt_RH_Allgemein;
	double bdgt_IH_Allgemein;
	double bdgt_SLB_Allgemein;
	double bdgt_IAD_Allgemein;
	double bdgt_ISH_Allgemein;
	double bdgt_RD_Allgemein;
	double bdgt_Jugend_Allgemein;

	double egnl_Praesidium;
	double egnl_RK_Allgemein;
	double egnl_RK_Sachkosten;
	double egnl_RK_Personalkosten;
	double egnl_IFS_Allgemein;
	double egnl_IFS_Sachkosten;
	double egnl_IFS_Personalkosten;
	double egnl_RH_Allgemein;
	double egnl_IH_Allgemein;
	double egnl_SLB_Allgemein;
	double egnl_IAD_Allgemein;
	double egnl_ISH_Allgemein;
	double egnl_RD_Allgemein;
    double egnl_Jugend_Allgemein;

public:
	__fastcall tcBudget() {
		init();
	}
	__fastcall void init() {
		this->bdgt_Praesidium = 0.0;
		this->bdgt_RK_Allgemein = 0.0;
		this->bdgt_RK_Sachkosten = 0.0;
		this->bdgt_RK_Personalkosten = 0.0;
		this->bdgt_IFS_Allgemein = 0.0;
		this->bdgt_IFS_Sachkosten = 0.0;
		this->bdgt_IFS_Personalkosten = 0.0;
		this->bdgt_RH_Allgemein = 0.0;
		this->bdgt_IH_Allgemein = 0.0;
		this->bdgt_SLB_Allgemein = 0.0;
		this->bdgt_IAD_Allgemein = 0.0;
		this->bdgt_ISH_Allgemein = 0.0;
		this->bdgt_RD_Allgemein = 0.0;
		this->bdgt_Jugend_Allgemein = 0.0;
		this->egnl_Praesidium = 0.0;
		this->egnl_RK_Allgemein = 0.0;
		this->egnl_RK_Sachkosten = 0.0;
		this->egnl_RK_Personalkosten = 0.0;
		this->egnl_IFS_Allgemein = 0.0;
		this->egnl_IFS_Sachkosten = 0.0;
		this->egnl_IFS_Personalkosten = 0.0;
		this->egnl_RH_Allgemein = 0.0;
		this->egnl_IH_Allgemein = 0.0;
		this->egnl_SLB_Allgemein = 0.0;
		this->egnl_IAD_Allgemein = 0.0;
		this->egnl_ISH_Allgemein = 0.0;
		this->egnl_RD_Allgemein = 0.0;
        this->egnl_Jugend_Allgemein = 0.0;
	}

	__fastcall void loadFromRegistry();
	__fastcall void saveIntoRegistry();

};




#endif

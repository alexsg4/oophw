#pragma once
#include "Project.h"
#include "RamblerU.h"


class wxTextCtrl;
class wxStaticText;
class wxChoice;
class wxChecBox;

class dAdd : public wxDialog
{

public:
	dAdd(wxWindow *parent, int id, const wxString& title);
	virtual ~dAdd();


private:
	wxWindow *m_parent = nullptr;
	
	wxPanel *pMain = nullptr;

	wxButton* bOK = nullptr;
	wxButton* bCancel = nullptr;

	wxBoxSizer* vBox = nullptr;
	wxFlexGridSizer* sFields = nullptr;

	wxStaticText* tType = nullptr;
	wxChoice *type = nullptr;
	wxArrayString choices;
	wxStaticText* tMake = nullptr;
	wxTextCtrl* make = nullptr;
	wxStaticText* tModel = nullptr;
	wxTextCtrl* model = nullptr;
	wxStaticText* tYear = nullptr;
	wxTextCtrl* year = nullptr;
	wxStaticText* tDamage = nullptr;
	wxCheckBox* damage = nullptr;



	wxBoxSizer* buttons = nullptr;

	void OnAdd(wxCommandEvent &event);
	void OnQuit(wxCommandEvent &event);
	static const unsigned ID_OK = 700;
	static const unsigned ID_CAN = 701;


	const Vehicle* generateVeh() const;

};

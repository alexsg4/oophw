#pragma once
#include "Project.h"


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
	wxStaticText* tDoors = nullptr;
	wxChoice* doors = nullptr;
	wxStaticText* tDamage = nullptr;
	wxCheckBox* damage = nullptr;


	int gType = 0;
	std::string gMake;
	std::string gModel;
	unsigned gYear = 0;
	unsigned gDoors = 0;
	wxBoxSizer* buttons = nullptr;

	void OnAdd(wxCommandEvent &event);
	void OnQuit(wxCommandEvent &event);
	void OnCheck(wxCommandEvent &event);
	void OnDoors(wxCommandEvent &event);
	static const unsigned ID_OK = 700;
	static const unsigned ID_CAN = 701;
	static const unsigned ID_CHK = 702;
	static const unsigned ID_DOOR = 703;

public:
	int getType() const;
	std::string getMake() const;
	std::string getModel() const;
	unsigned getYear() const;
	bool isDamaged() const;
	unsigned getDoors() const;
};

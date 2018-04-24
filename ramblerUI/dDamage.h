#include "Project.h"

class wxStdOutputStream;

class Vehicle;

class dDamage : public wxDialog
{
private:
	Vehicle ** toDamage = nullptr;

	void OnClose(wxCommandEvent& event);
	void OnDmg(wxCommandEvent& event);
	void OnAdd(wxCommandEvent& event);
	void OnDef(wxCommandEvent& event);

	wxVector<wxPoint> marker;

	wxTextCtrl* defText = nullptr;
	wxChoice* gPart = nullptr;
	wxChoice* gDef = nullptr;
	wxFlexGridSizer* choiceBox = nullptr;

	const unsigned ID_ADD = 100;
	const unsigned ID_DEF = 101;

	wxArrayString getPartChoices() const;
	wxArrayString getDefectChoices(const unsigned part) const;

	bool clearDisplay = true;

public:

	dDamage(Vehicle*, wxWindow* parent, const int id = wxID_ANY, const wxString& title="Adaugare defecte");
	virtual ~dDamage();


};
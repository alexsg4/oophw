#include "Project.h"
#include "RArray.h"

class wxStdOutputStream;

class Vehicle;

class dDamage : public wxDialog
{
private:
	Vehicle ** toDamage = nullptr;

	void OnClose(wxCommandEvent& event);
	void OnDmg(wxCommandEvent& event);


private:
	RArray<unsigned> partList;
	RArray<unsigned> dmgList;

public:

	dDamage(Vehicle*, wxWindow* parent, const int id = wxID_ANY, const wxString& title="Adaugare defecte");
	virtual ~dDamage();


};
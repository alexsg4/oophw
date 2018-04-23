#include "Project.h"


class wxStdOutputStream;
class Vehicle;

class dDiag : public wxDialog
{
private:
	Vehicle ** toDiag;

	void OnClose(wxCommandEvent& event);
	void OnFix(wxCommandEvent& event);

public:

	dDiag(Vehicle*, wxWindow* parent, const int id = wxID_ANY, const wxString& title="Diagnostic");
	virtual ~dDiag();


};
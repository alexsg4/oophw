#pragma once
#include "Project.h"
#include <wx/hyperlink.h>
#include <wx/statline.h>

class dAbout : public wxDialog
{
public:
	dAbout(const wxString& title = _T("Info"));

	void OnQuit(wxCommandEvent& event);

};

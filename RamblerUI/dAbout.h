#pragma once
#include "Project.h"
#include "wx/hyperlink.h"
#include "wx/statline.h"

class dAbout : public wxDialog
{
public:
	dAbout(const wxString& title);

	void OnQuit(wxCommandEvent& event);

};

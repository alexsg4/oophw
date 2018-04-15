#pragma once
#include "Project.h"
#include "dAbout.h"

class UIMainFrame : public wxFrame
{

public:
	UIMainFrame(const wxString& title);
	~UIMainFrame();

	void OnStart(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
};

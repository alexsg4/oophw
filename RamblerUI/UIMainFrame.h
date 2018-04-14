#pragma once
#include "Project.h"

#include "wx/hyperlink.h"
#include "wx/statline.h"
#include "wx/stattext.h"

class UIMainFrame : public wxFrame
{

public:
	UIMainFrame(const wxString& title);
	~UIMainFrame();

	void OnStart(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
};

class dAbout : public wxDialog
{
public:
	dAbout(const wxString& title);

	void OnQuit(wxCommandEvent& event);

};
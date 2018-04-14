#pragma once
#include "wx/wx.h"

class UIMainFrame : public wxFrame
{

private:
	const wxColor colBg = wxColor("#ABD0FF");
	const wxColor colFg = wxColor("#185CB2");
	const wxColor colAccent1 = wxColor("#FFB225");
	const wxColor colAccent2 = wxColor("#FFC864");
	const wxColor colAccent3 = wxColor("#B27708");

public:
	UIMainFrame(const wxString& title);
	~UIMainFrame();

	void OnStart(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
};


#pragma once
#include "wx/wx.h"

class UIMainFrame : public wxFrame
{
public:
	UIMainFrame(const wxString& title);
	~UIMainFrame();

	void OnQuit(wxCommandEvent& event);
};


#pragma once
#include "Project.h"

#include <wx/dcbuffer.h>

//#include "icon.xpm"
//#include "banner.xpm"

class dAbout;

class UIGarageFrame;

class UIMainFrame : public wxFrame
{

public:
	UIMainFrame(const wxString& title);
	~UIMainFrame();

private:
	
	wxPanel * pTopGraphics = nullptr;
	wxPanel * pMenu = nullptr;
	
	wxImage image;
	wxBitmap resized;
	int w = 0, h = 0;

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void render(wxDC& dc);

	void OnStart(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
};

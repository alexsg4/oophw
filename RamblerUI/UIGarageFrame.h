#pragma once
#include "Project.h"
#include "wx/menu.h"

#include "dAbout.h"

class UIGarageFrame : public wxFrame
{
private:

	//Menubar
	wxMenuBar * menuBar = nullptr;
	wxMenu* file = nullptr;
	wxMenu* edit = nullptr;
	
	//TODO implement
	wxMenu* race = nullptr;
	
	wxMenu* help = nullptr;

	//Sizers
	wxBoxSizer* vBox = nullptr;
	wxFlexGridSizer* sVehGrid = nullptr;
	wxBoxSizer* hBox = nullptr;
	wxGridSizer* sVehMenuGrid = nullptr;
	wxGridSizer* sVehSpecGrid = nullptr;

	//Panels

	wxPanel* pVehicles = nullptr;
	

public:
	UIGarageFrame(const wxString& title);
	~UIGarageFrame();

	//events

	void OnQuit(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);
};


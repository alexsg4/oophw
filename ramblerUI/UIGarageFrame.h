#pragma once
#include "Project.h"

#include <wx/menu.h>
#include <wx/stdstream.h>
#include <wx/wfstream.h>

#include <wx/textdlg.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>

class dAbout;

//Rambler includes
#include "RamblerU.h"

class UIGarageFrame : public wxFrame
{
private:

	//sensible default
	//OPTIONAL
	static const unsigned FLEET_MAX = 500;

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
	//TODO
	wxPanel* pVehicles = nullptr;

	//Data
	RArray<Vehicle*> fleet;
	static const unsigned initSize = 5;
	

public:
	UIGarageFrame(const wxString& title);
	~UIGarageFrame();

	//events

	void OnQuit(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);
	
	void OnClear(wxCommandEvent& event);
	
	void OnPopl(wxCommandEvent& event);




};


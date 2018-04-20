#pragma once
#include "Project.h"

#include <wx/menu.h>
#include <wx/stdstream.h>
#include <wx/wfstream.h>
#include <wx/sstream.h>

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


	wxBoxSizer* vehBox = nullptr;

	//Panels
	//TODO
	wxScrolledWindow* pVehicles = nullptr;

	//Data
	RArray<Vehicle*> fleet;
	static const unsigned initSize = 5;


public:
	UIGarageFrame(const wxString& title);
	virtual ~UIGarageFrame();

	//Dynamically update menus
	virtual void Refresh(bool eraseBackground = true, const wxRect *rect = NULL) override;


	//events

	//file
	void OnPopl(wxCommandEvent& event);
	void OnClear(wxCommandEvent& event);
	void OnQuit(wxCommandEvent & event);
	
/*
	//edit
	void OnAdd(wxCommandEvent& event);
	void OnRem(wxCommandEvent& event);
	void OnDiag(wxCommandEvent& event);
	void OnFix(wxCommandEvent& event);
	void OnUpg(wxCommandEvent& event);
*/
	//race
		//TODO implement

	//help
	void OnAbout(wxCommandEvent & event);
	
	//TODO implement
	//void OnCtrl(wxCommandEvent & event);

	//other methods

	wxPanel* generateEntry(Vehicle* veh, wxWindow* parent) const;

	




};


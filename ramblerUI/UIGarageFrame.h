#pragma once
#include "Project.h"

#include <wx/menu.h>
#include <wx/stdstream.h>
#include <wx/sstream.h>

#include <wx/textdlg.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>
#include <wx/dataview.h>

//Rambler includes
#include "RamblerU.h"

class dAbout;
class RIndexListModel;

class UIGarageFrame : public wxFrame
{
private:

	//sensible default
	//OPTIONAL: max fleet size
	static const unsigned FLEET_MAX = 500;
	static const unsigned dataID = 100;

	//stores currently selected fleet items by id
	static RArray<unsigned> dSelection;

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
	wxDataViewListCtrl* dVehicles = nullptr;
	RIndexListModel* mdVehicles = nullptr;

	//Data
	RArray<Vehicle*> fleet;
	static const unsigned initSize = 5;


public:
	UIGarageFrame(const wxString& title);
	void updateFleetDisplay();
	virtual ~UIGarageFrame();

	//Dynamically update menus
	 void updateMenuBar();


	//events

	//file
	void OnPopl(wxCommandEvent& event);
	void OnClear(wxCommandEvent& event);
	void OnQuit(wxCommandEvent & event);
	
	//edit
	//void OnAdd(wxCommandEvent& event);
	void OnRem(wxCommandEvent& event);
	//void OnDiag(wxCommandEvent& event);
	//void OnFix(wxCommandEvent& event);
	//void OnUpg(wxCommandEvent& event);

	//race
		//TODO implement

	//help
	void OnAbout(wxCommandEvent & event);
	
	//TODO implement
	//void OnCtrl(wxCommandEvent & event);

	//other methods

	void makeEntry(Vehicle* veh, wxVector<wxVariant> & entry, const int id = 0);

	void selectChangeHandler(wxDataViewEvent& event);




};


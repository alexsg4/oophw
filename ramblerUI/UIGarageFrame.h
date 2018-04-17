#pragma once
#include "Project.h"

#include <wx/menu.h>
#include <wx/stdstream.h>
#include <wx/wfstream.h>

class dAbout;

//Rambler includes
#include "RArray.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"

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

	//Data
	RArray<Vehicle*> fleet;
	static const unsigned initSize = 5;
	

public:
	UIGarageFrame(const wxString& title);
	~UIGarageFrame();

	//events

	void OnQuit(wxCommandEvent & event);
	void OnAbout(wxCommandEvent & event);

	// fleet functions
	void populateFleet(RArray<Vehicle*> &fleet, unsigned elementsToAdd);


};


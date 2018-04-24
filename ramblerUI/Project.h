#pragma once
// Header containing various info about the app, styles and other global includes 

//wxIncludes
#include <wx/wx.h>
#include <ctime>

#define _STR(s) #s
#define STR(s) _STR(s)

//App info
static const wxString ATitle = wxT("Rambler Garage");
static const wxString AVersion = wxT("0.3.0");
static const wxString ALTitle = ATitle + wxT(" v") + AVersion;
static const wxString AAuthor = wxT("Alexandru Stanciu");
static const wxString AYear = wxT("2018");

//Window
static const wxSize AMinSize(500, 350);

//IDs
	//Windows
	enum class fID
	{
		IND = 500,		//dummy index - temporary
		MAIN,			//mainMenu
		GAR,			//garage
		FLP,			//fleetPanel
	};

	//Events
	enum class eID
	{
		IND = 600,		//dummy index - temporary
		POPL,			//populate fleet
		CLR,			//clear fleet
		ADD,			//add vehicle
		REM,			//remove vehicle
		DIAG,			//diagnose vehicle
		FIX,			//fix vehicle
		DMG,			//damage vehicle
		UPG,			//upgrade vehicle
		SRAC,			//send vehicle to race
		RAC,			//start race
		CLRAC,			//clear race starting line
		LRAC,			//show racing leaderboards
		CTRL			//show race keyboard controls
	};


//Color styles
static const wxColor colBg = wxColor("#073799");
static const wxColor colL1 = wxColor("#EBFCFF");
static const wxColor colL2 = wxColor("#859CCC");
static const wxColor colW = wxColor("#FFFFFF");
static const wxColor colB = wxColor("#000000");
static const wxColor colAccent1 = wxColor("#FFAF8C");
static const wxColor colAccent2 = wxColor("#CC3214");

//Font styles
static const wxFont fHeading(10, wxDEFAULT, wxNORMAL, wxBOLD);

//Links
static const wxString ALicense = wxT("https://www.wxwidgets.org/about/licence/");

//copy
static const wxString AAbout = (STR(ASSETS) + wxString("/about.txt"));


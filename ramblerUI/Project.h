#pragma once
// Header containing various info about the app, styles and other global includes 

//wxIncludes
#include <wx/wx.h>
#include <ctime>

#define _STR(s) #s
#define STR(s) _STR(s)

//App info
static const wxString ATitle = wxT("Rambler Garage");
static const wxString AVersion = wxT("0.1.0");
static const wxString ALTitle = ATitle + wxT(" v") + AVersion;
static const wxString AAuthor = wxT("Alexandru Stanciu");
static const wxString AYear = wxT("2018");

//Window
static const wxSize AMinSize(500, 350);

//IDs
	//Frames
	enum class fID
	{
		IND = 500,		//dummy index - temporary
		MAIN,			//mainMenu
		GAR				//garage
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
		UPG,			//upgrade vehicle
		SRAC,			//send vehicle to race
		RAC,			//start race
		CLRAC,			//clear race starting line
		LRAC,			//show racing leaderboards
		CTRL			//show race keyboard controls
	};


//Color styles
static const wxColor colBg = wxColor("#ABD0FF");
static const wxColor colFg = wxColor("#185CB2");
static const wxColor colAccent1 = wxColor("#FFB225");
static const wxColor colAccent2 = wxColor("#FFC864");
static const wxColor colAccent3 = wxColor("#B27708");

//Font styles
static const wxFont fHeading(10, wxDEFAULT, wxNORMAL, wxBOLD);

//Links
static const wxString ALicense = wxT("https://www.wxwidgets.org/about/licence/");

//copy
static const wxString AAbout = 
wxT(
	"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."
);

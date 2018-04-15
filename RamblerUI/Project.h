#pragma once
/* Header containing various info about the app, styles and other global includes*/

//wxIncludes
#include "wx/wx.h"

//Rambler includes
#include "../OOP1-RamblerGarage/RArray.h"
#include "../OOP1-RamblerGarage/Car.h"
#include "../OOP1-RamblerGarage/Bike.h"
#include "../OOP1-RamblerGarage/Motorbike.h"


//App info
static const wxString ATitle = wxT("Rambler Garage");
static const wxString AVersion = wxT("0.1.0");
static const wxString ALTitle = ATitle + wxT(" v") + AVersion;
static const wxString AAuthor = wxT("Alexandru Stanciu");
static const wxString AYear = wxT("2018");

//Window
static const wxSize AMinSize(500, 350);

//IDs
	//Windows
	static const int ID_MAIN = 501;
	static const int ID_GAR = 502;
	//Events
	static const int ID_DIAG = 503;
	static const int ID_FIX = 504;
	static const int ID_UPG = 505;
	static const int ID_SRAC = 600;
	static const int ID_RAC = 601;
	static const int ID_CLRAC = 602;
	static const int ID_LRAC = 603;


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

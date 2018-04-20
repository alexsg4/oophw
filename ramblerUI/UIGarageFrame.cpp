#include "UIGarageFrame.h"
#include "dAbout.h"

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append((unsigned)eID::POPL, wxT("&Populate..."));
	file->Append((unsigned)eID::CLR, wxT("&Clear"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	
	edit = new wxMenu;
	edit->Append((unsigned)eID::ADD, wxT("&Add..."));
	edit->Append((unsigned)eID::REM, wxT("&Remove"));
	edit->AppendSeparator();
	edit->Append((unsigned)eID::DIAG, wxT("&Diagnose"));
	edit->Append((unsigned)eID::FIX, wxT("&Fix"));
	edit->Append((unsigned)eID::UPG, wxT("&Upgrade..."));
	edit->AppendSeparator();
	edit->Append((unsigned)eID::SRAC, wxT("&Send to Race"));

	race = new wxMenu;
	race->Append((unsigned)eID::RAC, wxT("&Start..."));
	race->Append((unsigned)eID::CLRAC, wxT("&Clear"));
	race->AppendSeparator();
	race->Append((unsigned)eID::LRAC, wxT("&Leaderboard..."));

	help = new wxMenu;
	help->Append(wxID_HELP, wxT("&Controls"));
	help->Append(wxID_ABOUT, wxT("&About"));

	menuBar->Append(file, wxT("&File"));
	menuBar->Append(edit, wxT("&Edit"));
	menuBar->Append(race, wxT("&Race"));
	menuBar->Append(help, wxT("&Help"));


	//Layout
	vBox = new wxBoxSizer(wxVERTICAL);
	pVehicles = new wxPanel(this, -1);
	
	vBox->Add(pVehicles, 1, wxEXPAND);


	//Events
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnQuit));
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAbout));


	//Frame properties

	SetMenuBar(menuBar);
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();

	//Data
	populateFleet(fleet, initSize);
	
}

UIGarageFrame::~UIGarageFrame()
{
}


void UIGarageFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	//show confirmation dialog
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, wxT("Are you sure?"), wxT("Exit"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

	if (dConfirmExit->ShowModal() == wxID_YES)
	{
		dConfirmExit->Destroy();
		Close(true);
	}
	else
	{
		dConfirmExit->Destroy();
	}
}

void UIGarageFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(wxT("About"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
}

void UIGarageFrame::OnClear(wxCommandEvent & event)
{

}

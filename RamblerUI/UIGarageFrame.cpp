#include "UIGarageFrame.h"

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append(wxID_ANY, wxT("&Populate..."));
	file->Append(wxID_ANY, wxT("&Clear"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	
	edit = new wxMenu;
	edit->Append(wxID_ADD, wxT("&Add..."));
	edit->Append(wxID_REMOVE, wxT("&Remove"));
	edit->AppendSeparator();
	edit->Append(ID_DIAG, wxT("&Diagnose"));
	edit->Append(ID_FIX, wxT("&Fix"));
	edit->Append(ID_UPG, wxT("&Upgrade..."));
	edit->AppendSeparator();
	edit->Append(ID_SRAC, wxT("&Send to Race"));

	race = new wxMenu;
	race->Append(ID_RAC, wxT("&Start..."));
	race->Append(ID_CLRAC, wxT("&Clear"));
	race->AppendSeparator();
	race->Append(ID_LRAC, wxT("&Leaderboard..."));

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
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	SetMenuBar(menuBar);
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();
}

UIGarageFrame::~UIGarageFrame()
{
}

void UIGarageFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(wxT("About"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
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
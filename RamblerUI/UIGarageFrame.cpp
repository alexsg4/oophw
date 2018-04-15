#include "UIGarageFrame.h"

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append(wxID_EXIT, wxT("&Populate..."));
	file->Append(wxID_EXIT, wxT("&Clear"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	
	edit = new wxMenu;
	edit->Append(wxID_ANY, wxT("&Add..."));
	edit->Append(wxID_ANY, wxT("&Remove"));
	edit->AppendSeparator();
	edit->Append(wxID_ANY, wxT("&Diagnose"));
	edit->Append(wxID_ANY, wxT("&Fix"));
	edit->Append(wxID_ANY, wxT("&Upgrade..."));
	edit->AppendSeparator();
	edit->Append(wxID_ANY, wxT("&Send to Race"));

	race = new wxMenu;
	race->Append(wxID_ANY, wxT("&Start..."));
	race->Append(wxID_ANY, wxT("&Clear"));
	race->AppendSeparator();
	race->Append(wxID_ANY, wxT("&Leaderboard..."));

	help = new wxMenu;
	help->Append(wxID_HELP, wxT("&Conntrols"));
	help->Append(wxID_ABOUT, wxT("&About"));



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
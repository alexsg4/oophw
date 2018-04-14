#include "UIMainFrame.h"

UIMainFrame::UIMainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel* pTopGraphics = new wxPanel(this, wxID_TOP);
	pTopGraphics->SetBackgroundColour(colBg);

	auto size = this->GetClientSize();
	pTopGraphics->SetMinSize(wxSize(size.GetWidth(), size.GetHeight()/3));

	wxPanel* pMenu = new wxPanel(this, wxID_BOTTOM);
	pMenu->SetBackgroundColour(colAccent1);

	wxButton* bStart = new wxButton(pMenu, wxID_HOME, wxT("Start"));
	Connect(wxID_HOME, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnStart));
	
	wxButton* bAbout = new wxButton(pMenu, wxID_ABOUT, wxT("About"));
	Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnAbout));
	
	wxButton* bQuit = new wxButton(pMenu, wxID_EXIT, wxT("Quit"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnQuit));

	wxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	wxSizer* sButtonGrid = new wxGridSizer(1, 5, 5);

	pMenu->SetSizer(sButtonGrid);
	sButtonGrid->Add(bStart, 0, wxALIGN_CENTER | wxALL, 1);
	sButtonGrid->Add(bAbout, 0, wxALIGN_CENTER | wxALL, 1);
	sButtonGrid->Add(bQuit, 0, wxALIGN_CENTER | wxALL, 1);
	
	vBox->Add(pTopGraphics, 1, wxEXPAND);
	vBox->Add(pMenu, 1, wxEXPAND);

	SetSizer(vBox);
	SetMinSize(wxSize(600, 500));
	bStart->SetFocus();

	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	Centre();
}


UIMainFrame::~UIMainFrame()
{
}

void UIMainFrame::OnStart(wxCommandEvent & event)
{	
	//TODO
	//Launch a new window with the workshop
}

void UIMainFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(wxT("About"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
}


void UIMainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
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

dAbout::dAbout(const wxString & title)
	: wxDialog(nullptr, -1, title, wxDefaultPosition, wxSize(300, 400))
{

	wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hBox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vTextBox = new wxBoxSizer(wxVERTICAL);

	wxStaticText* heading = new wxStaticText(this, -1, ALTitle);
	heading->SetFont(fHeading);

	wxTextCtrl* about = new wxTextCtrl(this, -1, AAbout, wxDefaultPosition, wxDefaultSize,
		wxTE_READONLY | wxTE_LEFT | wxTE_BESTWRAP | wxTE_MULTILINE);
	about->SetMargins(5);
	
	//(this, -1, AAbout,
		//wxDefaultPosition, wxSize(-1, -1), wxALIGN_LEFT);

	wxHyperlinkCtrl* link = new wxHyperlinkCtrl(this, -1, wxT("License"), ALicense);

	wxButton* bQuit = new wxButton(this, wxID_EXIT, wxT("Close"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dAbout::OnQuit));

	const wxString wx = wxT("This project uses wxWidgets. See license below:");
	wxStaticText* lic = new wxStaticText(this, -1, wx,
		wxDefaultPosition, wxSize(-1, -1), wxALIGN_LEFT);

	const wxString crt = wxT("Copyright ") + AAuthor + " " + AYear + "\n";
	wxStaticText* cr = new wxStaticText(this, -1, crt);

	hBox->Add(bQuit, 1);
	
	vTextBox->Add(about, 100, wxEXPAND | wxALL, 10);
	vTextBox->Add(lic, 0, wxALL, 10);
	vTextBox->Add(link, 0, wxALIGN_LEFT | wxALL, 10);
	
	wxStaticLine* sLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(1, 1));
	vBox->Add(heading, 0, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(vTextBox, 1, wxEXPAND | wxALIGN_CENTER);
	vBox->Add(sLine, 0, wxEXPAND | wxALL, 10);
	vBox->Add(cr, 0, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(hBox, 0, wxALIGN_RIGHT | wxALL , 10);

	SetSizer(vBox);
	ShowModal();
	Centre();
	Destroy();
}

void dAbout::OnQuit(wxCommandEvent & event)
{
	Close(true);
}

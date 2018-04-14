#include "UIMainFrame.h"

UIMainFrame::UIMainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel* pTopGraphics = new wxPanel(this, wxID_TOP);
	pTopGraphics->SetBackgroundColour(colBg);

	auto size = this->GetSize();
	pTopGraphics->SetMinSize(wxSize(size.GetWidth(), size.GetHeight()*2/3 ));

	wxPanel* pMenu = new wxPanel(this, wxID_BOTTOM);
	//pMenu->SetMinSize(wxSize(size.GetWidth(), size.GetHeight() / 3));
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
	//TODO
	//show a dialog with info about the project, licensing and credits
}


void UIMainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	//TODO
	//show confirmation dialog
	//exit application
	Close(true);
}
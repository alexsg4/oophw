#include "UIMainFrame.h"
#include "UIGarageFrame.h"
#include "dAbout.h"

UIMainFrame::UIMainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel* pTopGraphics = new wxPanel(this, wxID_TOP);
	pTopGraphics->SetBackgroundColour(colL1);

	auto size = this->GetClientSize();
	pTopGraphics->SetMinSize(wxSize(size.GetWidth(), size.GetHeight()/3));

	wxPanel* pMenu = new wxPanel(this, wxID_BOTTOM);
	pMenu->SetBackgroundColour(colBg);

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
	SetMinSize(AMinSize);
	bStart->SetFocus();
	
	//TODO add icon
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	Centre();
}


UIMainFrame::~UIMainFrame()
{
}

void UIMainFrame::OnStart(wxCommandEvent & event)
{	
	UIGarageFrame* GarageFrame = new UIGarageFrame(ALTitle);
	if (GarageFrame)
	{
		Close();
		GarageFrame->Show(true);
	}
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
		dConfirmExit->Close();
		Close();
	}
	else
	{	
		dConfirmExit->Close();
	}

}

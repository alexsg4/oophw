#include "UIMainFrame.h"

UIMainFrame::UIMainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxButton* button = new wxButton(panel, wxID_EXIT, wxT("Quit"),
		wxPoint(20, 20));

	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnQuit));
	button->SetFocus();


	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	Centre();
}


UIMainFrame::~UIMainFrame()
{
}


void UIMainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}
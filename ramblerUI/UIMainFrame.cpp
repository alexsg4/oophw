#include "UIMainFrame.h"
#include "UIGarageFrame.h"
#include "dAbout.h"

UIMainFrame::UIMainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	pTopGraphics = new wxPanel(this, wxID_TOP);
	pTopGraphics->SetBackgroundColour(colL1);

	image.LoadFile(AImg + "banner.png", wxBITMAP_TYPE_PNG);

	auto size = this->GetClientSize();
	pTopGraphics->SetMinSize(wxSize(size.GetWidth(), size.GetHeight()/3));

	pMenu = new wxPanel(this, wxID_BOTTOM);
	pMenu->SetBackgroundColour(colBg);

	wxButton* bStart = new wxButton(pMenu, wxID_HOME, _T("Atelier"));
	Connect(wxID_HOME, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnStart));
	
	wxButton* bAbout = new wxButton(pMenu, wxID_ABOUT, _T("Despre"));
	Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnAbout));
	
	wxButton* bQuit = new wxButton(pMenu, wxID_EXIT, _T("Iesire"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(UIMainFrame::OnQuit));

	//TODO fix and re-enable
	//Connect(wxEVT_PAINT, wxPaintEventHandler(UIMainFrame::OnPaint));
	
	Connect(wxEVT_SIZE, wxSizeEventHandler(UIMainFrame::OnSize));

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
	
	SetIcon(wxIcon(AImg+"icon.xpm", wxBITMAP_TYPE_XPM));
	Centre();
}


UIMainFrame::~UIMainFrame()
{
}

void UIMainFrame::OnPaint(wxPaintEvent & event)
{
	if (!pTopGraphics) { return; }
	
	wxPaintDC dc(pTopGraphics);
	render(dc);
}

void UIMainFrame::OnSize(wxSizeEvent & event)
{
	auto size = this->GetClientSize();
	pTopGraphics->SetMinSize(wxSize(size.GetWidth(), size.GetHeight() / 3));
	
	Refresh();
	//skip the event.
	event.Skip();
}

void UIMainFrame::render(wxDC & dc)
{
	int w1 = 0, h1 = 0;
	dc.GetSize(&w1, &h1);

	if (w1 != w || h1 != h)
	{
		resized = wxBitmap(image.Scale(w1, h1));
		w = w1; h = h1;
		dc.DrawBitmap(resized, 0, 0);
	}
	else {
		dc.DrawBitmap(resized, 0, 0);
	}
}

void UIMainFrame::OnStart(wxCommandEvent & event)
{	
	UIGarageFrame* GarageFrame = new UIGarageFrame(ALTitle);
	if (GarageFrame)
	{
		this->Close();
		GarageFrame->Show(true);
	}
}

void UIMainFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(_T("Info"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
}

void UIMainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	//show confirmation dialog
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, _T("Sunteti sigur?"), _T("Iesire"), 
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
		
	dConfirmExit->SetYesNoLabels("Da", "Nu");

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

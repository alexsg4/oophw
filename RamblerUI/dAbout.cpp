#include "dAbout.h"

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
	vBox->Add(hBox, 0, wxALIGN_RIGHT | wxALL, 10);

	SetSizer(vBox);
	ShowModal();
	Centre();
	Destroy();
}

void dAbout::OnQuit(wxCommandEvent & event)
{
	Close(true);
}

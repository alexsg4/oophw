#include "dDiag.h"

#include "Vehicle.h"
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/stdstream.h>
#include <wx/sstream.h>

dDiag::dDiag(Vehicle* toDiag, wxWindow * parent, const int id, const wxString & title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxSize(400, 450), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	this->toDiag = &toDiag;

	wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* bBox = new wxBoxSizer(wxHORIZONTAL);
	
	wxString vehData(toDiag->getNameType() + toDiag->getMake() + " " + toDiag->getModel());

	wxStaticText* heading = new wxStaticText(this, -1, vehData);
	heading->SetFont(fHeading);

	wxTextCtrl* defText = new wxTextCtrl(this, -1, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_DONTWRAP);
	
	std::ostream dOut(defText);
	toDiag->diagnose(dOut);
	defText->SetMargins(5,15);

	wxButton* bClose = new wxButton(this, wxID_EXIT, wxT("Close"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDiag::OnClose));
	
	wxButton* bFix = new wxButton(this, (unsigned)eID::FIX, wxT("Fix"));
	Connect((unsigned)eID::FIX, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDiag::OnFix));

	bBox->Add(bFix, 1, wxALL, 5);
	bBox->Add(bClose, 1, wxALL, 5);

	vBox->Add(heading, 1, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(defText, 10, wxALIGN_CENTER| wxEXPAND | wxALL, 10);
	vBox->Add(bBox, 1, wxALIGN_RIGHT | wxALL, 10);

	wxBoxSizer* mBox = new wxBoxSizer(wxVERTICAL);
	mBox->Add(vBox, 1, wxEXPAND | wxALL, 5);
	SetMinSize(wxSize(400, 450));
	SetSizer(vBox);
	ShowModal();
	Destroy();
}

dDiag::~dDiag()
{
}

void dDiag::OnClose(wxCommandEvent & event)
{
	Close();
}

void dDiag::OnFix(wxCommandEvent & event)
{
	//*toDiag->fix();
}
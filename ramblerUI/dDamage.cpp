#include "dDamage.h"

#include "Vehicle.h"
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/stdstream.h>
#include <wx/sstream.h>

dDamage::dDamage(Vehicle* toDamage, wxWindow * parent, const int id, const wxString & title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxSize(400, 450))
{
	this->toDamage = &toDamage;

	wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* bBox = new wxBoxSizer(wxHORIZONTAL);
	
	wxString vehData(toDamage->getNameType() + toDamage->getMake() + " " + toDamage->getModel());

	wxStaticText* heading = new wxStaticText(this, -1, vehData);
	heading->SetFont(fHeading);

	wxStaticText* tPart = new wxStaticText(this, -1, wxT("Alegeti componenta"));
	wxStaticText* tDefect = new wxStaticText(this, -1, wxT("Alegeti defectul:"));


	wxTextCtrl* defText = new wxTextCtrl(this, -1, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_DONTWRAP);
	
	std::ostream dOut(defText);

	defText->SetMargins(5,-1);
	defText->SetBackgroundColour("#000000");
	defText->SetForegroundColour("#FFFFFF");
	defText->SetFont(fHeading);

	wxButton* bClose = new wxButton(this, wxID_EXIT, wxT("Inchide"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDamage::OnClose));
	
	wxButton* bDamage = new wxButton(this, (unsigned)eID::DMG, wxT("Adauga defecte"));
	Connect((unsigned)eID::DMG, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDamage::OnDmg));

	bBox->Add(bDamage, 1, wxALL, 5);
	bBox->Add(bClose, 1, wxALL, 5);

	vBox->Add(heading, 1, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(tPart, 1, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(tDefect, 1, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(defText, 10, wxEXPAND | wxALL, 10);
	vBox->Add(bBox, 1, wxALIGN_RIGHT | wxALL, 5);

	wxBoxSizer* mBox = new wxBoxSizer(wxVERTICAL);
	mBox->Add(vBox, 1, wxEXPAND | wxALL, 5);
	//SetBackgroundColour(colL2);
	//SetForegroundColour(colW);
	SetSizer(mBox);
	ShowModal();
	Destroy();
}

dDamage::~dDamage()
{
}

void dDamage::OnClose(wxCommandEvent & event)
{
	Close();
}

void dDamage::OnDmg(wxCommandEvent & event)
{
	for (unsigned i = 0; i < partList.size(); i++)
	{
		for (unsigned j = 0; j < dmgList.size(); j++)
		{
			(*toDamage)->getPart(partList[i]).applyDamage(dmgList[j]);
		}
	}

	(*toDamage)->diagnose();
	this->Close();
}

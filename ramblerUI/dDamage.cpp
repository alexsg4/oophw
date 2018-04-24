#include "dDamage.h"

#include "Vehicle.h"
#include "Defect.h"
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
	choiceBox = new wxFlexGridSizer(2, wxSize(5, 5));

	wxString vehData(toDamage->getNameType() + toDamage->getMake() + " " + toDamage->getModel());

	wxStaticText* heading = new wxStaticText(this, -1, vehData);
	heading->SetFont(fHeading);

	wxStaticText* tPart = new wxStaticText(this, -1, wxT("Componenta: \t\t"));
	gPart = new wxChoice(this, ID_DEF, wxDefaultPosition, wxDefaultSize, getPartChoices());
	gPart->SetSelection(0);
	
	Connect(ID_DEF, wxEVT_CHOICE,
		wxCommandEventHandler(dDamage::OnDef));
	
	
	wxStaticText* tDefect = new wxStaticText(this, -1, wxT("Defect: \t\t"));
	gDef = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, getDefectChoices(gPart->GetSelection()));
	gDef->SetSelection(0);
	
	choiceBox->Add(tPart, 1);
	choiceBox->Add(gPart, 1);
	choiceBox->Add(tDefect, 1);
	choiceBox->Add(gDef, 1);

	choiceBox->AddGrowableCol(2, 1);


	defText = new wxTextCtrl(this, -1, "Momentan nu exista defecte.",
	wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_DONTWRAP);
	
	std::ostream dOut(defText);

	defText->SetMargins(5,-1);
	defText->SetBackgroundColour("#000000");
	defText->SetForegroundColour("#FFFFFF");
	defText->SetFont(fHeading);

	wxButton* bClose = new wxButton(this, wxID_EXIT, wxT("Inchide"));
	Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDamage::OnClose));
	
	wxButton* bDamage = new wxButton(this, (unsigned)eID::DMG, wxT("OK"));
	Connect((unsigned)eID::DMG, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDamage::OnDmg));

	wxButton* bSave = new wxButton(this, ID_ADD, wxT("Adauga"));
	Connect(ID_ADD, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dDamage::OnAdd));

	bBox->Add(bDamage, 1, wxALL, 5);
	bBox->Add(bSave, 1, wxALL, 5);
	bBox->Add(bClose, 1, wxALL, 5);

	vBox->Add(heading, 1, wxALIGN_LEFT | wxALL, 10);
	vBox->Add(choiceBox, 1, wxALIGN_CENTER | wxALL, 5);
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
	unsigned i = 0, j = 0;
	for (unsigned k = 0; k< marker.size(); k++)
	{
		i = static_cast<unsigned>(marker[k].x);
		j = static_cast<unsigned>(marker[k].y);
		(*toDamage)->getPart(i).applyDamage(j);
	}
	(*toDamage)->diagnose();
	this->Close();
}


void dDamage::OnDef(wxCommandEvent & event)
{
	int part = gPart->GetSelection();
	auto strings = getDefectChoices(part);
	gDef->Clear();
	for (int  i = 0; i < strings.size(); i++)
	{
		gDef->Append(strings[i]);
	}
	gDef->SetSelection(0);
}

void dDamage::OnAdd(wxCommandEvent & event)
{
	//get part choice
	int part = gPart->GetSelection();
	
	if (!gDef) { return; }
	
	//get defect choice
	int defect = gDef->GetSelection();
	
	wxPoint toAdd(part, defect);
	bool canAdd = true;
	for (unsigned i = 0; i < marker.size(); i++)
	{
		if(marker[i]==toAdd) 
		{
			canAdd = false;
			break;
		}
	}

	if (canAdd)
	{
		marker.push_back(wxPoint(part, defect));

		//print part name and defect to defText
		std::ostream dOut(defText);
		if (clearDisplay)
		{
			defText->Clear();
			clearDisplay = false;
		}
		dOut << gPart->GetStringSelection() << ": " << gDef->GetStringSelection() << "\n";
	}
}

wxArrayString dDamage::getPartChoices() const
{
	wxArrayString choices;
	for (unsigned i = 0; i < (*toDamage)->getNumParts(); i++)
	{
		wxString part;
		part << (*toDamage)->getPart(i).generateName();
		choices.Add(part);
	}

	return choices;
}

wxArrayString dDamage::getDefectChoices(const unsigned part) const
{
	wxArrayString choices;
	for (unsigned i = 0; i < (*toDamage)->getPart(part).getPossibleDefectsNum(); i++)
	{
		wxString defect;
		Defect* def = (*toDamage)->getPart(part).getDefect(i);
		
		if (def != nullptr) 
		{	
			defect << def->getName();	
			choices.Add(defect);
		}
	}

	return choices;
}
#include "dAdd.h"

#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>

dAdd::dAdd(wxWindow* parent, int id, const wxString& title)
	: wxDialog(parent, id, title)
{
	m_parent = parent;

	pMain = new wxPanel(this, -1, wxDefaultPosition, wxSize(400,250));

	vBox = new wxBoxSizer(wxVERTICAL);
	
	sFields = new wxFlexGridSizer(2, wxSize(10,10));
	//############FIELDS###################

	tType = new wxStaticText(pMain, -1, wxT("Tip vehicul:"));
	choices.Add(wxT("Automobil"));
	choices.Add(wxT("Motocicleta"));
	choices.Add(wxT("Bicicleta"));
	type = new wxChoice(pMain, -1, wxDefaultPosition, wxDefaultSize, choices);
	type->SetSelection(0);
	sFields->Add(tType, 1);
	sFields->Add(type, 1);


	tMake = new wxStaticText(pMain, -1, wxT("Marca:"));
	make = new wxTextCtrl(pMain, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	make->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC));
	sFields->Add(tMake, 1);
	sFields->Add(make, 1);


	tModel = new wxStaticText(pMain, -1, wxT("Model:"));
	model = new wxTextCtrl(pMain, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	model->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC));
	sFields->Add(tModel, 1);
	sFields->Add(model, 1);


	tYear = new wxStaticText(pMain, -1, wxT("An:"));
	year = new wxTextCtrl(pMain, -1, AYear, wxDefaultPosition, wxDefaultSize);
	year->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
	sFields->Add(tYear, 1);
	sFields->Add(year, 1);


	tDamage = new wxStaticText(pMain, -1, wxT("Defect:"));
	damage = new wxCheckBox(this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	sFields->Add(tDamage, 1);
	wxBoxSizer* hBox = new wxBoxSizer(wxHORIZONTAL);
	hBox->Add(damage, 1, wxALIGN_CENTER | wxALL, 10);
	sFields->Add(hBox, 1);

	//#######################################
	pMain->SetSizer(sFields);

	buttons = new wxBoxSizer(wxHORIZONTAL);
	bOK = new wxButton(this, ID_OK, wxT("OK"));
	Connect(ID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dAdd::OnAdd));
	
	bCancel = new wxButton(this, ID_CAN, wxT("Cancel"));
	Connect(ID_CAN, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dAdd::OnQuit));

	buttons->Add(bOK, 1, wxBOTTOM | wxALL, 5);
	buttons->Add(bCancel, 1, wxBOTTOM | wxALL, 5);

	vBox->Add(pMain, 1, wxEXPAND | wxALL, 10);
	vBox->Add(buttons, 0, wxALIGN_RIGHT | wxALL, 5);

	SetSizer(vBox);
	ShowModal();
	Destroy();
}

dAdd::~dAdd()
{
	delete generatedVeh;
}

void dAdd::OnAdd(wxCommandEvent & event)
{
	//get vehicle data from fields
	Part::Type vType = Part::Type::ANY;
	int gType = type->GetSelection();

	std::string gMake = make->GetValue().ToStdString();
	std::string gModel = model->GetValue().ToStdString();

	if (gMake.empty() || gModel.empty())
	{
		return;
	}


	unsigned long _gYear = 0;
	year->GetValue().ToULong(&_gYear);
	unsigned gYear = static_cast<unsigned>(_gYear);


	//generate vehicle
	switch ((Part::Mount) gType)
	{
	case Part::Mount::CAR:
		generatedVeh = new Car(gMake, gModel, gYear);
		break;
	case Part::Mount::MOTO:
		generatedVeh = new Motorbike(gMake, gModel, gYear);
		break;
	case Part::Mount::BIKE:
		generatedVeh = new Bike(gMake, gModel, gYear);
		break;
	case Part::Mount::ANY:
		generatedVeh = nullptr;
		break;
	}

	if (generatedVeh && damage->IsChecked())
	{
		generatedVeh->applyRandomDamage();
	}

	//add to parent
	Close();
}

void dAdd::OnQuit(wxCommandEvent & event)
{
	Close();
}

Vehicle * dAdd::getVehicle() const
{
	return generatedVeh;
}

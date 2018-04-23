#include "dAdd.h"

#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>

dAdd::dAdd(wxWindow* parent, int id, const wxString& title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxSize(250, 300))
{
	m_parent = parent;

	pMain = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);

	vBox = new wxBoxSizer(wxVERTICAL);
	
	sFields = new wxFlexGridSizer(2, wxSize(10,10));
	//############FIELDS###################

	tType = new wxStaticText(pMain, -1, wxT("Tip vehicul:"));
	choices.Add(wxT("Automobil"));
	choices.Add(wxT("Motocicleta"));
	choices.Add(wxT("Bicicleta"));
	type = new wxChoice(pMain, ID_DOOR, wxDefaultPosition, wxDefaultSize, choices);
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

	choices.clear();
	choices.Add(wxT("2")); choices.Add(wxT("4"));
	tDoors = new wxStaticText(pMain, -1, wxT("Nr usi:"));
	doors = new wxChoice(pMain, -1, wxDefaultPosition, wxDefaultSize, choices);
	doors->SetSelection(0);
	sFields->Add(tDoors, 1);
	sFields->Add(doors, 1);

	tDamage = new wxStaticText(pMain, -1, wxT("Defect:"));
	damage = new wxCheckBox(pMain, ID_CHK, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	
	sFields->Add(tDamage, 1);
	sFields->Add(damage, 1);
	Connect(ID_CHK, wxEVT_CHECKBOX, wxCommandEventHandler(dAdd::OnCheck));

	//#######################################
	pMain->SetSizer(sFields);

	buttons = new wxBoxSizer(wxHORIZONTAL);
	bOK = new wxButton(this, ID_OK, wxT("OK"));
	Connect(ID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dAdd::OnAdd));
	
	bCancel = new wxButton(this, ID_CAN, wxT("Cancel"));
	Connect(ID_CAN, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(dAdd::OnQuit));

	Connect(ID_DOOR, wxEVT_CHOICE,
		wxCommandEventHandler(dAdd::OnDoors));

	buttons->Add(bOK, 1, wxBOTTOM | wxALL, 5);
	buttons->Add(bCancel, 1, wxBOTTOM | wxALL, 5);

	vBox->Add(pMain, 1, wxEXPAND | wxALL, 10);
	vBox->Add(buttons, 0, wxALIGN_RIGHT | wxALL, 5);

	SetSizer(vBox);
	SetBackgroundColour(colL2);
	ShowModal();
	Destroy();
}

dAdd::~dAdd(){}

void dAdd::OnAdd(wxCommandEvent & event)
{
	//get vehicle data from fields
	gType = type->GetSelection();
	
	gMake = make->GetValue().ToStdString();
	gModel = model->GetValue().ToStdString();

	if (gMake.empty() || gModel.empty())
	{
		return;
	}

	unsigned long _gYear = 0;
	year->GetValue().ToULong(&_gYear);
	gYear = static_cast<unsigned>(_gYear);
	gDoors = static_cast<unsigned> (doors->GetSelection());


	Close();
}

void dAdd::OnQuit(wxCommandEvent & event) { Close(); }

void dAdd::OnCheck(wxCommandEvent & event)
{
	bool x = damage->GetValue();
	
	if (damage->HitTest(damage->GetPosition()) == wxHT_WINDOW_INSIDE)
	{
		damage->SetValue(!x);
	}
}

void dAdd::OnDoors(wxCommandEvent & event)
{
	//Allow door selection for cars only
	doors->Enable((type->GetSelection() == 0));
}

int dAdd::getType() const { return gType; }
std::string dAdd::getMake() const { return gMake; }
std::string dAdd::getModel() const { return gModel; }
unsigned dAdd::getYear() const { return gYear; }
bool dAdd::isDamaged() const { return  damage->IsChecked(); }

unsigned dAdd::getDoors() const
{
	return gDoors;
}

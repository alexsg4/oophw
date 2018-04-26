#include "UIGarageFrame.h"

#include "dAbout.h"
#include "dAdd.h"
#include "dDiag.h"
#include "dDamage.h"

//statics
RArray<unsigned> UIGarageFrame::dSelection;

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append((unsigned)eID::POPL, _T("&Adaugare multipla..."));
	file->Append((unsigned)eID::CLR, _T("&Eliberare garaj"));
	file->Append(wxID_EXIT, _T("&Iesire"));
	
	edit = new wxMenu;
	edit->Append((unsigned)eID::ADD, _T("&Adauga..."));
	edit->Append((unsigned)eID::REM, _T("&Inlatura"));
	edit->AppendSeparator();
	edit->Append((unsigned)eID::DIAG, _T("&Diagnostic..."));
	edit->Append((unsigned)eID::DMG, _T("&Defecte..."));
	
	//edit->Append((unsigned)eID::UPG, _T("&Upgrade..."));
	//edit->AppendSeparator();
	//edit->Append((unsigned)eID::SRAC, _T("&Send to Race"));

	//race = new wxMenu;
	//race->Append((unsigned)eID::RAC, _T("&Start..."));
	//race->Append((unsigned)eID::CLRAC, _T("&Clear"));
	//race->AppendSeparator();
	//race->Append((unsigned)eID::LRAC, _T("&Leaderboard..."));

	help = new wxMenu;
	//help->Append(wxID_HELP, _T("&Controls"));
	help->Append(wxID_ABOUT, _T("&Despre"));

	menuBar->Append(file, _T("&Atelier"));
	menuBar->Append(edit, _T("&Vehicule"));
	//menuBar->Append(race, _T("&Race"));
	menuBar->Append(help, _T("&Ajutor"));

	//Layout
	vBox = new wxBoxSizer(wxVERTICAL);

	pVehicles = new wxScrolledWindow(this, -1, wxDefaultPosition, wxDefaultSize);
	dVehicles = new wxDataViewListCtrl(pVehicles, dataID, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES | wxDV_MULTIPLE);
	
	//Events
	
	Connect((unsigned)eID::POPL, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnPopl));
	
	Connect((unsigned)eID::CLR, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnClear));
	
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnQuit));

	Connect((unsigned)eID::ADD, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAdd));
	
	Connect((unsigned)eID::REM, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnRem));

	Connect((unsigned)eID::DIAG, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnDiag));

	Connect((unsigned)eID::DMG, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnDmg));

	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAbout));

	Connect(dataID, wxEVT_DATAVIEW_SELECTION_CHANGED,
		wxDataViewEventHandler(UIGarageFrame::OnSelect));

	dVehicles->AppendTextColumn(_T("#"));
	dVehicles->AppendTextColumn(_T("Tip"));
	dVehicles->AppendTextColumn(_T("Marca"));
	dVehicles->AppendTextColumn(_T("Model"));
	dVehicles->AppendTextColumn(_T("An"));
	dVehicles->AppendTextColumn(_T("Stare"));

	vehBox = new wxBoxSizer(wxVERTICAL);
	vehBox->Add(dVehicles, 1, wxEXPAND);

	//Data
	populateFleet(fleet, initSize);
	updateFleetDisplay();

	pVehicles->SetSizer(vehBox);
	pVehicles->SetBackgroundColour(colAccent1);
	pVehicles->FitInside();
	pVehicles->SetScrollRate(5, 5);
	
	vBox->Add(pVehicles, 1, wxEXPAND);
	

	//Frame properties

	SetMenuBar(menuBar);
	SetIcon(wxIcon(AImg + "icon.xpm", wxBITMAP_TYPE_XPM));
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();
	updateMenuBar();

}

//TODO optimize
	void UIGarageFrame::updateFleetDisplay(bool append)
{
	if(dVehicles->GetItemCount()){ dVehicles->DeleteAllItems(); }
	
	wxVector<wxVariant> temp;
	for (unsigned i = 0; i < fleet.size(); i++)
	{
		makeEntry(fleet[i], temp, i + 1);
		if(!temp.empty())
		{ 
			dVehicles->AppendItem(temp);
		}
	}
}

UIGarageFrame::~UIGarageFrame()
{
}

//TODO add the other menu options
void UIGarageFrame::updateMenuBar()
{	
	if (fleet.size() == FLEET_MAX)
	{
		edit->Enable((unsigned)eID::ADD, false);
		file->Enable((unsigned)eID::POPL, false);
	}
	else
	{
		edit->Enable((unsigned)eID::ADD, true);
		file->Enable((unsigned)eID::POPL, true);
	}

	if (fleet.isEmpty())
	{
		file->Enable((unsigned)eID::CLR, false);
	}
	else
	{
		file->Enable((unsigned)eID::CLR, true);
	}

	if (dSelection.isEmpty() || fleet.isEmpty())
	{
		edit->Enable((unsigned)eID::REM, false);
		edit->Enable((unsigned)eID::DIAG, false);
		edit->Enable((unsigned)eID::DMG, false);
		//edit->Enable((unsigned)eID::FIX, false);
		//edit->Enable((unsigned)eID::UPG, false);
	}
	else
	{
		if (dSelection.size() == 1)
		{
			edit->Enable((unsigned)eID::DIAG, true);
			//edit->Enable((unsigned)eID::FIX, true);
			//edit->Enable((unsigned)eID::UPG, true);
			edit->Enable((unsigned)eID::DMG, true);
		}
		else
		{
			edit->Enable((unsigned)eID::DIAG, false);
			//edit->Enable((unsigned)eID::FIX, false);
			//edit->Enable((unsigned)eID::UPG, false);
			edit->Enable((unsigned)eID::DMG, false);
		}
		edit->Enable((unsigned)eID::REM, true);
	}
}

//File
void UIGarageFrame::OnPopl(wxCommandEvent & event)
{
	wxString message;

	message.Printf("Numar vehicule [max %u]", FLEET_MAX - fleet.size());
	wxTextEntryDialog* txtEntry = new wxTextEntryDialog(this, message, _T("Adaugare vehicule"));

	txtEntry->SetTextValidator(wxFILTER_DIGITS);
	txtEntry->SetMaxLength(3);
	wxMessageDialog* msgResult = new wxMessageDialog(this, _T("Info"), _T("Info"));
	message.Clear();

	if (txtEntry->ShowModal() == wxID_OK)
	{
		unsigned long x = 0;
		if (txtEntry->GetValue().ToULong(&x) && (fleet.size() + x <= FLEET_MAX) && x!=0)
		{
			populateFleet(fleet, x);
			
			if(x>1) { message.Printf("Au fost adaugate %lu de vehicule.", x); }
			else { message.Printf("A fost adaugat un vehicul."); }
			msgResult->SetMessage(message);

			msgResult->ShowModal();
			msgResult->Destroy();

			updateFleetDisplay();
			updateMenuBar();
		}
		
		else
		{
			message.Printf("Numar invalid de vehicule!");
			msgResult->SetMessage(message);
			msgResult->ShowModal();
			msgResult->Destroy();
		}

		txtEntry->Close();
	}
	else
	{
		txtEntry->Close();
	}

}

void UIGarageFrame::OnClear(wxCommandEvent & event)
{
	//show confirmation dialog
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, _T("Sunteti sigur?"), _T("Eliberare garaj"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	dConfirmExit->SetYesNoLabels("Da", "Nu");
	if (dConfirmExit->ShowModal() == wxID_YES)
	{
		if (!fleet.isEmpty()) { fleet.erase(); }
		dConfirmExit->Destroy();

		updateMenuBar();
		updateFleetDisplay();
	}
	else
	{
		dConfirmExit->Destroy();
	}

}

void UIGarageFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	//show confirmation dialog
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, _T("Sunteti sigur?"), _T("Iesire"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	dConfirmExit->SetYesNoLabels("Da", "Nu");
	if (dConfirmExit->ShowModal() == wxID_YES)
	{
		dConfirmExit->Destroy();
		Close();
	}
	else
	{
		dConfirmExit->Destroy();
	}
}

//edit
void UIGarageFrame::OnAdd(wxCommandEvent & event)
{
	//launch add vehicle dialog
	dAdd* add = new dAdd(this, -1, "Adaugare Vehicule");
	add->Show(true);

	//generate a vehicle based on user input
	Vehicle* toAdd = nullptr;

	if (add->getMake().empty() || add->getModel().empty()) { return; }

	//generate vehicle
	switch ((Part::Mount) add->getType())
	{
	case Part::Mount::CAR:
		toAdd = new Car(add->getMake(), add->getModel(), add->getYear(), add->getDoors());
		break;
	case Part::Mount::MOTO:
		toAdd = new Motorbike(add->getMake(), add->getModel(), add->getYear());
		break;
	case Part::Mount::BIKE:
		toAdd = new Bike(add->getMake(), add->getModel(), add->getYear());
		break;
	}

	if (toAdd && add->isDamaged())
	{
		toAdd->applyRandomDamage();
		toAdd->diagnose();
	}


	if (toAdd && fleet.size() < FLEET_MAX)
	{
		//add vehicle to fleet 
		fleet.add(toAdd);
		
		wxVector<wxVariant> temp;
		makeEntry(fleet[fleet.size()-1], temp, fleet.size());
		if(!temp.empty())
		{
			dVehicles->AppendItem(temp);
		}
		updateMenuBar();
	}
}

void UIGarageFrame::OnRem(wxCommandEvent & event)
{
	if (dSelection.size() == fleet.size())
	{
		if (!fleet.isEmpty()) 
		{ 
			fleet.erase(); 
			updateFleetDisplay();
			updateMenuBar();
			return;
		}
	}

	if (dSelection.size() == 1)
	{
		fleet.removeById(dSelection[0]);
		dVehicles->DeleteItem(dSelection[0]);
		updateFleetDisplay();
		updateMenuBar();
		return;
	}

	dSelection.sort();
	
	unsigned *temp = new unsigned[dSelection.size()];
	for (unsigned i = 0; i < dSelection.size(); i++)
	{
		temp[i] = dSelection[i];
	}

	fleet.removeMultiple(temp, dSelection.size());

	updateFleetDisplay();
	updateMenuBar();
}

void UIGarageFrame::OnDiag(wxCommandEvent & event)
{
	dDiag* diag = new dDiag(fleet[dSelection[0]], this);
	diag->Show(true);

	updateFleetDisplay();
	updateMenuBar();
}

void UIGarageFrame::OnDmg(wxCommandEvent & event)
{
	dDamage* dmg = new dDamage(fleet[dSelection[0]], this);
	dmg->Show(true);

	updateFleetDisplay();
	updateMenuBar();
}


//race

//help
void UIGarageFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout();
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
}

void UIGarageFrame::makeEntry(Vehicle* veh, wxVector<wxVariant> & entry, const unsigned id)
{
	if(!entry.empty()) { entry.clear(); }
	if (!veh) { return; }
	
	wxString label;
	int temp = static_cast<int>(id);
	label.Printf("%d", temp);
	entry.push_back(wxVariant(label));

	entry.push_back(wxVariant(veh->getNameType()));
	
	entry.push_back(wxVariant(veh->getMake()));

	entry.push_back(wxVariant(veh->getModel()));

	label.clear();
	int year = static_cast<int>(veh->getYear());
	label.Printf("%d", year);
	entry.push_back(wxVariant(label));

	label.clear();
	int cond = static_cast<int>(veh->getCondition());
	label.Printf("%d %%", cond);
	entry.push_back(wxVariant(label));
}

void UIGarageFrame::OnSelect(wxDataViewEvent& event)
{
	dSelection.erase();
	
	for (int i = 0; i < dVehicles->GetItemCount(); i++)
	{
		if (dVehicles->IsRowSelected(i))
		{
			dSelection.add(i);
		}
	}
	
	updateMenuBar();
}

#include "UIGarageFrame.h"
#include "dAbout.h"
#include "RIndexListModel.h"
#include "dAdd.h"


//statics
RArray<unsigned> UIGarageFrame::dSelection;

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append((unsigned)eID::POPL, wxT("&Populate..."));
	file->Append((unsigned)eID::CLR, wxT("&Clear"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	
	edit = new wxMenu;
	edit->Append((unsigned)eID::ADD, wxT("&Add..."));
	edit->Append((unsigned)eID::REM, wxT("&Remove"));
	edit->AppendSeparator();
	edit->Append((unsigned)eID::DIAG, wxT("&Diagnose"));
	edit->Append((unsigned)eID::FIX, wxT("&Fix"));
	edit->Append((unsigned)eID::UPG, wxT("&Upgrade..."));
	//edit->AppendSeparator();
	//edit->Append((unsigned)eID::SRAC, wxT("&Send to Race"));

	//race = new wxMenu;
	//race->Append((unsigned)eID::RAC, wxT("&Start..."));
	//race->Append((unsigned)eID::CLRAC, wxT("&Clear"));
	//race->AppendSeparator();
	//race->Append((unsigned)eID::LRAC, wxT("&Leaderboard..."));

	help = new wxMenu;
	//help->Append(wxID_HELP, wxT("&Controls"));
	help->Append(wxID_ABOUT, wxT("&About"));

	menuBar->Append(file, wxT("&File"));
	menuBar->Append(edit, wxT("&Edit"));
	//menuBar->Append(race, wxT("&Race"));
	menuBar->Append(help, wxT("&Help"));

	//Layout
	vBox = new wxBoxSizer(wxVERTICAL);

	pVehicles = new wxScrolledWindow(this, -1, wxDefaultPosition, wxDefaultSize);
	dVehicles = new wxDataViewListCtrl(pVehicles, dataID, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES | wxDV_MULTIPLE);

	mdVehicles = new RIndexListModel(fleet, 0);
	//dVehicles->AssociateModel(mdVehicles);
	
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

	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAbout));

	Connect(dataID, wxEVT_DATAVIEW_SELECTION_CHANGED,
		wxDataViewEventHandler(UIGarageFrame::OnSelect));

	dVehicles->AppendTextColumn(wxT("#"));
	dVehicles->AppendTextColumn(wxT("Tip"));
	dVehicles->AppendTextColumn(wxT("Marca"));
	dVehicles->AppendTextColumn(wxT("Model"));
	dVehicles->AppendTextColumn(wxT("An"));
	dVehicles->AppendTextColumn(wxT("Stare"));

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
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();
	updateMenuBar();

}

//TODO optimize
void UIGarageFrame::updateFleetDisplay()
{
	wxVector<wxVariant> temp;
	dVehicles->DeleteAllItems();

	for (unsigned i = 0; i < fleet.size(); i++)
	{
		temp.clear();
		makeEntry(fleet[i], temp, i + 1);
		dVehicles->AppendItem(temp);
	}
	//mdVehicles->Reset(fleet.size());
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
		edit->Enable((unsigned)eID::FIX, false);
		edit->Enable((unsigned)eID::UPG, false);
	}
	else
	{
		if (dSelection.size() == 1)
		{
			edit->Enable((unsigned)eID::DIAG, true);
			edit->Enable((unsigned)eID::FIX, true);
			edit->Enable((unsigned)eID::UPG, true);
		}
		else
		{
			edit->Enable((unsigned)eID::DIAG, false);
			edit->Enable((unsigned)eID::FIX, false);
			edit->Enable((unsigned)eID::UPG, false);
		}
		edit->Enable((unsigned)eID::REM, true);
	}
}

//File
void UIGarageFrame::OnPopl(wxCommandEvent & event)
{
	wxString message;

	message.Printf("Numar vehicule [max %u]", FLEET_MAX - fleet.size());
	wxTextEntryDialog* txtEntry = new wxTextEntryDialog(this, message, wxT("Adaugare vehicule"));
	txtEntry->SetTextValidator(wxFILTER_DIGITS);
	txtEntry->SetMaxLength(3);
	
	wxMessageDialog* msgResult = new wxMessageDialog(this, wxT("Info"), wxT("Info"));
	message.Clear();

	if (txtEntry->ShowModal() == wxID_OK)
	{
		unsigned long x = 0;
		if (txtEntry->GetValue().ToULong(&x) && (fleet.size() + x <= FLEET_MAX) && x!=0)
		{
			populateFleet(fleet, x);
			//mdVehicles->Reset(fleet.size());
			
			if(x>1) { message.Printf("Au fost adaugate %lu de vehicule", x); }
			else { message.Printf("A fost adaugat un vehicul"); }
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
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, wxT("Sunteti sigur?"), wxT("Eliberare garaj"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

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
	wxMessageDialog* dConfirmExit = new wxMessageDialog(nullptr, wxT("Are you sure?"), wxT("Exit"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

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

void UIGarageFrame::OnAdd(wxCommandEvent & event)
{
	//launch add vehicle dialog
	dAdd* add = new dAdd(this, -1, "Adaugare Vehicule");
	add->Show(true);

	//generate a vehicle base on user data
	auto toAdd = add->getVehicle();
	if (toAdd && fleet.size() < FLEET_MAX)
	{
		//add vehicle to fleet 
		fleet.add(toAdd);
		updateFleetDisplay();
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

//edit

//race

//help
void UIGarageFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(wxT("About"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
}


void UIGarageFrame::makeEntry(Vehicle* veh, wxVector<wxVariant> & entry, const int id)
{
	wxString label;

	entry.push_back(wxVariant(id));

	label.Printf("%s", veh->getNameType());
	entry.push_back(wxVariant(label));
	label.Clear();
	
	label.Printf("%s", veh->getMake());
	entry.push_back(wxVariant(label));
	label.Clear();

	label.Printf("%s", veh->getModel());
	entry.push_back(wxVariant(label));
	label.Clear();

	int year = static_cast<int>(veh->getYear());
	entry.push_back(wxVariant(year));
	label.Clear();

	int cond = static_cast<int>(veh->getCondition());
	entry.push_back(wxVariant(cond));
}

void UIGarageFrame::OnSelect(wxDataViewEvent& event)
{
	dSelection.erase();
	
	for (unsigned i = 0; i < dVehicles->GetItemCount(); i++)
	{
		if (dVehicles->IsRowSelected(i))
		{
			dSelection.add(i);
		}
	}
	
	updateMenuBar();
}
#include "UIGarageFrame.h"
#include "dAbout.h"
#include "RIndexListModel.h"

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
	edit->AppendSeparator();
	edit->Append((unsigned)eID::SRAC, wxT("&Send to Race"));

	race = new wxMenu;
	race->Append((unsigned)eID::RAC, wxT("&Start..."));
	race->Append((unsigned)eID::CLRAC, wxT("&Clear"));
	race->AppendSeparator();
	race->Append((unsigned)eID::LRAC, wxT("&Leaderboard..."));

	help = new wxMenu;
	help->Append(wxID_HELP, wxT("&Controls"));
	help->Append(wxID_ABOUT, wxT("&About"));

	menuBar->Append(file, wxT("&File"));
	menuBar->Append(edit, wxT("&Edit"));
	menuBar->Append(race, wxT("&Race"));
	menuBar->Append(help, wxT("&Help"));

	//Layout
	vBox = new wxBoxSizer(wxVERTICAL);
	//TODO remove
	vehBox = new wxBoxSizer(wxVERTICAL);
	pVehicles = new wxScrolledWindow(this, -1, wxDefaultPosition, wxDefaultSize);
	dVehicles = new wxDataViewListCtrl(pVehicles, -1);

	mdVehicles = new RIndexListModel(fleet, initSize);
	//dVehicles->AssociateModel(mdVehicles);
	
	//Events
	
	Connect((unsigned)eID::POPL, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnPopl));
	
	Connect((unsigned)eID::CLR, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnClear));
	
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnQuit));
	
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAbout));


	dVehicles->AppendTextColumn(wxT("#"));
	dVehicles->AppendTextColumn(wxT("Tip"));
	dVehicles->AppendTextColumn(wxT("Marca"));
	dVehicles->AppendTextColumn(wxT("Model"));
	dVehicles->AppendTextColumn(wxT("An"));
	dVehicles->AppendTextColumn(wxT("Stare"));

	vehBox->Add(dVehicles, 1, wxEXPAND);

	//Data
	populateFleet(fleet, initSize);


	for (unsigned i = 0; i < fleet.size(); i++)
	{
		wxVector<wxVariant> temp;
		makeEntry(fleet[i], temp, i+1);
		dVehicles->AppendItem(temp);
		//mdVehicles->RowAppended();
	}



	pVehicles->SetSizer(vehBox);
	pVehicles->SetBackgroundColour(colAccent1);
	pVehicles->FitInside();
	pVehicles->SetScrollRate(5, 5);
	
	//TODO remove
	//pVehicles->SetSizer(vehBox);
	
	vBox->Add(pVehicles, 1, wxEXPAND);
	

	//Frame properties

	SetMenuBar(menuBar);
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();

}

UIGarageFrame::~UIGarageFrame()
{
}

//TODO add the other menu options
void UIGarageFrame::Refresh(bool eraseBackground, const wxRect * rect)
{
	wxFrame::Refresh(eraseBackground, rect);
	
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
		edit->Enable((unsigned)eID::REM, false);
	}
	else
	{
		file->Enable((unsigned)eID::CLR, true);
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
			
			if(x>1) { message.Printf("Au fost adaugate %lu de vehicule", x); }
			else { message.Printf("A fost adaugat un vehicul"); }
			msgResult->SetMessage(message);

			msgResult->ShowModal();
			msgResult->Destroy();

			Refresh();
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

		Refresh();
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
		Close(true);
	}
	else
	{
		dConfirmExit->Destroy();
	}
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

//TODO
void UIGarageFrame::makeEntry(Vehicle* veh, wxVector<wxVariant> & entry, const unsigned id)
{
	wxString label;

	label.Printf("%u", id);
	entry.push_back(wxVariant(label));
	label.Clear();

	label.Printf("%s", veh->getNameType());
	entry.push_back(wxVariant(label));
	label.Clear();
	
	label.Printf("%s", veh->getMake());
	entry.push_back(wxVariant(label));
	label.Clear();

	label.Printf("%s", veh->getModel());
	entry.push_back(wxVariant(label));
	label.Clear();

	label.Printf("%u", veh->getYear());
	entry.push_back(wxVariant(label));
	label.Clear();

	label.Printf("%i %% ", static_cast<int>(veh->getCondition()));
	entry.push_back(wxVariant(label));
	label.Clear();
}

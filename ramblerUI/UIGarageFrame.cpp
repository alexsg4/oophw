#include "UIGarageFrame.h"
#include "dAbout.h"

UIGarageFrame::UIGarageFrame(const wxString & title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	menuBar = new wxMenuBar;
	file = new wxMenu;
	
	file->Append(wxID_ANY, wxT("&Populate..."));
	file->Append(wxID_ANY, wxT("&Clear"));
	file->Append(wxID_EXIT, wxT("&Quit"));
	
	edit = new wxMenu;
	edit->Append(wxID_ADD, wxT("&Add..."));
	edit->Append(wxID_REMOVE, wxT("&Remove"));
	edit->AppendSeparator();
	edit->Append(ID_DIAG, wxT("&Diagnose"));
	edit->Append(ID_FIX, wxT("&Fix"));
	edit->Append(ID_UPG, wxT("&Upgrade..."));
	edit->AppendSeparator();
	edit->Append(ID_SRAC, wxT("&Send to Race"));

	race = new wxMenu;
	race->Append(ID_RAC, wxT("&Start..."));
	race->Append(ID_CLRAC, wxT("&Clear"));
	race->AppendSeparator();
	race->Append(ID_LRAC, wxT("&Leaderboard..."));

	help = new wxMenu;
	help->Append(wxID_HELP, wxT("&Controls"));
	help->Append(wxID_ABOUT, wxT("&About"));

	menuBar->Append(file, wxT("&File"));
	menuBar->Append(edit, wxT("&Edit"));
	menuBar->Append(race, wxT("&Race"));
	menuBar->Append(help, wxT("&Help"));


	//Layout
	vBox = new wxBoxSizer(wxVERTICAL);
	pVehicles = new wxPanel(this, -1);
	
	vBox->Add(pVehicles, 1, wxEXPAND);


	//Events
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnQuit));
	Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(UIGarageFrame::OnAbout));


	//Frame properties
	//SetIcon(wxIcon(wxT("rambler.ico"), wxBitmapType::wxBITMAP_TYPE_ICO));
	SetMenuBar(menuBar);
	SetMinSize(AMinSize);
	SetSizer(vBox);
	Centre();

	//Data
	populateFleet(fleet, initSize);
	
}

UIGarageFrame::~UIGarageFrame()
{
}

void UIGarageFrame::OnAbout(wxCommandEvent & event)
{
	dAbout* dialog = new dAbout(wxT("About"));
	//show a dialog with info about the project, licensing and credits
	dialog->Show(true);
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

void UIGarageFrame::populateFleet(RArray<Vehicle*> &fleet, unsigned elementsToAdd)
{
	if (!elementsToAdd)
	{
		return;
	}
	srand((unsigned)time(0));

	//open vehicle type generators for make and model
	wxString GDIR = wxT(STR(ASSETS));
	GDIR = GDIR + "/generators/";
	
	wxFFileInputStream fMake(GDIR + "genericMakes.in");
	wxFFileInputStream fModel(GDIR + "genericModels.in");

	wxStdInputStream make(fMake);
	wxStdInputStream model(fModel);

	//select apppropriate generator
	//for this example we will use the two generic files

	//count lines 
	unsigned mLines = 0, modLines = 0, mi = 0, modi = 0;
	std::string m, mod;

	if (fMake.IsOk() && fModel.IsOk())
	{
		while (std::getline(make, m))
		{
			mLines++;
		}

		while (std::getline(model, mod))
		{
			modLines++;
		}

	//TODO ensure rand() return different on every iteration 
		while (elementsToAdd)
	{
		//random choose vehicle type
		Part::Mount vehType = (Part::Mount)(rand() % Part::getPosTypes() + 1);

		//reset file pointers
		make.clear();
		make.seekg(0, std::ios::beg);

		model.clear();
		model.seekg(0, std::ios::beg);

		//clear strings
		m.clear();
		mod.clear();

		//random select lines for make and model
		mi = (rand() + elementsToAdd + 312341) % mLines + 1;
		modi = (rand() + elementsToAdd + 54837) % modLines + 1;

		//extract from files
		for (unsigned i = 0; i < mi; i++)
		{
			make.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		make >> m;

		for (unsigned i = 0; i < modi; i++)
		{
			model.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		model >> mod;

		//random select year (and doors for cars)
		unsigned year = 1950 + rand() % 150, doors = 0;

		//create new vehicle with make and model, add vehicle to list if possible
		Vehicle* toAdd = nullptr;
		switch (vehType)
		{
		case Part::Mount::CAR:
			doors = (rand() % 2) ? 2 : 4;
			toAdd = new Car(m, mod, year, doors);
			break;
		case Part::Mount::MOTO:
			toAdd = new Motorbike(m, mod, year);
			break;
		case Part::Mount::BIKE:
			toAdd = new Bike(m, mod, year);
			break;
		default:
			break;
		}

		//damage vehicle
		if (toAdd)
		{
			toAdd->applyRandomDamage();

			fleet.add(toAdd);

			//decrement elements
			elementsToAdd--;
		}
	}

	}
}

//TODO implement for UI
/*
void displayFleet(RArray<Vehicle*> &fleet)
{
	unsigned size = fleet.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (fleet[i]) { std::cout << i + 1 << ". " << *fleet[i] << "\n"; }
	}
	std::cout << "\n";
}

void damageVehicle(Vehicle * vehicle)
{
	vehicle->showPartsList();
	unsigned part = 0;
	while ((std::cout << "Alegeti componenta: " && !(std::cin >> part))
		|| (part > vehicle->getNumParts()))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Componenta nu este pe lista. Incercati din nou.\n";
	}
	part--;

	vehicle->getPart(part).showPossibleDefects();

	unsigned defect = 0;
	while ((std::cout << "Alegeti defectul: " && !(std::cin >> defect))
		|| (defect > vehicle->getPart(part).getNumDefects()))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Defectul nu este pe lista. Incercati din nou.\n";
	}
	defect--;
	vehicle->getPart(part).applyDamage(defect, true);
}
*/

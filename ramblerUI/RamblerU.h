#pragma once 

// Header containing the definitions of fleet operations. Similar to Rambler.h for ramblerConsole
#include "Project.h"

//Fleet and structures
#include "RArray.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"

#include <wx/stdstream.h>
#include <wx/wfstream.h>

//fleet wrappers

//TODO adapt for UI and uncomment
//void addVehicle(RArray<Vehicle*> &fleet, wxStdOutputStream& out);
//void diagnoseFleet(RArray<Vehicle*> &fleet, wxStdOutputStream& out);
//void damageVehicle(Vehicle* vehicle, wxStdOutputStream& out);


//##################################################################
/*
void addVehicle(RArray<Vehicle*> &fleet)
{
	std::cout << "Tipuri de vehicule disponibile: \n";
	for (unsigned i = 0; i <= Part::getPosTypes(); i++)
	{
		switch ((Part::Mount)i)
		{
		case Part::Mount::CAR:
			std::cout << i << ". Automobil \n";
			break;
		case Part::Mount::MOTO:
			std::cout << i << ". Motocicleta \n";
			break;
		case Part::Mount::BIKE:
			std::cout << i << ". Bicicleta \n";
			break;
		}
	}

	//ask user for type, make, model, year
	std::string make, model;
	unsigned year = 0, doors = 0, temp = 0;
	Part::Mount type;

	std::cout << "\nAti ales: ";

	while (!(std::cin >> temp) || (temp <= 0 || temp > 3))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Tip vehicul invalid. Incercati din nou. \n";
	}

	type = (Part::Mount)temp;

	std::cout << "Dati marca, modelul si anul fabricatiei: ";
	std::cin >> make >> model >> year;
	if (type == Part::Mount::CAR)
	{
		std::cout << "Dati numarul de usi [2 sau 4]: ";
		std::cin >> doors;
	}

	Vehicle* toAdd = nullptr;
	//create vehicle and add it to fleet if possible
	switch (type)
	{
	case Part::Mount::CAR:
		toAdd = new Car(make, model, year, doors);
		std::cout << "Masina a fost adaugata. \n";
		break;

	case Part::Mount::MOTO:
		toAdd = new Motorbike(make, model, year);
		std::cout << "Motocicleta a fost adaugata. \n";
		break;

	case Part::Mount::BIKE:
		toAdd = new Bike(make, model, year);
		std::cout << "Bicicleta a fost adaugata. \n";
		break;

	default:
		std::cout << "Ne pare rau. Nu putem repara acest tip de vehicul\n";
		WAIT(2)
			break;
	}

	fleet.add(toAdd);
}
*/

/*
void diagnoseFleet(RArray<Vehicle*> &fleet, wxStdOutputStream& out)
{
	if (fleet.isEmpty())
	{
		out << "Momentan nu sunt vehicule in atelier.\n";
		return;
	}

	for (unsigned i = 0; i<fleet.size(); i++)
	{
		fleet[i]->diagnose(out);
	}
}
*/

/*
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
		|| (defect > vehicle->getPart(part).getPossibleDefectsNum()))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Defectul nu este pe lista. Incercati din nou.\n";
	}
	defect--;
	vehicle->getPart(part).applyDamage(defect, true);
}
*/

static void populateFleet(RArray<Vehicle*> &fleet, const unsigned toAdd)
{
	auto elementsToAdd = toAdd;
	if (!elementsToAdd)
	{
		return;
	}

	srand((unsigned)time(0));

	//open vehicle type generators for make and model
	wxString GDIR = wxT(STR(ASSETS));
	GDIR = GDIR + "/generators/";

	//select apppropriate generator
		//optional step. using generics for now
	
	//file streams
	wxFFileInputStream fMake(GDIR + "genericMakes.in");
	wxFFileInputStream fModel(GDIR + "genericModels.in");

	//I/O streams for files
	wxStdInputStream make(fMake);
	wxStdInputStream model(fModel);

	//count lines 
	unsigned mLines = 0, modLines = 0, mi = 0, modi = 0;
	std::string m, mod;


	if (fMake.IsOk() && fModel.IsOk())
	{
		while (std::getline(make, m))
		{
			mLines++;
		}

		while (std::getline(model, m))
		{
			modLines++;
		}

		while (elementsToAdd)
		{
			//reset file pointers
			make.clear();
			make.seekg(0, std::ios::beg);

			model.clear();
			model.seekg(0, std::ios::beg);

			//clear strings
			m.clear();
			mod.clear();

			//random choose vehicle type
			Part::Mount vehType = (Part::Mount)(rand() % Part::getMountTypes() + 1);

			//random select lines for make and model
			mi = (rand() + elementsToAdd) % (mLines + (mLines==0));
			modi = (rand() + elementsToAdd) % (modLines + (modLines == 0));

			//extract data from files
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

	//TODO write error to dedicated stream
	/*
	else
	{
		std::cout << "Nu s-au putut incarca vehiculele.\n";
	}
	*/
}

static void displayFleet(RArray<Vehicle*> &fleet, wxStdOutputStream& out)
{
	for (unsigned i = 0; i < fleet.size(); i++)
	{
		if (fleet[i]) 
		{ 
			out << i + 1 << ". " << *fleet[i] << "\n"; 
		}
	}
}

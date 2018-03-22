#include "Vehicle.h"
#include <ctime>

Vehicle::Vehicle()
{
}

Vehicle::Vehicle(std::string make, std::string model, unsigned year, unsigned tParts) : make(make), model(model), totalParts(tParts)
{
	if (year >= 1950 && year < 2100) { this->year = year; }
	
	parts = new Part*[totalParts];
	for (unsigned i = 0; i < totalParts; i++) { parts[i] = nullptr; }

}

Vehicle::~Vehicle()
{
	for (unsigned i = 0; i < totalParts; i++) { delete parts[i]; }
	delete[] parts;
}

std::string Vehicle::getMake() const { return make; }

std::string Vehicle::getModel() const { return model; }

unsigned int Vehicle::getYear() const { return year; }

double Vehicle::getCondition() const { return condition;	}

void Vehicle::addPart(Part::Type t, Part::Position p)
{
	if (numParts < totalParts)
	{
		parts[numParts++] = new Part(Part::Mount::ANY, t, p);
	}
}

void Vehicle::applyRandomDamage(bool verbose)
{
	srand((int)time(0));
	
	for (unsigned i = 0; i < numParts; i++)
	{
		parts[i]->applyDamage( ((rand() + i + 5345) % parts[i]->getNumDefects()) , verbose);
	}
}

void Vehicle::showPartsList()
{
	//totalParts from derivate classes is used
	for (unsigned i = 0; i < numParts; i++)
	{
		std::cout <<i+1<<". "<<parts[i]->generateName() << "\n";
	}
	std::cout << "\n";
}

void Vehicle::applySpecificDamage(bool verbose)
{
	std::cout << make << " " << model << " " << year << "\n";
	showPartsList();

	unsigned part = 0;
	while ((std::cout << "Alegeti componenta: " && !(std::cin >> part))
		|| (part > numParts))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Componenta nu este pe lista. Incercati din nou.\n";
	}
	part--;

	if (!parts[part]) 
	{ 
		std::cout << "Nu se pot aplica defecte componentei selectate.\n"; 
		return;
	}

	parts[part]->showPossibleDefects();
	
	unsigned defect = 0;
	while ((std::cout << "Alegeti defectul: " && !(std::cin >> defect)) 
		|| (defect > parts[part]->getNumDefects()))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Defectul nu este pe lista. Incercati din nou.\n";
	}

	defect--;

	parts[part]->applyDamage(defect, verbose);

}

void Vehicle::DBG_showLoadedDefects()
{
	for (unsigned i = 0; i < numParts; i++)
	{
		std::cout << parts[i]->generateName() << ": \n";
		parts[i]->showPossibleDefects();
	}
}

//TODO ensure output is displayed correctly
void Vehicle::diagnose()
{
	//here, the vehicle "type" is given by its Parts
	//TODO consider adding vehicle type member and scrap inheritance 
	switch (parts[0]->getMount())
	{
	case Part::Mount::CAR:
		std::cout << "Automobil ";
		break;
	case Part::Mount::MOTO:
		std::cout << "Motocicleta ";
		break;
	case Part::Mount::BIKE:
		std::cout << "Bicicleta ";
		break;
	default:
		break;
	}

	std::cout << make + " " + model + " din " << year << " :\n\n";
	
	if(year<2000 && parts[0]->getMount()!= Part::Mount::BIKE) 
	{	std::cout<<"Vehiculul este anterior anului 2000\n"; }

	double newCondition = 0.;
	for (unsigned i = 0; i < numParts; i++)
	{
		parts[i]->diagnose();
		newCondition += parts[i]->getCondition();
	}

	if (numParts && newCondition >= 0){	condition = newCondition / numParts; }
	else if (newCondition / numParts < 0) { condition = 0.; }

}


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

Vehicle::Vehicle(const Vehicle & src)
{
	make = src.make;
	model = src.model;
	year = src.year;
	condition = src.condition;

	for (unsigned i = 0; i < numParts; i++)
	{
		delete parts[i];
	}
	delete[] parts;

	totalParts = src.totalParts;
	numParts = src.numParts;
	parts = new Part*[totalParts];

	for (unsigned i = 0; i < numParts; i++)
	{
		if (parts && src.parts[i] != nullptr)
		{
			parts[i] = new Part(*src.parts[i]);
		}
	}

	if (src.stats)
	{
		for (unsigned i = 0; i < (unsigned)Stats::NUM; i++)
		{
			stats[i] = src.stats[i];
		}
	}
}

Vehicle & Vehicle::operator=(const Vehicle & src)
{
	make = src.make;
	model = src.model;
	year = src.year;
	condition = src.condition;

	for (unsigned i = 0; i < numParts; i++)
	{
		delete parts[i];
	}
	delete[] parts;

	totalParts = src.totalParts;
	numParts = src.numParts;
	parts = new Part*[totalParts];

	for (unsigned i = 0; i < numParts; i++)
	{
		if (parts && src.parts[i] != nullptr)
		{
			parts[i] = new Part(*src.parts[i]);
		}
	}

	if (src.stats)
	{
		for (unsigned i = 0; i < (unsigned)Stats::NUM; i++)
		{
			stats[i] = src.stats[i];
		}
	}

	return *this;
}

Part& Vehicle::getPart(const unsigned part)
{
	if (!parts[part]) { throw"Out of bounds"; }
	return *parts[part];
}

Vehicle::~Vehicle()
{
	for (unsigned i = 0; i < totalParts; i++) { delete parts[i]; }
	delete[] parts;

	delete[] stats;
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

void Vehicle::applyRandomDamage(std::ostream& out)
{
	unsigned k = 0;
	for (unsigned i = 0; i < numParts; i++)
	{
		k = parts[i]->getPossibleDefectsNum();
		parts[i]->applyDamage( rand() % k);
	}
}

void Vehicle::showPartsList(std::ostream& out)
{
	out << *this << "\n";
	//totalParts from derivate classes is used
	for (unsigned i = 0; i < numParts; i++)
	{
		out <<i+1<<". "<<parts[i]->generateName() << "\n";
	}
	out << "\n";
}

void Vehicle::showLoadedDefects(std::ostream& out)
{
	for (unsigned i = 0; i < numParts; i++)
	{
		out << parts[i]->generateName() << ": \n";
		parts[i]->showPossibleDefects();
	}
}

//TODO ensure output is displayed correctly
void Vehicle::diagnose(std::ostream& out)
{
	//here, the vehicle "type" is given by its Parts
	//TODO consider adding vehicle type member and scrap inheritance 

	out << *this<<"\n";
	
	if(year<2000 && parts[0]->getMount()!= Part::Mount::BIKE) 
	{	
		out<<"Vehiculul este anterior anului 2000\n"; 
	}

	double newCondition = 0.;
	for (unsigned i = 0; i < numParts; i++)
	{
		parts[i]->diagnose(out);
		newCondition += parts[i]->getCondition();
	}

	if (numParts && newCondition >= 0){	condition = newCondition / numParts; }
	else if (newCondition / numParts < 0) { condition = 0.; }

}

unsigned Vehicle::getNumParts() const
{
	return numParts;
}

std::istream & operator>>(std::istream & in,  Vehicle & src)
{
	in >> src.make >> src.model >> src.year;
	
	//TODO validate input
	//in.setstate(std::ios::failbit);

	return in;
}

std::ostream & operator<<(std::ostream & out, const Vehicle & src)
{
	out << src.getNameType();
	out << src.make + " " + src.model + " din " << src.year << " ";
	return out;
}

const std::string Vehicle::getNameType() const
{
	std::string type("Vehicul necunoscut");
	
	if (!parts) { return type; }

	switch (parts[0]->getMount())
	{
	case Part::Mount::ANY:
		type = "Vehicul necunoscut";
	case Part::Mount::CAR:
		type = "Automobil ";
		break;
	case Part::Mount::MOTO:
		type = "Motocicleta ";
		break;
	case Part::Mount::BIKE:
		type = "Bicicleta ";
		break;
	}

	return type;
}

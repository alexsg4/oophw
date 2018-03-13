#include "stdafx.h"
#include "Vehicle.h"

//TODO modify if necessary
Vehicle::Vehicle()
{
	condition = 100.;
	totalParts = 10; // TODO change accordingly 
	parts = new Part*[totalParts];
	for (unsigned i = 0; i < totalParts; i++) { parts[i] = nullptr; }
}

Vehicle::Vehicle(std::string make, std::string model, unsigned year)
	: make(make), model(model) 
{
	if (year >= 1950 && year < 2100) { year = year; }
	
	condition = 100.;
	totalParts = 10; // TODO change accordingly 
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

void Vehicle::addPart(Part::Type t, Part::Vehicle v, Part::Position p)
{
	if (numParts < totalParts)
	{
		parts[numParts++] = new Part(t, v, p);
	}
}

#include "stdafx.h"
#include "Vehicle.h"

//TODO modify if necessary
Vehicle::Vehicle()
{

}

Vehicle::Vehicle(std::string make, std::string model, unsigned year = 1950)
	: make(make), model(model) {
	if (year > 1950 && year < 2100) { year = year; }
	
	condition = 100.;
	totalParts = 10; // TODO change accordingly 
	parts = new Part*[totalParts];
	for (int i = 0; i < totalParts; i++) { parts[i] = nullptr; }

}


Vehicle::~Vehicle()
{
	for (int i = 0; i < totalParts; i++) { delete parts[i]; }
	delete[] parts;
}

const std::string Vehicle::getMake() const
{
	return make;
}

const std::string Vehicle::getModel() const
{
	return model;
}

const unsigned int Vehicle::getYear() const
{
	return year;
}

const double Vehicle::getCondition() const
{
	return condition;
}

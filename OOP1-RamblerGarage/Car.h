#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
private:
	unsigned doors;
public:
	Car();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);
	Car(std::string m, std::string mod, unsigned year = 1950, unsigned doors = 2);
	~Car();

	//
};


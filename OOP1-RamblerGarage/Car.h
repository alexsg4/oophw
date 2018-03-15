#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{

public:
	Car();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);
	Car(std::string m, std::string mod, unsigned year = 1950);
	~Car();
};


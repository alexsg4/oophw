#pragma once
#include "Vehicle.h"
class Motorbike : public Vehicle
{
public:
	Motorbike();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);
	Motorbike(std::string m, std::string mod, unsigned year = 1950);
	~Motorbike();
};


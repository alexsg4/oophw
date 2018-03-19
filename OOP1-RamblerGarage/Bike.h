#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
private:
	static constexpr unsigned totalParts = 7;
public:
	Bike();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);
	Bike(std::string m, std::string mod, unsigned year = 1950);
	~Bike();
};


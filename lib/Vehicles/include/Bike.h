#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
private:
	static const unsigned totalParts = 7;
public:
	Bike();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY) override;
	Bike(std::string m, std::string mod, unsigned year = 1950);
	Bike(const Bike& src);
	Bike& operator=(const Bike& src);

	~Bike();
};


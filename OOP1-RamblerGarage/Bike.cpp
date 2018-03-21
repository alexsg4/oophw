#include "Bike.h"


Bike::Bike()
{
}

void Bike::addPart(Part::Type t, Part::Position p)
{
	if (numParts < totalParts)
	{
		parts[numParts++] = new Part(Part::Mount::BIKE, t, p);
	}
}

Bike::Bike(std::string m, std::string mod, unsigned year) : Vehicle(m, mod, year, totalParts)
{
	addPart(Part::Type::TRANSMISSION, Part::Position::ANY);
	addPart(Part::Type::SUSPENSION, Part::Position::ANY);
	addPart(Part::Type::BODY, Part::Position::ANY);

	addPart(Part::Type::WHEEL, Part::Position::FRONT);
	addPart(Part::Type::WHEEL, Part::Position::REAR);

	addPart(Part::Type::BRAKE, Part::Position::FRONT);
	addPart(Part::Type::BRAKE, Part::Position::REAR);
}


Bike::~Bike()
{
}

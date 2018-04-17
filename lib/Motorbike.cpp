#include "Motorbike.h"


Motorbike::Motorbike()
{
}

void Motorbike::addPart(Part::Type t, Part::Position p)
{
	if (numParts < totalParts)
	{
		parts[numParts++] = new Part(Part::Mount::MOTO, t, p);
	}
}

Motorbike::Motorbike(std::string m, std::string mod, unsigned year) : Vehicle(m,mod,year, totalParts)
{
	addPart(Part::Type::ENGINE, Part::Position::ANY);
	addPart(Part::Type::TRANSMISSION, Part::Position::ANY);
	addPart(Part::Type::ECU, Part::Position::ANY);
	addPart(Part::Type::SUSPENSION, Part::Position::ANY);
	addPart(Part::Type::BODY, Part::Position::ANY);

	addPart(Part::Type::WHEEL, Part::Position::FRONT);
	addPart(Part::Type::WHEEL, Part::Position::REAR);

	addPart(Part::Type::BRAKE, Part::Position::FRONT);
	addPart(Part::Type::BRAKE, Part::Position::REAR);
}

Motorbike::Motorbike(const Motorbike & src) : Vehicle(src)
{
}

Motorbike & Motorbike::operator=(const Motorbike & src)
{
	static_cast<Vehicle>(*this) = static_cast<Vehicle>(src);
	return *this;
}

Motorbike::~Motorbike()
{
}

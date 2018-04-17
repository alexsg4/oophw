#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
private:
	unsigned doors = 2;
	static const unsigned totalParts = 18;
public:
	Car();
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY) override;
	Car(std::string m, std::string mod, unsigned year = 1950, unsigned doors = 2);
	Car(const Car& src);
	Car& operator= (const Car& src);

	~Car();

};


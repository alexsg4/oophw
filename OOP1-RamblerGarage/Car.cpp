#include "stdafx.h"
#include "Car.h"


Car::Car()
{
}

void Car::addPart(Part::Type t, Part::Position p)
{
	if (numParts < totalParts)
	{
		parts[numParts++] = new Part(Part::Mount::CAR, t, p);
	}
}

Car::Car(std::string m, std::string mod, unsigned year, unsigned doors) : Vehicle (m, mod, year, 14) 
{

	addPart(Part::Type::ENGINE, Part::Position::ANY);
	addPart(Part::Type::TRANSMISSION, Part::Position::ANY);
	addPart(Part::Type::ECU, Part::Position::ANY);
	addPart(Part::Type::SUSPENSION, Part::Position::ANY);
	addPart(Part::Type::BODY, Part::Position::ANY);
	addPart(Part::Type::INTERIOR, Part::Position::ANY);

	addPart(Part::Type::DOOR, Part::Position::FRONTLT);
	addPart(Part::Type::DOOR, Part::Position::FRONTRT);
	
	//Only 2-4 door vehicles accepted for now
	//The trunk can be modeled as a REAR door for hatchbacks if necessary
	doors = doors;
	if(doors == 4)
	{
		addPart(Part::Type::DOOR, Part::Position::REARLT);
		addPart(Part::Type::DOOR, Part::Position::REARRT);
	}

	addPart(Part::Type::WHEEL, Part::Position::FRONTLT);
	addPart(Part::Type::WHEEL, Part::Position::FRONTRT);
	addPart(Part::Type::WHEEL, Part::Position::REARLT);
	addPart(Part::Type::WHEEL, Part::Position::REARRT);

	addPart(Part::Type::BRAKE, Part::Position::FRONTLT);
	addPart(Part::Type::BRAKE, Part::Position::FRONTRT);
	addPart(Part::Type::BRAKE, Part::Position::REARLT);
	addPart(Part::Type::BRAKE, Part::Position::REARRT); 
	
}


Car::~Car()
{
}

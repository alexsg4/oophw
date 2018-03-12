#include "stdafx.h"
#include "Part.h"
#include "Defect.h"


Part::Part()
{
	numDefects = 0;
	type = Type::ANY;
	vehicle = Vehicle::ANY;
	position = Position::ANY;

	defects = new Defect*[maxDefects];
	for (int i = 0; i < maxDefects; i++){ defects[i] = nullptr; }

}

Part::Part(Type t, Vehicle v, Position pos) : type(t), vehicle(v), position(pos)
{
	defects = new Defect*[maxDefects];
	for (int i = 0; i < maxDefects; i++) { defects[i] = nullptr; }
}

Part::~Part()
{
	for (int i = 0; i < maxDefects; i++)
	{
		delete defects[i];
	}
	delete[] defects;
}

Part::Type Part::getType() const
{
	return type;
}

Part::Vehicle Part::getVehicle() const
{
	return vehicle;
}

Part::Position Part::getMount() const
{
	return position;
}


double Part::getCondition() const
{
	return condition;
}

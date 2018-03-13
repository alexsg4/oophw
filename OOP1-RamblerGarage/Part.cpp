#include "stdafx.h"
#include "Part.h"

Part::Part()
{
	numDefects = 0;
	type = Type::ANY;
	vehicle = Vehicle::ANY;
	position = Position::ANY;

	defectMarker = new int[maxDefects];
	for (int i = 0; i < maxDefects; i++) { defectMarker[i] = 0; }
}

Part::Part(Type t, Vehicle v, Position pos) : type(t), vehicle(v), position(pos)
{
	defectMarker = new int[maxDefects];
	for (int i = 0; i < maxDefects; i++) { defectMarker[i] = 0; }
}

Part::~Part()
{
	delete[] defectMarker;
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

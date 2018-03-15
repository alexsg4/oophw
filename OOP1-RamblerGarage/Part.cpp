#include "stdafx.h"
#include "Part.h"
#include "Defect.h"

Part::Part()
{
	numDefects = 0;
	type = Type::ANY;
	mount = Mount::ANY;
	position = Position::ANY;

	defectMarker = new bool[maxDefects];
	for (int i = 0; i < maxDefects; i++) { defectMarker[i] = 0; }
}

Part::Part(Mount v, Type t, Position pos) : mount(v), type(t), position(pos)
{
	defectMarker = new bool[maxDefects];
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

Part::Mount Part::getMount() const
{
	return mount;
}

Part::Position Part::getPosition() const
{
	return position;
}


double Part::getCondition() const
{
	return condition;
}

unsigned Part::getMaxDefects() const
{
	return maxDefects;
}

void Part::loadDefects(int mount, int type)
{
	if (numDefects >= maxDefects)
	{
		std::cout << "lista defecte plina\n";
		return;
	}

	//test
	int k[3] = { 1,2,3 };
	defects[(unsigned)mount][(unsigned)type][numDefects++] = new Defect("asd", 2, 3, k);

}


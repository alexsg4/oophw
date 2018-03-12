#include "stdafx.h"
#include "Part.h"
#include "Defect.h"


Part::Part()
{
	maxDefects = 20; //TODO change accordingly 
	numDefects = 0;
	condition = 100;

	defects = new Defect*[maxDefects];
	for (int i = 0; i < maxDefects; i++){ defects[i] = nullptr; }
}


Part::~Part()
{
	for (int i = 0; i < maxDefects; i++)
	{
		delete defects[i];
	}
	delete[] defects;
}

const std::string Part::getType() const
{
	return type;
}

const std::string Part::getVehicle() const
{
	return type;
}

const std::string Part::getMount() const
{
	return mount;
}

const double Part::getCondition() const
{
	return condition;
}

#include "stdafx.h"
#include "Part.h"
#include "Defect.h"
#include <fstream>

Part::Part()
{
	type = Type::ANY;
	mount = Mount::ANY;
	position = Position::ANY;

	defectMarker = new bool[maxDefects];
	for (unsigned i = 0; i < maxDefects; i++) { defectMarker[i] = false; }

	dTable = new Defect*[maxDefects];
	for (unsigned i = 0; i < maxDefects; i++) { dTable[i] = nullptr; }

}

Part::Part(Mount v, Type t, Position pos) : mount(v), type(t), position(pos)
{
	defectMarker = new bool[maxDefects];
	for (unsigned i = 0; i < maxDefects; i++) 
	{ 
		defectMarker[i] = false; 
	}

	dTable = new Defect*[maxDefects];
	for (unsigned i = 0; i < maxDefects; i++) { dTable[i] = nullptr; }

	loadDefects(getDefectsFile());
}

Part::~Part()
{
	delete[] defectMarker;
}

Part::Type Part::getType() const{	return type;	}

Part::Mount Part::getMount() const{	return mount;	}

Part::Position Part::getPosition() const{	return position;	}

double Part::getCondition() const{	return condition;	}

unsigned Part::getMaxDefects() const{	return maxDefects;	}

std::string& Part::getDefectsFile()
{
	std::string file;
	switch (mount)
	{
	case Part::Mount::ANY:
		break;
	case Part::Mount::CAR:
		file = file + "car";
		break;
	case Part::Mount::MOTO:
		file = file + "moto";
		break;
	case Part::Mount::BIKE:
		file = file + "bike";
		break;
	default:
		break;
	}

	switch (type)
	{
	case Part::Type::ANY:
		break;
	case Part::Type::WHEEL:
		file = file + "Wheel";
		break;
	case Part::Type::ENGINE:
		file = file + "Engine";
		break;
	case Part::Type::BRAKE:
		file = file + "Brake";
		break;
	case Part::Type::SUSPENSION:
		file = file + "Suspension";
		break;
	case Part::Type::TRANSMISSION:
		file = file + "Transmission";
		break;
	case Part::Type::INTERIOR:
		file = file + "Interior";
		break;
	case Part::Type::ECU:
		file = file + "ECU";
		break;
	case Part::Type::BODY:
		file = file + "Body";
		break;
	case Part::Type::DOOR:
		file = file + "Door";
		break;
	default:
		break;
	}

	file = file + "in";
}

void Part::loadDefects(std::string s)
{
	std::ifstream fin(s);
	if (fin.is_open())
	{
		//create temporary variables for a defect
		std::string name;
		double hours = 0.;
		double damage = 0.;
		unsigned cost[100];
		do
		{
			unsigned i = 0;
			std::getline(fin, name, '/');
			fin >> damage >> hours;
			while (fin >> cost[i++]);

			dTable[numDefects++] = new Defect(name, damage, hours);
			dTable[numDefects - 1]->loadCost(cost);

		} while (!fin.eof() && numDefects < maxDefects);
	}
	else
	{
		std::cout << "Eroare: nu s-au putut incarca defectele \n";
	}

	fin.close();
}


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

	loadDefects(DDIR+getDefectsFile());
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

std::string Part::getDefectsFile()
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

	file = file + ".in";
	
	return file;
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
		unsigned* cost = new unsigned[Defect::getSpareTypes()]();
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

const std::string Part::generateName()
{
	std::string name;

	switch (type)
	{
	case Part::Type::ANY:
		break;
	case Part::Type::WHEEL:
		name = "Roata";
		break;
	case Part::Type::ENGINE:
		name = "Motor";
		break;
	case Part::Type::BRAKE:
		name = "Frana";
		break;
	case Part::Type::SUSPENSION:
		name = "Suspensie";
		break;
	case Part::Type::TRANSMISSION:
		if(mount == Mount::BIKE) { name = "Ansamblu lant-pedale-directie"; }
		else { name = "Transmisie"; }
		break;
	case Part::Type::INTERIOR:
		if(mount == Mount::CAR){ name = "Habitaclu"; }
		break;
	case Part::Type::ECU:
		name = "Unitate control motor";
		break;
	case Part::Type::BODY:
		if (mount == Mount::CAR) { name = "Caroserie"; }
		else { name = "Cadru"; }
		break;
	case Part::Type::DOOR:
		name = "Usa";
		break;
	default:
		break;
	}

	name += " ";

	switch (position)
	{
	case Part::Position::ANY:
		break;
	case Part::Position::LEFT:
		name += "stanga";
		break;
	case Part::Position::RIGHT:
		name += "dreapta";
		break;
	case Part::Position::FRONT:
		name += "fata";
		break;
	case Part::Position::REAR:
		name += "spate";
		break;
	case Part::Position::FRONTLT:
		name += "fata-stanga";
		break;
	case Part::Position::FRONTRT:
		name += "fata-dreapta";
		break;
	case Part::Position::REARLT:
		name += "spate-stanga";
		break;
	case Part::Position::REARRT:
		name += "spate-dreapta";
		break;
	default:
		break;
	}

	return name;
}

void Part::diagnose()
{
	for (unsigned i = 0; i < numDefects; i++)
	{
		if (defectMarker[i])
		{
			dTable[i]->displayName();
			std::cout << "\n";
			dTable[i]->displaySpareCost();
		}
	}

}

void Part::applyDamage(unsigned marker)
{
	if (defectMarker[marker]) { return; }
	else 
	{
		//TODO adjust formatting
		defectMarker[marker] = true;
		condition -= dTable[marker]->getDamage();
		std::cout << "Componentei " << generateName() << " i-a fost aplicata defectiunea: "; 
		dTable[marker]->displayName();
		std::cout << "\n";
	}
}


#include "Part.h"
#include "Defect.h"
#include <fstream>

RArray<Defect> Part::_dTable[partTypes*mountTypes];
unsigned Part::dSection[mountTypes];
bool Part::_dLoaded[partTypes * mountTypes];


Part::Part()
{
	tMount = static_cast<unsigned>(mount);
	tType = static_cast<unsigned>(type);
	tIndex = _index();
}

Part::Part(Mount v, Type t, Position p) : mount(v), type(t), position(p)
{

	tMount = static_cast<unsigned>(mount);
	tType = static_cast<unsigned>(type);
	tIndex = _index();

	//prevent repeated initialisation
	if(dSection[1]==0)
	{ 
		for (unsigned i = 0; i < mountTypes; i++)
		{
			dSection[i] = i * partTypes;
		}
	}

	//prevent repeated initialisation
	if (!_dLoaded[tIndex])
	{
		std::string DDIR = STR(ASSETS);
		_dLoaded[tIndex] = loadDefectsFromFile(DDIR + "/defects/" + getDefectsFile());
	}
	
	if(dMarker.isEmpty())
	{
		for (unsigned i = 0; i < getPossibleDefectsNum(); i++)
		{
			dMarker.add();
		}
	}
}

Part::Part(const Part & src)
{
	mount = src.mount;
	type = src.type;
	position = src.position;

	numDefects = src.numDefects;
	dMarker = src.dMarker;
	condition = src.condition;
	
	tIndex = _index();
}

Part & Part::operator=(const Part & src)
{
	mount = src.mount;
	type = src.type;
	position = src.position;

	numDefects = src.numDefects;
	dMarker = src.dMarker;
	condition = src.condition;
	tIndex = _index();
	
	return *this;
}

Part::~Part()
{
	delete dTable;
}

Part::Type Part::getType() const{	return type;	}

Part::Mount Part::getMount() const{	return mount;	}

Part::Position Part::getPosition() const{	return position;	}

double Part::getCondition() const{	return condition;	}

unsigned Part::getNumDefects() const {	return numDefects;	}

unsigned Part::getPosTypes()
{
	return posTypes;
}

unsigned Part::getMountTypes()
{
	return mountTypes;
}

std::string Part::getDefectsFile() const
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

bool Part::loadDefectsFromFile(std::string s, std::ostream& out)
{
	std::ifstream fin(s);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			Defect temp;
			fin >> temp;
			fin.ignore(); //ignore rest of the line (usually just '\n'

			dTable[tIndex]+=temp;
		} 
	}
	else
	{
		out << "Eroare: nu s-au putut incarca defectele \n";
		return false;
	}

	fin.close();
	return true;
}

std::string Part::generateName() const
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
	}

	name += " ";

	switch (position)
	{
	case Part::Position::ANY:
		name.pop_back();
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

void Part::diagnose(std::ostream& out)
{
	//check if there are defects
	bool hasDefects = false;
	
	for(unsigned i=0; i<dMarker.size(); i++)
	{
		if(dMarker[i]) 
		{
			hasDefects = true;
			break;
		}
	}

	out << generateName() << ": ";
	if (hasDefects)
	{
		out << "\n";
		auto k = dTable[dSection[tMount] + tType].size();
		for (unsigned i = 0; i <k; i++)
		{
			if (dMarker[i])
			{
				out << dTable[dSection[tMount] + tType][i];
			}
		}
	}
	else { out << "/t/t/t componenta nu are defecte"; }
	out << "\n";
}

void Part::applyDamage(unsigned marker, bool verbose, std::ostream& out)
{
	//part already has this defect or defect is not on the list
	if (dMarker[marker] || marker >= getPossibleDefectsNum()) { return; }
	else
	{
		Defect* toAdd = &_dTable[tIndex][marker];
		
		if(!toAdd) 
		{ 
			//TODO show message
			return; 
		}	
		
		dMarker[marker] = true;
		condition -= toAdd->getDamage();
		
		if (verbose)
		{
			out << "Componentei " << generateName() << " i-a fost aplicata defectiunea: " << toAdd->getName() << ". \n";
		}
	}
	numDefects++;
}

void Part::showPossibleDefects(std::ostream& out)
{
	auto k = getPossibleDefectsNum();
	
	for (unsigned i = 0; i < k; i++)
	{
		Defect* toShow = &_dTable[tIndex][i];
		out << i + 1 << ". " << toShow->getName() << "\n"; 
	}
}

unsigned Part::getPossibleDefectsNum()
{
	return _dTable[tIndex].size();
}


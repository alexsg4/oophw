#include "stdafx.h"
#include "Defect.h"


Defect::Defect()
{
	cost = new unsigned[spares];
	for (int i = 0; i < spares; i++) { cost[i] = 0; }
}

Defect::Defect(std::string n, double d, double h, int *def)
{
	name = n;

	if (d > 0)
	{
		if (d > 100.){	d = 100.; }
		damage = d;
	}

	if (h > 0){	manHours = h; }

	cost = new unsigned[spares];
	
	//TODO test
	//TODO display spares amount when adding defects 
	if (def)
	{
		for (int i = 0; i < spares; i++)
		{
			if (def[i]) { cost[i] = def[i]; }
			else { cost[i] = 0; }
		}
	}
}

Defect::~Defect()
{
	delete[] cost;
}

unsigned Defect::getSpares() const {	return spares;	}

std::string Defect::getName() const {	return name;	}

double Defect::getDamage() const {	return damage;	}

unsigned Defect::getManHours() const {	return manHours; }

//TODO possible need to overload [] for simpler syntax
void Defect::displaySpareCost()
{
	if (cost[(unsigned)Spare::SCREW])
	{
		std::cout << cost[(unsigned)Spare::SCREW] << " suruburi\n";
	}

	if (cost[(unsigned)Spare::OIL])
	{
		std::cout << cost[(unsigned)Spare::OIL] << " ml ulei\n";
	}

	if (cost[(unsigned)Spare::WIRE])
	{
		std::cout << cost[(unsigned)Spare::WIRE] << " cm fire\n";
	}
}

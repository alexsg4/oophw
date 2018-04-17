#include "Defect.h"


Defect::Defect()
{
	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	cost = new unsigned[spares];
	for (unsigned i = 0; i < spares; i++) { cost[i] = 0; }
}

Defect::Defect(std::string n, double d, double h, const int *def)
{
	name = n;

	if (d > 0)
	{
		if (d > 100.){	d = 100.; }
		damage = d;
	}

	if (h > 0){	manHours = h; }

	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	cost = new unsigned[spares];
	
	if (def)
	{
		for (unsigned i = 0; i < spares; i++)
		{
			if (def[i]>0) { cost[i] = def[i]; }
			else { cost[i] = 0; }
		}
	}
}

Defect::Defect(std::string n, double d, double h)
{
	name = n;

	if (d > 0)
	{
		if (d > 100.) { d = 100.; }
		damage = d;
	}

	if (h > 0) { manHours = h; }
	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	cost = new unsigned[spares]();
}

Defect::Defect(const Defect & src)
{
	name = src.name;
	damage = src.damage;
	manHours = src.manHours;
	unsigned spares = static_cast<unsigned>(Spare::TYPES);

	if (!cost) { cost = new unsigned[spares](); }

	if (src.cost)
	{
		for (unsigned i = 0; i < spares; i++){	cost[i] = src.cost[i];	}
	}
}

Defect & Defect::operator=(const Defect & src)
{
	name = src.name;
	damage = src.damage;
	manHours = src.manHours;

	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	if (!cost) { cost = new unsigned[spares](); }

	if (src.cost)
	{
		for (unsigned i = 0; i < spares; i++){ cost[i] = src.cost[i]; }
	}

	return *this;
}

Defect::~Defect()
{
	delete[] cost;
}

unsigned Defect::getSpareTypes() 
{
	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	return spares;	
}

std::string Defect::getName() const {	return name;	}

double Defect::getDamage() const {	return damage;	}

unsigned Defect::getManHours() const {	return static_cast<unsigned>(manHours); }

//TODO possible need to overload [] for simpler syntax
void Defect::showSpareCost(std::ostream& out)
{
	if (!cost) { throw"NO COST ARRAY"; }
	if (cost[(unsigned)Spare::REPLACE])
	{
		out << "Componenta trebuie inlocuita. \n";
	}

	if (cost[(unsigned)Spare::SCREW])
	{
		out << cost[(unsigned)Spare::SCREW] << " suruburi\n";
	}

	if (cost[(unsigned)Spare::OIL])
	{
		out << cost[(unsigned)Spare::OIL] << " l ulei\n";
	}

	if (cost[(unsigned)Spare::WIRE])
	{
		out << cost[(unsigned)Spare::WIRE] << " cm fire\n";
	}

	if (cost[(unsigned)Spare::PAINT])
	{
		out << cost[(unsigned)Spare::PAINT] << " l vopsea\n";
	}
}

void Defect::loadCost(const unsigned* dCost)
{
	unsigned spares = static_cast<unsigned>(Spare::TYPES);
	for (unsigned i = 0; i < spares; i++)
	{
		if (dCost[i] > 0)
		{
			cost[i] = dCost[i];
		}
	}

}

std::ostream& operator<<(std::ostream& out, Defect& src)
{
	out << src.name << " " << src.manHours << "Ore necesare reparatie\n";
	src.showSpareCost(out);

	return out;
}

std::istream& operator>>(std::istream& in, Defect& src)
{
	std::getline(in, src.name, '/');
	in >> src.damage >> src.manHours;
	for (unsigned i = 0; i < src.getSpareTypes(); i++)
	{
		if (!src.cost)
		{
			throw"NO COST ARRAY";
		}
			in >> src.cost[i];
	}

	return in;
}
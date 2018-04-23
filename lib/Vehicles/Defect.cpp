#include "Defect.h"

Defect::Defect()
{
	for (unsigned i = 0; i < spares; i++){	cost[i] = 0;	}
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

	for (unsigned i = 0; i < spares; i++) { cost[i] = 0; }
	
	if (def)
	{
		for (unsigned i = 0; i < spares; i++)
		{
			cost[i] = def[i]; 
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
	for (unsigned i = 0; i < spares; i++) { cost[i] = 0; }
}

Defect::Defect(const Defect & src)
{
	name = src.name;
	damage = src.damage;
	manHours = src.manHours;
	
	for (unsigned i = 0; i < spares; i++){	cost[i] = src.cost[i];	}
}

Defect & Defect::operator=(const Defect & src)
{
	//prevent self assignment
	if(src!=*this)
	{ 
		name = src.name;
		damage = src.damage;
		manHours = src.manHours;

		for (unsigned i = 0; i < spares; i++)
		{ 
			cost[i] = src.cost[i]; 
		}
	}
	return *this;
}

bool Defect::operator==(const Defect & src) const
{
	if (name != src.name || damage != src.damage || src.manHours != src.manHours)
	{
		return false;
	}

	for (unsigned i = 0; i<spares; i++)
	{
		if (cost[i] != src.cost[i])
		{
			return false;
		}
	}

	return true;
}

bool Defect::operator!=(const Defect & src) const
{
	return !(*this == src);
}

Defect::~Defect()
{
}

unsigned Defect::getSpareTypes() {	return spares;	}

std::string Defect::getName() const {	return name;	}

double Defect::getDamage() const {	return damage;	}

unsigned Defect::getManHours() const {	return static_cast<unsigned>(manHours); }

void Defect::showSpareCost(std::ostream& out)
{
	//TODO use a switch
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
	out << src.name << " \n";

	auto h = src.manHours;
	if (h == 1)
	{
		out << "Reparatia necesita o ora de munca\n";
	}
	else if (h > 1)
	{
		out << "Reparatia necesita " << src.manHours << " ore de munca\n";
	}

	src.showSpareCost(out);

	return out;
}

std::istream& operator>>(std::istream& in, Defect& src)
{
	std::getline(in, src.name, '/');
	in >> src.damage >> src.manHours;
	
	for (unsigned i = 0; i < src.spares; i++)
	{
		in >> src.cost[i];
	}

	return in;
}
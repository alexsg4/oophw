#include "Ingredient.h"

Ingredient::Ingredient() {}

Ingredient::Ingredient(const std::string& nm, const double pr, const int id)
{
	name = nm;
	if (ID >= 0)
	{
		ID=id;
	}

	if (pr > 0.) { price = pr; }
}

Ingredient::Ingredient(const Ingredient & other)
{
	name = other.name;
	ID = other.ID;
	price = other.price;
}

Ingredient & Ingredient::operator=(const Ingredient & other)
{
	if (*this != other)
	{
		name = other.name;
		ID = other.ID;
		price = other.price;
	}
	return *this;
}

Ingredient::~Ingredient() {}

bool operator==(const Ingredient & src, const Ingredient & other)
{
	return (src.price == other.price  && src.ID == other.ID && src.name == other.name);
}

bool operator!=(const Ingredient & src, const Ingredient & other)
{
	return !(src==other);
}

std::istream & operator>>(std::istream & in, Ingredient & other)
{
	//delimiter character when reading ingredients from stream
	const char c_delim = '|';

	std::string buf;
	getline(in, buf, c_delim);
	other.name = buf;
	
	double pr = 0.;
	in >> pr;
	other.setPrice(pr);

	return in;
}

std::ostream & operator<<(std::ostream & out, const Ingredient & other)
{
	out << other.name;
	return out;
}

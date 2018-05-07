#include "Ingredient.h"

Ingredient::Ingredient() {}

Ingredient::Ingredient(const int tp, const double pr)
{
	if (tp >= 0 && tp < static_cast<int>(Types::NUM))
	{
		type = static_cast<Ingredient::Types>(tp);
	}

	if (pr > 0.) { price = pr; }
}

Ingredient::Ingredient(const Types tp, const double pr)
{
	type = tp;
	if (pr > 0.) { price = pr; }
}

Ingredient::Ingredient(const Ingredient & other)
{
	type = other.type;
	price = other.price;
}

Ingredient & Ingredient::operator=(const Ingredient & other)
{
	if (*this != other)
	{
		type = other.type;
		price = other.price;
	}
	return *this;
}

Ingredient::~Ingredient() {}

double Ingredient::getPrice() const
{
	if (price > 0.)
	{
		return price;
	}
	return 0.;
}

int Ingredient::getTypesNum() 
{
	return static_cast<int>(Types::NUM);
}

int Ingredient::getType() const
{
	return static_cast<int>(type);
}

const std::string Ingredient::getNameType() const
{
	std::string name;

	//TODO fill in ingredient types
	switch (type)
	{

	case Types::ANY:
		name = "Generic Ingredient";
		break;

	case Types::MARINARA:
		name = "Generic Ingredient";
		break;

	case Types::MOZZA:
		name = "Generic Ingredient";
		break;

	case Types::HAN:
		name = "Generic Ingredient";
		break;

	case Types::BEEFC:
		name = "Generic Ingredient";
		break;

	case Types::CHICKC:
		name = "Generic Ingredient";
		break;

	case Types::BACON:
		name = "Generic Ingredient";
		break;

	case Types::PEPPE:
		name = "Generic Ingredient";
		break;

	case Types::PEPPER:
		name = "Generic Ingredient";
		break;

	case Types::SHROOM:
		name = "Generic Ingredient";
		break;

	case Types::TOMATO:
		name = "Generic Ingredient";
		break;

	case Types::ONION:
		name = "Generic Ingredient";
		break;

	case Types::CORN:
		name = "Generic Ingredient";
		break;

	case Types::CHIL:
		name = "Generic Ingredient";
		break;

		//Add new entries here
	case Types::NUM:
		name = "THIS SHOULD NOT OCCUR";
		break;
	}

	return name;
}

void Ingredient::setPrice(const double pr)
{
	if (pr > 0.)
	{
		price = pr;
		return;
	}
	price = 0.;
}


bool operator==(const Ingredient & src, const Ingredient & other)
{
	return (src.price == other.price  && src.type == other.type);
}

bool operator!=(const Ingredient & src, const Ingredient & other)
{
	return !(src==other);
}

std::istream & operator>>(std::istream & in, Ingredient & other)
{
	double pr = 0.;
	int tp = 0;

	in >> tp >> pr;

	if (tp >= 0 && tp < static_cast<int>(Ingredient::Types::NUM))
	{
		other.type = static_cast<Ingredient::Types>(tp);
	}

	if (pr > 0.)
	{
		other.price = pr;
	}

	return in;
}

std::ostream & operator<<(std::ostream & out, const Ingredient & other)
{
	out << other.getNameType() << ": " << other.price << " $";
	return out;
}

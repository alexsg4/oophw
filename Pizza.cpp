#include "Pizza.h"
#include "Ingredient.h"


Pizza::Pizza() {}

Pizza::Pizza(const std::string& name, const std::vector<Product::Point>& recipeToSet, const std::vector<Ingredient> & refToSet, const std::string & flagToSet)
	: Product(name, recipeToSet, refToSet), flagStr(flagToSet){}

Pizza::Pizza(const Pizza & other) : Product(other)
{
	if (other.ref)
	{
		ref = other.ref;
	}

	flagStr = other.flagStr;
}

Pizza & Pizza::operator=(const Pizza & other)
{
	if (*this != other)
	{
		name = other.name;

		recipe = other.recipe;

		if (other.ref)
		{
			ref = other.ref;
		}

		flagStr = other.flagStr;
	}
	return *this;
}

Pizza::~Pizza()
{
	ref = nullptr;
}

const std::string Pizza::getName() const
{
	return Product::getName();
}

double Pizza::getPrice() const
{
	double price = 0.;

	if (ref && recipe.size())
	{
		for (size_t i = 0; i < recipe.size(); i++)
		{
			if (recipe[i].id > -1)
			{
				price += (*ref)[recipe[i].id].getPrice()*recipe[i].qty;
			}
		}
	}
	return price;
	
}

const std::vector<Product::Point> & Pizza::getRecipe() const
{
	return Product::recipe;
}

void Pizza::setRef(const std::vector<Ingredient> & refToSet)
{
	ref = &refToSet;
}

bool operator==(const Pizza & src, const Pizza & other)
{
	return (static_cast<Product>(src) == static_cast<Product>(other) && src.flagStr == other.flagStr);
}

bool operator!=(const Pizza & src, const Pizza & other)
{
	return !(src == other);
}

//TODO validate
std::istream & operator>>(std::istream & in, Pizza & other)
{
	//delimiter character when reading ingredients from stream
	const char c_delim = '|';

	std::string buf;

	getline(in, buf, c_delim);
	other.name = buf;
	buf.clear();

	/*
	getline(in, buf, c_delim);
	for (size_t i = 0; i<buf.size(); i++)
	{
		if (buf[i] > '0' && buf[i] <= '9')
		{
			other.recipe.push_back(std::stoi(buf, (size_t*)i));
		}
		else
		{
			other.recipe.push_back(0);
		}
	}
	*/

	return in;
}

std::ostream & operator<<(std::ostream & out, const Pizza & other)
{
	out << other.name << " : $" << other.getPrice();
	return out;
}
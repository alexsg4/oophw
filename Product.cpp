#include "Product.h"

const std::vector<Ingredient> * Product::ref = nullptr;

Product::Product(){}

Product::Product(const std::string& name, const std::vector<int>& recipeToSet, const std::vector<Ingredient> & refToSet) 
{
	this->name = name;
	recipe = recipeToSet;

	ref = &refToSet;
}

Product::Product(const Product & other)
{
	name = other.name;

	recipe = other.recipe;

	if (other.ref)
	{
		ref = other.ref;
	}
}

Product & Product::operator=(const Product & other)
{
	if (*this != other)
	{
		name = other.name;

		recipe = other.recipe;

		if (other.ref)
		{
			ref = other.ref;
		}
	}
	return *this;
}

Product::~Product()
{
	ref = nullptr;
}

const std::string Product::getName() const
{
	return name;
}

double Product::getPrice() const
{
	double price = 0.;

	if (ref && recipe.size())
	{
		for (size_t i = 0; i < recipe.size(); i++)
		{
			price += (*ref)[i].getPrice()*recipe[i];
		}
	}
	return price;
}

const std::vector<int> & Product::getRecipe() const
{
	return recipe;
}

void Product::setRef(const std::vector<Ingredient> & refToSet)
{
	if (ref && ref != &refToSet)
	{
		ref = &refToSet;
	}
}

bool operator==(const Product & src, const Product & other)
{
	if (src.name != other.name) { return false; }

	if (!src.ref || !other.ref) { return false; }

	if (src.recipe != other.recipe) { return false; }

	return true;
}

bool operator!=(const Product & src, const Product & other)
{
	return !(src==other);
}

//TODO validate
std::istream & operator>>(std::istream & in, Product & other)
{
	//delimiter character when reading ingredients from stream
	const char c_delim = '|';

	std::string buf;

	getline(in, buf, c_delim);
	other.name = buf;
	buf.clear();

	getline(in, buf, c_delim);
	for (size_t i=0; i<buf.size(); i++)
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

	return in;
}

std::ostream & operator<<(std::ostream & out, const Product & other)
{
	out << other.name << ": $" << other.getPrice();
	return out;
}

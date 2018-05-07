#include "Product.h"


Product::Product(){}

Product::Product(const std::string& name, const std::vector<int>& comp, Ingredient** reff)
{
	this->name = name;
	ingSize = Ingredient::getTypesNum();
	recipe = comp;

	if (reff)
	{
		ref = &reff[0];
	}
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
	delete ref;
}

const std::string Product::getName() const
{
	return name;
}

double Product::getPrice() const
{
	size_t size = Ingredient::getTypesNum();
	double price = 0.;

	if (ref && recipe.size() == size)
	{
		for (size_t i = 0; i < size; i++)
		{
			price += ref[i]->getPrice()*recipe[i];
		}
	}
	return price;
}

const std::vector<int> & Product::getRecipe()
{
	return recipe;
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
	in >> other.name;
	//TODO implement

	return in;
}

std::ostream & operator<<(std::ostream & out, const Product & other)
{
	out << other.name << ": $" << other.getPrice();
	return out;
}

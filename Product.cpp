#include "Product.h"


Product::Product(){}

Product::Product(const std::string& name, const double pr, const int* comp, Ingredient** reff)
{
	this->name = name;
	this->price = pr;

	recipe = new int[Ingredient::getTypesNum()]();

	if (comp)
	{
		for (size_t i = 0; i < sizeof(comp) / sizeof(int); i++)
		{
			if (comp[i])
			{
				recipe[i] = comp[i];
			}
		}
	}

	if (reff)
	{
		ref = &reff[0];
	}
}

Product::Product(const Product & other)
{
	name = other.name;
	price = other.price;

	size_t size = Ingredient::getTypesNum();
	
	if (!recipe)
	{
		recipe = new int[size]();
	}

	if (other.recipe)
	{
		for (size_t i = 0; i < size ; i++)
		{
			recipe[i] = other.recipe[i];
		}
	}

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
		price = other.price;

		size_t size = Ingredient::getTypesNum();

		if (!recipe)
		{
			recipe = new int[size]();
		}

		if (other.recipe)
		{
			for (size_t i = 0; i < size; i++)
			{
				recipe[i] = other.recipe[i];
			}
		}

		if (other.ref)
		{
			ref = other.ref;
		}
	}
	return *this;
}

Product::~Product()
{
	delete[] recipe;
	delete ref;
}

const std::string Product::getName() const
{
	return name;
}

double Product::getPrice() const
{
	return price;
}

void Product::setPrice(const double pr)
{
	if (pr>0.) { price = pr; }
}

int ** Product::getRecipe()
{
	if (recipe)
	{
		return &recipe;
	}
	return nullptr;
}

bool operator==(const Product & src, const Product & other)
{
	if (src.name != other.name && src.price != other.price) { return false; }
	
	if (!src.ref || !src.recipe || !other.recipe || !other.ref) { return false; }
	else
	{
		if (*src.ref != *other.ref) { return false; }
		size_t size = Ingredient::getTypesNum();

		if ( (sizeof(other.recipe) / sizeof(int)) != (sizeof(src.recipe) / sizeof(int)) ) { return false; }

		if ( (sizeof(other.recipe) / sizeof(int)) != size) { return false; }

		for (size_t i = 0; i < size; i++)
		{
			if (src.recipe[i] != other.recipe[i]) { return false; }
		}
	}
	
	return true;
}

bool operator!=(const Product & src, const Product & other)
{
	return !(src==other);
}

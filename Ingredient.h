#pragma once
#include "Item.h"

#include <string>
#include <iostream>

class Ingredient :
	public Item
{

private:
	std::string name = "Generic Ingredient";
	double price = 0;
	int ID = -1;

public:
	Ingredient();
	Ingredient(const std::string& nm, const double pr, const int id = -1);
	Ingredient(const double pr, const int id = -1);
	Ingredient(const Ingredient & other);
	Ingredient& operator = (const Ingredient & other);
	virtual ~Ingredient();

	inline virtual double getPrice() const override
	{
		return price;
	}
	
	inline int getID() const
	{
		return ID;
	}

	inline void setID(const int id)
	{
		if (id >= 0) { ID = id; }
	}
	
	inline std::string getName() const
	{
		return name;
	}
	
	inline void setPrice(const double pr)
	{
		if (pr > 0.)
		{
			price = pr;
			return;
		}
		price = 0.;
	}

	friend bool operator == (const Ingredient & src, const Ingredient & other);
	friend bool operator != (const Ingredient & src, const Ingredient & other);
	friend std::istream& operator >>(std::istream& in, Ingredient & other);
	friend std::ostream& operator <<(std::ostream& out, const Ingredient & other);

};

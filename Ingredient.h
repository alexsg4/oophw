#pragma once
#include "Item.h"

#include <string>
#include <iostream>

class Ingredient :
	public Item
{

public:
	enum class Types
	{
		ANY = -1,
		MARINARA,		//That magic sauce
		MOZZA,			//Mozzarella Cheese
		HAN,
		BEEFC,			//Fried beef cubes
		CHICKC,			//Fried chicken cubes
		BACON,
		PEPPE,			//Pepperoni
		PEPPER,			//Bell peppers
		SHROOM,
		TOMATO,
		ONION,
		CORN,
		CHIL,			//Chilli
		//Add new entries here
		NUM
	};

private:
	
	Types type = Types::ANY;
	double price = 0;


public:
	Ingredient();
	Ingredient(const int tp, const double pr);
	Ingredient(const Types tp, const double pr);
	Ingredient(const Ingredient & other);
	Ingredient& operator = (const Ingredient & other);
	virtual ~Ingredient();

	virtual double getPrice() const override;
	
	static int getTypesNum();
	
	int getType() const;
	const std::string getNameType() const;
	void setPrice(const double pr);


	friend bool operator == (const Ingredient & src, const Ingredient & other);
	friend bool operator != (const Ingredient & src, const Ingredient & other);
	friend std::istream& operator >>(std::istream& in, Ingredient & other);
	friend std::ostream& operator <<(std::ostream& out, const Ingredient & other);



};

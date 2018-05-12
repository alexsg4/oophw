#pragma once
#include "Item.h"

#include <string>
#include <vector>

class Ingredient;

class Product :
	public Item
{
public:
	//Recipe entry consiting of ingredient id and quantity
	struct Ing
	{
		int id = -1;
		int qty = 1;

		Ing(const int id, const int qty) : id(id), qty(qty) {}
		friend bool operator == (const Ing & i1, const Ing & i2)
		{
			return (i1.id == i2.id && i1.qty == i2.qty);
		}

		friend bool operator != (const Ing & i1, const Ing & i2)
		{
			return !(i1==i2);
		}

		Ing& operator = (const Ing& other)
		{
			if (*this != other)
			{
				id = other.id;
				qty = other.qty;
			}
			return *this;
		}
	};

protected:
	std::string name = "Generic Product";
	std::vector<Ing> recipe;
	const std::vector<Ingredient> * ref = nullptr;

public:
	Product();
	Product(const std::string& name, const std::vector<Ing>& recipeToSet, const std::vector<Ingredient> & refToSet);
	Product(const std::string& name, const std::vector<Ing>& recipeToSet);
	Product(const Product & other);
	Product& operator = (const Product & other);
	virtual ~Product();

	const std::string getName() const;
	virtual double getPrice() const override;
	const std::vector<Ing> & getRecipe() const;

	void setRef(const std::vector<Ingredient> & refToSet);

	friend bool operator == (const Product & src, const Product & other);
	friend bool operator != (const Product & src, const Product & other);
	
	friend std::istream& operator >>(std::istream& in, Product & other);
	friend std::ostream& operator <<(std::ostream& out, const Product & other);

};

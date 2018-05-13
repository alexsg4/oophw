#pragma once
#include "Item.h"

#include <string>
#include <vector>

class Ingredient;

class Product :
	public Item
{
public:
	//A simple 2 (x,y) point class
	struct Point
	{
		double id = -1;
		double qty = 1;

		Point(const int id, const int qty) : id(id), qty(qty) {}
		friend bool operator == (const Point & i1, const Point & i2)
		{
			return (i1.id == i2.id && i1.qty == i2.qty);
		}

		friend bool operator != (const Point & i1, const Point & i2)
		{
			return !(i1==i2);
		}

		Point& operator = (const Point& other)
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
	std::vector<Point> recipe;
	const std::vector<Ingredient> * ref = nullptr;

public:
	Product();
	Product(const std::string& name, const std::vector<Point>& recipeToSet, const std::vector<Ingredient> & refToSet);
	Product(const std::string& name, const std::vector<Point>& recipeToSet);
	Product(const Product & other);
	Product& operator = (const Product & other);
	virtual ~Product();

	const std::string getName() const;
	virtual double getPrice() const override;
	const std::vector<Point> & getRecipe() const;

	void setRef(const std::vector<Ingredient> & refToSet);

	friend bool operator == (const Product & src, const Product & other);
	friend bool operator != (const Product & src, const Product & other);
	
	friend std::istream& operator >>(std::istream& in, Product & other);
	friend std::ostream& operator <<(std::ostream& out, const Product & other);

};

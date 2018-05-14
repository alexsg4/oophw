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
		double x = -1;
		double y = 1;

		Point(const int x, const int y) : x(x), y(y) {}
		friend bool operator == (const Point & i1, const Point & i2)
		{
			return (i1.x == i2.x && i1.y == i2.y);
		}

		friend bool operator != (const Point & i1, const Point & i2)
		{
			return !(i1==i2);
		}

		Point& operator = (const Point& other)
		{
			if (*this != other)
			{
				x = other.x;
				y = other.y;
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

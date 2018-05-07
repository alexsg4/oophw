#pragma once
#include "Item.h"
#include <string>
#include "Ingredient.h"

class Product :
	public Item
{

private:
	std::string name = "Generic Product";
	int * recipe = nullptr;
	Ingredient** ref = nullptr;
	size_t ingSize = 0;


public:
	Product();
	Product(const std::string& name, const int* comp, Ingredient** reff);
	Product(const Product & other);
	Product& operator = (const Product & other);
	virtual ~Product();

	const std::string getName() const;
	virtual double getPrice() const override;
	int** getRecipe();


	friend bool operator == (const Product & src, const Product & other);
	friend bool operator != (const Product & src, const Product & other);
	
	//TODO
	friend std::istream& operator >>(std::istream& in, Product & other);
	friend std::ostream& operator <<(std::ostream& out, const Product & other);

};
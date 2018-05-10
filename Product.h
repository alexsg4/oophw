#pragma once
#include "Item.h"
#include "Ingredient.h"

#include <string>
#include <vector>

class Product :
	public Item
{

private:
	std::string name = "Generic Product";
	std::vector<int> recipe;
	static const std::vector<Ingredient> * ref;

public:
	Product();
	Product(const std::string& name, const std::vector<int>& recipeToSet, const std::vector<Ingredient> & refToSet);
	Product(const Product & other);
	Product& operator = (const Product & other);
	virtual ~Product();

	const std::string getName() const;
	virtual double getPrice() const override;
	const std::vector<int> & getRecipe() const;

	void setRef(const std::vector<Ingredient> & refToSet);

	friend bool operator == (const Product & src, const Product & other);
	friend bool operator != (const Product & src, const Product & other);
	
	//TODO
	friend std::istream& operator >>(std::istream& in, Product & other);
	friend std::ostream& operator <<(std::ostream& out, const Product & other);

};

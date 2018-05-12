#pragma once
#include "Product.h"
class Pizza :
	public Product
{
public:
	//special characteristics of the product that are constant
	enum class Flags : char
	{
		VEG = 'V'	//fit for vegeratian consumption
		//add other flags here
	};

private:
	std::string flagStr;
	static const std::vector<Ingredient> * ref;

public:
	Pizza();
	Pizza(const std::string& name, const std::vector<Product::Ing>& recipeToSet, const std::vector<Ingredient> & refToSet, const std::string & flagToSet="");
	Pizza(const Pizza & other);
	Pizza& operator = (const Pizza & other);
	virtual ~Pizza();

	inline bool isVeg() const
	{
		return ( flagStr.find(static_cast<char>(Flags::VEG) != std::string::npos) );
	}

	inline std::string getFlags() const { return flagStr; }
	inline void setFlags(const std::string & flags) { flagStr = flags; }

	const std::string getName() const;
	virtual double getPrice() const override;
	const std::vector<Product::Ing> & getRecipe() const;

	void setRef(const std::vector<Ingredient> & refToSet);

	friend bool operator == (const Pizza & src, const Pizza & other);
	friend bool operator != (const Pizza & src, const Pizza & other);

	//TODO
	friend std::istream& operator >>(std::istream& in, Pizza & other);
	friend std::ostream& operator <<(std::ostream& out, const Pizza & other);








};


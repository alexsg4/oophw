#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "Ingredient.h"
#include "Pizza.h"
#include "Parser.h"

template<class T>
class Menu;

template<class T>
class Menu
{
private:
	
	//unused for now
	struct Section
	{
		std::string name;
		std::vector <double> mods;
		Section(const std::string & nm, const std::vector<double> md) : name(nm), mods(md) {}
	};

	std::vector<Ingredient> IngredientRef;
	std::vector<T> ProductRef;

	//unused for now
	std::vector<Section> Sections;

	//price modifiers
	std::vector<double> mods;
	
	//tracks product sales
	std::vector<int> Ledger;

	//tracks Vege product IDs
	std::set<int> VLedger;

	//generator files directory
	const std::string genDir = "gen/";

public:
	
	inline Menu()
	{
		loadIngredients();
		loadProducts();
		updateLedgers();
	};

	inline ~Menu() {};
	inline void showIngredients(std::ostream & out = std::cout)
	{
		if (IngredientRef.empty())
		{
			out << "Nu exista ingrediente. \n";
			return;
		}
		for (const auto& ing : IngredientRef)
		{
			//TODO alter after test
			out << ing <<": $"<<ing.getPrice()<<"\n";
		}
	}
	
	inline void showProducts(std::ostream & out = std::cout)
	{
		if (ProductRef.empty())
		{
			out << "Nu exista produse. \n";
			return;
		}
		
		for (size_t i=0; i < ProductRef.size(); i++)
		{
			out << i + 1 << ".\t" << ProductRef[i] << " \n";
		}
	}

	inline void sellProduct(const int productID, const int qty = 1)
	{
		if (id >= 0 && id < Ledger.size() && !Ledger.empty())
		{
			if (qty > 0){	Ledger[productID] += qty;	}
		}
	}

private:
	void loadIngredients();
	void loadProducts();
	void updateLedgers();

};

template<>
void Menu<Pizza>::loadIngredients()
{
	Parser<Ingredient> P1(genDir + "pizzaIng.in");
	P1.parseFile();
	std::vector<std::string> src;
	auto status = P1.getParsedData(src);

	if (status != Parser<Ingredient>::Status::PARSEOK)
	{
		return;
	}

	for (const std::string &elem : src)
	{
		std::istringstream iss(elem);
		Ingredient ingToAdd;
		iss >> ingToAdd;
		ingToAdd.setID(IngredientRef.size());

		IngredientRef.push_back(ingToAdd);
	}
}

template<>
void Menu<Pizza>::loadProducts()
{
	Parser<Pizza> P1(genDir + "pizza.in");
	P1.parseFile();

	std::vector<std::string> toAdd;
	auto status = P1.getParsedData(toAdd);

	if (status != Parser<Pizza>::Status::PARSEOK) { return; }

	//for every pizza
	for (size_t i = 0; i < toAdd.size(); i+=2)
	{
		//parse the title and flag line
		auto prod = P1.getStringToken(toAdd[i], '|');
		
		//prepare the recipe vector
		std::vector<Product::Point> tempRecipe;

		//count elements in recipe
		auto rec = P1.getStringToken(toAdd[i + 1], ',');
		for (auto &x : rec) 
		{ 
			//parse each ingredient
			auto ing = P1.getStringToken(x, '|');
			
			P1.trimWhitespace(ing[0]);
			int qty = 1;
			
			if (ing.size() > 1)
			{
				P1.trimWhitespace(ing[1]);
				qty = std::stoi(ing[1]);
			}

			//check ingredient against refrence in Menu
			for (auto const & ref : IngredientRef)
			{
				//update recipe
				if (ref.getName() == ing[0])
				{
					Product::Point temp(ref.getID(), qty);
					tempRecipe.push_back(temp);
				}

			}

		}

		Pizza pizzaToAdd(prod[0], tempRecipe, IngredientRef);
		//set flags if they exist
		if (prod.size() > 1) { pizzaToAdd.setFlags(prod[1]); }

		//add product
		ProductRef.push_back(pizzaToAdd);

		//add Veg to separate ledger
		if (pizzaToAdd.isVeg())
		{
			VLedger.insert(ProductRef.size() - 1);
		}
 	}
}

template <class T>
void Menu<T>::updateLedgers()
{
	if (Ledger.size() < ProductRef.size())
	{
		Ledger.reserve(ProductRef.size());
		for (size_t i = Ledger.size(); i < ProductRef.size(); i++)
		{
			Ledger.push_back(0);
			//add Veg to separate ledger
			if (ProductRef[i].isVeg())
			{
				VLedger.insert(i);
			}
		}
	}
}
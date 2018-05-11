#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Ingredient.h"
#include "Pizza.h"
#include "Parser.h"

template<class T>
class Menu;

template<class T>
class Menu
{
private:
	std::vector<Ingredient> IngredientRef;
	std::vector<T> ProductRef;

	//tracks product sales
	std::vector<int> Ledger;

	//generator files directory
	const std::string genDir = "gen/";

public:
	inline Menu() 
	{
		loadIngredients();
		loadProducts();
	};
	inline ~Menu() {};
	inline void showIngredients(std::ostream & out = std::cout)
	{
		if (IngredientRef.empty())
		{
			out << "No ingredients. \n";
			return;
		}
		for (const auto& ing : IngredientRef)
		{
			//TODO alter after test
			out << ing <<": $"<<ing.getPrice()<<"\n";
		}
	}

private:
	void loadIngredients();
	void loadProducts();

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

		IngredientRef.push_back(ingToAdd);
	}
}

//TODO
template<>
void Menu<Pizza>::loadProducts()
{
	Parser<Pizza> P1("pizza.in");
}


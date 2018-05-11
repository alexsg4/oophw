// pizzaParlor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>

#include "Menu.h"
#include "Pizza.h"

int main()
{

	std::vector<int> recipe;
	std::vector<Ingredient> ing;
	std::vector<Ingredient> ing2;

	for (size_t i = 0; i < 4; i++)
	{
		ing.push_back(Ingredient(24.36*(i + 5)));
		ing2.push_back(Ingredient(10.11*(i + 2)));
		recipe.push_back(static_cast<int>(i + 6));
	}


	std::cout << "Ing\n";
	Pizza pizza("Test Pizza", recipe, ing);

	std::cout << pizza << "\n";
	for (size_t i = 0; i < ing.size(); i++)
	{
		std::cout << ing[i] << " : $" << ing[i].getPrice() << " x " << recipe[i] << " \n";
	}

	std::cout << "\nIng2\n";
	pizza.setRef(ing2);
	std::cout << pizza << "\n";
	for (size_t i = 0; i < ing2.size(); i++)
	{
		std::cout << ing2[i]<<" : $"<<ing2[i].getPrice()<< " x " << recipe[i] << " \n";
	}
	
	std::cout << "\n\n";
	
	for (int i = 0; i < 10; i++) { std::cout << "==="; }
	std::cout << "\n";

	Menu<Pizza> M1;
	M1.showIngredients();
	for (int i = 0; i < 10; i++) { std::cout << "==="; }
	
	std::cout << "\n\n";
	
	return 0;
}

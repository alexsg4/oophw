// pizzaParlor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

#include "Ingredient.h"
#include "Product.h"

int main()
{

	std::vector<int> recipe;
	std::vector<Ingredient> ing;
	std::vector<Ingredient> ing2;

	for (size_t i = 0; i < 4; i++)
	{
		ing.push_back(Ingredient(i, 24.36*(i + 5)));
		ing2.push_back(Ingredient(i, 10.11*(i + 2)));
		recipe.push_back(static_cast<int>(i + 6));
	}


	std::cout << "\n Ing\n";
	Product pizza("Pizza", recipe, ing);
	std::cout << pizza << "\n";
	for (size_t i = 0; i < ing.size(); i++)
	{
		std::cout << ing[i] << " x "<<recipe[i]<<" \n";
	}

	std::cout << "\n Ing2\n";
	pizza.setRef(ing2);
	std::cout << pizza << "\n";
	for (size_t i = 0; i < ing2.size(); i++)
	{
		std::cout << ing2[i] << " x " << recipe[i] << " \n";
	}

	std::cout << "\n";
	return 0;
}

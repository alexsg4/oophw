// pizzaParlor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Ingredient.h"
#include "Product.h"

int main()
{
	//TESTING
	
	size_t ingSize = Ingredient::getTypesNum();
	Ingredient** ing = new Ingredient*[ingSize];

	std::vector<int> price;


	for (size_t i = 0; i < ingSize; i++)
	{
		ing[i] = new Ingredient(i, 24.36*(i + 5) );
		price.push_back(i + 6);
	}

	Product pizza("Pizza", price, ing);
	std::cout << pizza.getName() << ": $" << pizza.getPrice() << "\n\n";

	for (size_t i = 0; i < ingSize; i++)
	{
		std::cout << *ing[i] << " \n";
		delete ing[i];
	}
    
	std::cout << "\n";
	return 0;
}


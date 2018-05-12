// pizzaParlor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>

#include "Menu.h"
#include "Pizza.h"

int main()
{

	Menu<Pizza> M1;

	for (int i = 0; i < 10; i++) { std::cout << "==="; }
	std::cout << "\n";
	M1.showProducts();
	for (int i = 0; i < 10; i++) { std::cout << "==="; }
	
	std::cout << "\n\n";
	
	return 0;
}

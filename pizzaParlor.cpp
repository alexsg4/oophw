// pizzaParlor.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>

#include "pizzaParlor.h"
#include "Menu.h"
#include "Pizza.h"

int main()
{

	Menu<Pizza> M1;
	
	static unsigned selection = 0;
	int temp = 0;
	MenuItem choice = MenuItem::WAIT;
	
	CS_init();

	while (choice != MenuItem::QUIT)
	{
		CS_showMenu();
		//handle bad input
		while (std::cout << "Alegerea dvs. : " && !(std::cin >> temp))
		{
			std::cin.clear(); //clear bad input flag
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Optiunea nu exista. Incercati din nou\n";
			WAIT(1);
			CS_showMenu();
		}

		switch ((MenuItem)temp)
		{
		case MenuItem::ORD:
			CLEAR;

			placeOrder(M1);
			
			CS_waitUserInput();
			break;

		case MenuItem::SALES:
			CLEAR;
			showSales(M1);
			CS_waitUserInput();
			break;

		case MenuItem::INGS:
			CLEAR;
			showIngredients(M1);
			CS_waitUserInput();
			break;

		

		case MenuItem::QUIT:
			CLEAR;
			std::cout << "La revedere...\n\n";
			WAIT(1);
			choice = MenuItem::QUIT;
			break;
		}
	}
	
	return 0;
}

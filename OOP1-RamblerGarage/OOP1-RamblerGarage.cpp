// OOP1-RamblerGarage.cpp : Defines the entry point for the console application.

#include "Rambler.h"

int main()
{
	//TODO add a stopwatch function

	//TODO Remove
	//TESTING $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	/* Works 
	RArray<Vehicle*> testFleet;
	Vehicle* c1 = new Car("Test", "TestME");
	c1->applyRandomDamage();
	testFleet.add(c1);
	testFleet.display();
	testFleet[0]->diagnose();
	*/
	//TESTING END $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	RArray<Vehicle*> fleet;
	static unsigned selection = 0;

	init(fleet);
	int temp = 0;
	MenuItem choice = MenuItem::WAIT;

	while (choice != MenuItem::QUIT)
	{
		CS_showMenu();	
		//handle bad input
		while (std::cout << "Alegerea dvs. : " && !(std::cin >> temp))
		{
			std::cin.clear(); //clear bad input flag
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Optiunea nu exista. Incercati din nou\n";
			WAIT(1)
			CS_showMenu();
		}

		switch ((MenuItem)temp)
		{
		case MenuItem::ADD:
			CLEAR
			addVehicle(fleet);
			break;
		
		case MenuItem::DIAG:
			CLEAR
			if (fleet.isEmpty())
			{
				std::cout << "Nu mai sunt vehicule in atelier.\n";
				break;
			}

			displayFleet(fleet);

			CS_printDivider();
			while ( (std::cout << "Alegerea dvs. [1-"<<fleet.size()<<"]: ") && !(std::cin >> selection) )
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Optiunea nu exista. Incercati din nou\n";
			}
			
			fleet[selection-1]->diagnose();
			CS_printDivider();
			CS_waitUserInput();

			break;

		case MenuItem::DIAGA:
			CLEAR
			diagnoseFleet(fleet);
			break;
		
		case MenuItem::DISP:
			if (fleet.isEmpty())
			{
				std::cout << "Nu se pot afisa detalii despre vehiculul selectat. \n";
				break;
			}
			std::cout << *fleet[selection] << "\n";
			CS_waitUserInput();
			break;

		case MenuItem::DAMAGE:
			CLEAR
			if (fleet.isEmpty())
			{
				std::cout << "Momentan, atelierul este gol. \n";
				break;
			}
			displayFleet(fleet);
			CS_printDivider();
			while ((std::cout << "Alegerea dvs. [1-" << fleet.size() << "]: ") && !(std::cin >> selection))
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Optiunea nu exista. Incercati din nou\n";
			}
			selection--;
			damageVehicle(fleet[selection]);

			break;
		case MenuItem::CLR:
			fleet.erase();
			std::cout << "Atelier eliberat\n";
			WAIT(1);
			break;
		
		case MenuItem::REM:
			CLEAR
				if (fleet.isEmpty())
				{
					std::cout << "Nu mai sunt vehicule in atelier.\n";
					break;
				}

			displayFleet(fleet);

			CS_printDivider();
			while ((std::cout << "Alegerea dvs. [1-" << fleet.size() << "]: ") && !(std::cin >> selection))
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Optiunea nu exista. Incercati din nou\n";
			}

			fleet.removeById(selection - 1);
			std::cout << "Vehiculul a fost inlaturat\n";
			
			break;

		case MenuItem::QUIT:
			CLEAR
			std::cout << "La revedere...\n\n";
			WAIT(2);
			choice = MenuItem::QUIT;
			break;
		default:
			CLEAR
			std::cout << "BAD STUFF\n";
			break;
		}
	}
	
    return 0;
}
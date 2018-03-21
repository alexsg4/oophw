// OOP1-RamblerGarage.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"
#include <cstdlib>
#include <queue>
#include <fstream>
#include <limits>
#include <ctime>

#ifdef _WIN32
#include <windows.h>

#define CLEAR system("cls");
#define WAIT(n) Sleep((n*1000));
#define TERMSIZE system("MODE CON COLS=155 LINES=50");
#define GDIR "generators\\"
#define ADIR "ascii\\"

#endif // _WIN32

#ifdef linux
#include <unistd.h>
#define CLEAR system("clear");
#define WAIT(n) sleep(n);
#define GDIR "generators/"
#define ADIR "ascii/"

#endif // linux

enum class MenuItem { WAIT, ADD, DIAG, DIAGA, DISP, DAMAGE, QUIT};

void init(std::queue<Vehicle*> & fleet, unsigned &capacity);
void showMenu();
void populateFleet(std::queue<Vehicle*> &fleet, const unsigned capacity, unsigned elementsToAdd);
void addVehicle(std::queue<Vehicle*> &fleet, const unsigned capacity);
void diagnoseFleet(std::queue<Vehicle*> &fleet);

int main()
{
	//sensible default
	static unsigned fleetCapacity = 10;
	std::queue<Vehicle*> fleet;
	
	init(fleet, fleetCapacity);
	int temp = 0;
	MenuItem choice = MenuItem::WAIT;

	while (choice != MenuItem::QUIT)
	{
		showMenu();	
		//handle bad input
		while (std::cout << "Alegerea dvs. : " && !(std::cin >> temp))
		{
			std::cin.clear(); //clear bad input flag
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			std::cout << "Optiunea nu exista. Incercati din nou\n";
			WAIT(1)
			showMenu();
		}

		switch ((MenuItem)temp)
		{
		case MenuItem::ADD:
			CLEAR
			addVehicle(fleet, fleetCapacity);
			break;
		case MenuItem::DIAG:
			CLEAR
			fleet.back()->diagnose();
			break;
		case MenuItem::DIAGA:
			CLEAR
			diagnoseFleet(fleet);
			break;
		case MenuItem::DISP:
			CLEAR
			std::cout << fleet.back()->getMake() << " " << fleet.back()->getModel() << " " << fleet.back()->getYear() << "\n";
			break;
		case MenuItem::DAMAGE:
			CLEAR
			fleet.back()->applySpecificDamage();
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

//displays splash screen, sets correct terminal width on windows, gets fleet capacity from user
void init(std::queue<Vehicle*> & fleet, unsigned &capacity)
{
	//show splash screen
	TERMSIZE
	std::string s = ADIR;
	std::ifstream welcome(s + "welcome.in");

	if (welcome.is_open())
	{
		while (std::getline(welcome, s))
		{
			std::cout << s;
		}
		WAIT(3)
		CLEAR 
		//std::cout << "\n\n";
	}

	else { std::cout << "Welcome to Rambler Garage\n\n"; }

	welcome.close();

	unsigned temp = 0;
	//ask user for fleet capacity
	std::cout << "Dupa calculele noastre putem repara maxim " << capacity << " vehicule astazi.\n";
	std::cout << "Totusi, n-am putea merge mai departe fara indrumarea mecanicului sef. Cate vehicule ar trebui sa reparam?\n";
	while ( (std::cout << "Raspuns: ") && !(std::cin >> temp))
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); //discard bad input
		std::cout << "Numar invalid de vehicule Incercati din nou. \n";
		WAIT(1)
	}
	
	if (temp > 0)
	{
		capacity = temp;
		if (temp == 1)
		{
			std::cout << "Pare cam putin, dar seful stie cel mai bine.\n";
			WAIT(3)
		}
		else if (temp < 20)
		{
			std::cout << "OK, asa ramane. Vom primi " << capacity << " vehicule\n";
			WAIT(3)
		}
		else 
		{ 
			std::cout << "OK, asa ramane. Vom primi " << capacity << " de vehicule\n"; 
			WAIT(3)
		}
	}
	else 
	{ 
		std::cout << "OK, ramanem la " << capacity << " atunci.\n"; 
		WAIT(3)
	}

	std::cout << "Putem incepe sa lucram la o parte din vehicule chiar acum.\n";
	std::cout << "Cate ar trebui sa fie (maxim "<< capacity<<")\n";
	
	//TODO needs testing
	while (((std::cout << "Raspuns: ") && !(std::cin >> temp) ) || temp > capacity)
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); //discard bad input
		std::cout << "Numar invalid de vehicule incercati din nou. \n";
		WAIT(1)
			CLEAR
	}

	//TODO Needs indication of success
	populateFleet(fleet, capacity, temp);

}

void showMenu()
{
	CLEAR
	std::cout << "\t\t\t Meniu \t\t\t\n";

	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::ADD << ". Adauga vehicul. \t\t\t\t\t\n";
	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::DIAG << ". Diagnosticare vehicul curent. \t\t\t\t\t\n";
	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::DIAGA << ". Diagnosticare vehicule prezente. \t\t\t\t\t\n";
	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::DISP << ". Afisare vehicul curent. \t\t\t\t\t\n";
	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::DAMAGE << ". Adaugare defectiuni vehicul curent. \t\t\t\t\t\n";
	std::cout << "\t\t\t\t\t " << (unsigned)MenuItem::QUIT << ". Iesire. \t\t\t\t\t\n";

}

//TODO correct formatting for make and model
void populateFleet(std::queue<Vehicle*> &fleet, const unsigned capacity, unsigned elementsToAdd)
{
	if (fleet.size() + elementsToAdd <= capacity && elementsToAdd)
	{
		srand((unsigned)time(0));
		std::string s = GDIR;
		
		//open vehicle type generators for make and model
		std::ifstream make(s + "genericMakes.in");
		std::ifstream model(s + "genericModels.in");
		
		//select apppropriate generator
			//for this example we will use the two generic files

		//count lines 
		unsigned mLines = 0, modLines = 0, mi = 0, modi = 0;
		std::string m, mod;
		
		if (make.is_open())
		{
			while (std::getline(make, m))
			{
				mLines++;
			}
		}

		if (model.is_open())
		{
			while (std::getline(model, mod))
			{
				modLines++;
			}
		}
		
		//TODO ensure rand() return different on every iteration 
		while (elementsToAdd)
		{
			//random choose vehicle type
			Part::Mount vehType = (Part::Mount)(rand() % Part::getMountTypes() + 1);

			//reset file pointers
			make.clear();
			make.seekg(0, std::ios::beg);

			model.clear();
			model.seekg(0, std::ios::beg);

			//clear strings (optional, needs testing)
			m.clear();
			mod.clear();

			//random select lines for make and model
			mi = rand() % mLines;
			modi = rand() % modLines;

			//extract from files
			for (unsigned i = 0; i < mi; i++)
			{
				make.ignore();
			}
			make >> m;

			for (unsigned i = 0; i < modi; i++)
			{
				model.ignore();
			}
			model >> mod;

			//random select year (and doors for cars)
			unsigned year = 1950 + rand() % 150, doors = 0;

			//create new vehicle with make and model 
			//add vehicle to list
			switch (vehType)
			{
			case Part::Mount::CAR:
				doors = (rand() % 2) ? 2 : 4;
				fleet.emplace(new Car(m, mod, year, doors));
				break;
			case Part::Mount::MOTO:
				fleet.emplace(new Motorbike(m, mod, year));
				break;
			case Part::Mount::BIKE:
				fleet.emplace(new Bike(m, mod, year));
				break;
			default:
				break;
			}
			//damage vehicle
			fleet.back()->applyRandomDamage();
			
			//decrement elements
			elementsToAdd--;
		}
	}

	else
	{
		std::cout << "Could not populate fleet.";
	}
}

//Removal will take place once vehicle is diagnosed and is handled by the structure holding the fleet
void addVehicle(std::queue<Vehicle*> &fleet, const unsigned capacity)
{
	//if fleet size < capacity
	if (fleet.size() < capacity)
	{
		//ask user for type, make, model, year
		std::string make, model;
		unsigned year = 0, doors = 0, temp = 0;
		Part::Mount type;

		std::cout << "Tipuri de vehicule disponibile: ";
		for (unsigned i = 0; i <= Part::getMountTypes(); i++)
		{
			switch ((Part::Mount)i)
			{
			case Part::Mount::CAR:
				std::cout << i << ". Masina ";
				break;
			case Part::Mount::MOTO:
				std::cout << i << ". Motocicleta ";
				break;
			case Part::Mount::BIKE:
				std::cout << i << ". Bicicleta ";
				break;
			default:
				break;
			}
		}

		std::cout << "\nAti ales: ";

		while (!(std::cin >> temp) && (temp < 0 || temp > 3))
		{
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');;
			std::cout << "Tip vehicul invalid. Incercati din nou. \n";
			WAIT(1)
			CLEAR
		}

		type = (Part::Mount)temp;

		std::cout << "Dati marca, modelul si anul fabricatiei: ";
		std::cin >> make >> model >> year;
		if (type == Part::Mount::CAR)
		{
			std::cout << "Dati numarul de usi [2 sau 4]: ";
			std::cin >> doors;
		}

		//create vehicle and add it to fleet if possible
		switch (type)
		{
		case Part::Mount::CAR:
			fleet.emplace(new Car(make, model, year, doors));
			std::cout << "Masina a fost adaugata. \n";
			break;
		case Part::Mount::MOTO:
			fleet.emplace(new Motorbike(make, model, year));
			std::cout << "Motocicleta a fost adaugata. \n";
			break;
		case Part::Mount::BIKE:
			fleet.emplace(new Bike(make, model, year));
			std::cout << "Bicicleta a fost adaugata. \n";
			break;
		default:
			std::cout << "Ne pare rau. Nu putem repara acest tip de vehicul\n";
			break;
		}
	}
	else
	{
		std::cout << "Ne pare rau. Momentan, mecanicii nostri lucreaza la capacitate maxima. Incercati mai tarziu.\n";
	}
}

//side effect: fleet is cleared
void diagnoseFleet(std::queue<Vehicle*> &fleet)
{
	while (!fleet.empty())
	{
		//diagnose
		fleet.front()->diagnose();
		WAIT(5)
		CLEAR
		delete fleet.front();
		fleet.pop();
	}
}





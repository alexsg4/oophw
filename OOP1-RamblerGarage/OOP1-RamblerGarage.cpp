// OOP1-RamblerGarage.cpp : Defines the entry point for the console application.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <iomanip>

#include "RArray.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"

#define COLS 155
#define ROWS 50
#define GDIR "../Assets/generators/"
#define ADIR "../Assets/ascii/"

#ifdef _WIN32
#include <windows.h>

#define CLEAR system("cls");
#define WAIT(n) Sleep((n*1000));
#define TERMSIZE system("MODE CON COLS=155 LINES=50");

#endif // _WIN32

#ifdef __linux__
#include <unistd.h>
#define CLEAR system("clear");
#define WAIT(n) sleep(n);
#define TERMSIZE ;

#endif // __linux__

//TODO Add Drag Strip class (distance = 402m)

//Menu specifics
enum class MenuItem { WAIT, ADD, DIAG, DIAGA, DISP, DAMAGE, REM, CLR, QUIT};

void showArt(const std::string file, const size_t width = COLS, const std::string alternate="");
void waitUserInput();
void showMenuEntry(const unsigned num, const std::string s, const unsigned cols = COLS);
void showMenu();
void printDivider(const char c = '=', const unsigned len = COLS);

//fleet wrappers
void addVehicle(RArray<Vehicle*> &fleet);
void diagnoseFleet(RArray<Vehicle*> &fleet);
void populateFleet(RArray<Vehicle*> &fleet, unsigned elementsToAdd);
void displayFleet(RArray <Vehicle*> &fleet);

//initialise program
void init(RArray<Vehicle*> &fleet);

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
			//fleet.display(); TODO test and remove afterwards

			printDivider();
			while ( (std::cout << "Alegerea dvs. [1-"<<fleet.size()<<"]: ") && !(std::cin >> selection) )
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Optiunea nu exista. Incercati din nou\n";
			}
			
			fleet[selection-1]->diagnose();
			printDivider();
			waitUserInput();

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
			waitUserInput();
			break;
		
		case MenuItem::DAMAGE:
			CLEAR
			if (fleet.isEmpty())
			{
				std::cout << "Momentan, atelierul este gol. \n";
				break;
			}
			displayFleet(fleet);
			//fleet.display(); TODO remove
			printDivider();
			while ((std::cout << "Alegerea dvs. [1-" << fleet.size() << "]: ") && !(std::cin >> selection))
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
				std::cout << "Optiunea nu exista. Incercati din nou\n";
			}

			fleet[selection-1]->applySpecificDamage(true);
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

//###################################################################################

void showArt(const std::string file, const size_t width, const std::string alternate)
{
	std::string s = ADIR;
	std::ifstream fin(s + file);

	if (fin.is_open())
	{
		while (std::getline(fin, s))
		{
			std::cout << std::setw(width) << s;
		}
	}

	else 
	{ 
		std::cout << alternate; 
	}

	std::cout << "\n\n";

	fin.close();
}

void waitUserInput()
{
	std::cout << "Apasati <Enter> a continua...\n";
	//flush cin
	std::cin.clear();
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	//wait for user input
	while (!std::cin.get()) {}
}

void showMenuEntry(const unsigned num, const std::string s, const unsigned cols)
{
	std::cout << std::setw((cols - s.length() - 4) / 2) << num << ". " + s + ".";
	std::cout << "\n";
}

//TODO populate all options
void showMenu()
{
	CLEAR;
	showArt("title.in", 155);
	showArt("menu.in", 155, "\t\t\t Meniu \t\t\t");

	showMenuEntry((unsigned)MenuItem::ADD, "Adaugare vehicul");
	showMenuEntry((unsigned)MenuItem::DIAG, "Diagnosticare vehicul.");
	showMenuEntry((unsigned)MenuItem::DIAGA, "Diagnosticarea tuturor vehiculelor");
	showMenuEntry((unsigned)MenuItem::DISP, "Afisare detalii vehicul");
	showMenuEntry((unsigned)MenuItem::DAMAGE, "Adaugare defectiuni unui vehicul");
	showMenuEntry((unsigned)MenuItem::REM, "Inlaturare vehicul");
	showMenuEntry((unsigned)MenuItem::CLR, "Eliberare atelier");
	showMenuEntry((unsigned)MenuItem::QUIT, "Iesire");
}

void printDivider(const char c, const unsigned len)
{
	for (unsigned i = 0; i < len; i++)
	{
		std::cout << c;
	}
	std::cout << "\n";
}

//###################################################################################

void addVehicle(RArray<Vehicle*> &fleet)
{
	std::cout << "Tipuri de vehicule disponibile: \n";
	for (unsigned i = 0; i <= Part::getMountTypes(); i++)
	{
		switch ((Part::Mount)i)
		{
		case Part::Mount::CAR:
			std::cout << i << ". Automobil \n";
			break;
		case Part::Mount::MOTO:
			std::cout << i << ". Motocicleta \n";
			break;
		case Part::Mount::BIKE:
			std::cout << i << ". Bicicleta \n";
			break;
		}
	}

	//ask user for type, make, model, year
	std::string make, model;
	unsigned year = 0, doors = 0, temp = 0;
	Part::Mount type;

	std::cout << "\nAti ales: ";

	while (!(std::cin >> temp) || (temp <= 0 || temp > 3))
	{
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "Tip vehicul invalid. Incercati din nou. \n";
	}

	type = (Part::Mount)temp;

	std::cout << "Dati marca, modelul si anul fabricatiei: ";
	std::cin >> make >> model >> year;
	if (type == Part::Mount::CAR)
	{
		std::cout << "Dati numarul de usi [2 sau 4]: ";
		std::cin >> doors;
	}

	Vehicle* toAdd = nullptr;
	//create vehicle and add it to fleet if possible
	switch (type)
	{
	case Part::Mount::CAR:
		toAdd = new Car(make, model, year, doors);
		std::cout << "Masina a fost adaugata. \n";
		break;

	case Part::Mount::MOTO:
		toAdd = new Motorbike(make, model, year);
		std::cout << "Motocicleta a fost adaugata. \n";
		break;

	case Part::Mount::BIKE:
		toAdd = new Bike(make, model, year);
		std::cout << "Bicicleta a fost adaugata. \n";
		break;

	default:
		std::cout << "Ne pare rau. Nu putem repara acest tip de vehicul\n";
		WAIT(2)
		break;
	}

	fleet.add(toAdd);
}

void diagnoseFleet(RArray<Vehicle*> &fleet)
{
	if (fleet.isEmpty())
	{
		std::cout << "Momentan nu sunt vehicule in atelier.\n";
		return;
	}

	for (unsigned i=0; i<fleet.size(); i++)
	{
		fleet[i]->diagnose();
		printDivider();
		waitUserInput();
		CLEAR;
	}
}

void populateFleet(RArray<Vehicle*> &fleet, unsigned elementsToAdd)
{
	if (!elementsToAdd) 
	{
		return;
	}
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

		//clear strings
		m.clear();
		mod.clear();

		//random select lines for make and model
		mi = (rand() + elementsToAdd + 312341) % mLines + 1;
		modi = (rand() + elementsToAdd + 54837) % modLines + 1;

		//extract from files
		for (unsigned i = 0; i < mi; i++)
		{
			make.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		make >> m;

		for (unsigned i = 0; i < modi; i++)
		{
			model.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		model >> mod;

		//random select year (and doors for cars)
		unsigned year = 1950 + rand() % 150, doors = 0;

		//create new vehicle with make and model, add vehicle to list if possible
		Vehicle* toAdd = nullptr;
		switch (vehType)
		{
		case Part::Mount::CAR:
			doors = (rand() % 2) ? 2 : 4;
			toAdd = new Car(m, mod, year, doors);
			break;
		case Part::Mount::MOTO:
			toAdd = new Motorbike(m, mod, year);
			break;
		case Part::Mount::BIKE:
			toAdd = new Bike(m, mod, year);
			break;
		default:
			break;
		}

		//damage vehicle
		if (toAdd)
		{
			toAdd->applyRandomDamage();

			fleet.add(toAdd);

			//decrement elements
			elementsToAdd--;
		}
	}
}

void displayFleet(RArray<Vehicle*> &fleet)
{
	unsigned size = fleet.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (fleet[i]) { std::cout << i + 1 << ". " << *fleet[i] << "\n"; }
	}
	std::cout << "\n";
}


//displays splash screen, sets correct terminal width on windows, gets fleet capacity from user
void init(RArray<Vehicle*> &fleet)
{
	//Sensible default
	static unsigned capacity = 20;

	//Set correct terminal size on windows
	TERMSIZE;

	//show splash screen
	showArt("welcome.in", COLS, "Welcome to Rambler Garage!");

	unsigned temp = 0;
	//ask user for fleet capacity
	std::cout << "Dupa calculele noastre putem repara in jur de " << capacity << " vehicule astazi.\n";
	std::cout << "Totusi, n-am putea merge mai departe fara indrumarea mecanicului sef. Cate vehicule ar trebui sa reparam?\n";
	while ((std::cout << "Raspuns: ") && !(std::cin >> temp))
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
		}
		else if (temp < 20)
		{
			std::cout << "OK, asa ramane. Vom primi " << capacity << " vehicule\n";
		}
		else
		{
			std::cout << "OK, asa ramane. Vom primi " << capacity << " de vehicule\n";
		}
		WAIT(2)
	}
	else
	{
		std::cout << "OK, ramanem la " << capacity << " atunci.\n";
		WAIT(2)
	}

	std::cout << "Putem incepe sa lucram la o parte din vehicule chiar acum.\n";
	std::cout << "Cate ar trebui sa fie?\n";

	while (((std::cout << "Raspuns (maxim " << capacity << "):  ") && !(std::cin >> temp)) || temp > capacity)
	{
		std::cin.clear(); //clear bad input flag
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); //discard bad input
		std::cout << "Numar invalid de vehicule incercati din nou. \n";
		WAIT(1)
		CLEAR
	}

	//TODO Needs indication of success
	fleet.expand(capacity);
	populateFleet(fleet, capacity);
}





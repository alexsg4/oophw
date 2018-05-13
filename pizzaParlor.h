#pragma once

// Set of funtions for console display and user interaction

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <iomanip>

#include "Menu.h"
#include "Pizza.h"

#define _STR(s) #s
#define STR(s) _STR(s)

#define COLS 155
#define ROWS 50

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

//Menu specifics
enum class MenuItem 
{ 
	WAIT,		//no action
	ORD,		//place order  
	SALES,		//show sales figures
	INGS,		//show ingredients
	QUIT		//exit program
};

//console specifics
void CS_showArt(const std::string file, const size_t width = COLS, const std::string alternate = "");
void CS_waitUserInput();
void CS_showMenuEntry(const unsigned num, const std::string s, const unsigned cols = COLS);
void CS_showMenu();
void CS_printDivider(const char c = '=', const unsigned len = COLS);

//menu wrappers
void placeOrder(const Menu<Pizza> &menu);
void showSales(const Menu<Pizza> &menu);
void showIngredients(const Menu<Pizza> &menu);

//initialise program
void CS_init();

//###################################################################################

void CS_showArt(const std::string file, const size_t width, const std::string alternate)
{
	std::string ADIR(STR(ASSETS));
	ADIR = ADIR + "/ascii/";

	std::ifstream fin(ADIR + file);

	std::string s;

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

void CS_waitUserInput()
{
	std::cout << "\n";
	std::cout << "Apasati <Enter> a continua...\n";
	//flush cin
	std::cin.clear();
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	//wait for user input
	while (!std::cin.get()) {}
}

void CS_showMenuEntry(const unsigned num, const std::string s, const unsigned cols)
{
	std::cout << std::setw((cols - s.length() - 4) / 2) << num << ". " + s + ".";
	std::cout << "\n";
}

void CS_showMenu()
{
	CLEAR;
	CS_showArt("title.in", 155);
	CS_showArt("menu.in", 155, "\t\t\t Meniu \t\t\t");

	CS_showMenuEntry((unsigned)MenuItem::ORD, "Plasare comanda..");
	CS_showMenuEntry((unsigned)MenuItem::SALES, "Afisare vanzari..");
	CS_showMenuEntry((unsigned)MenuItem::INGS, "Afisare lista ingrediente..");
	CS_showMenuEntry((unsigned)MenuItem::QUIT, "Iesire");
}

void CS_printDivider(const char c, const unsigned len)
{
	for (unsigned i = 0; i < len; i++)
	{
		std::cout << c;
	}
	std::cout << "\n";
}

//###################################################################################

void placeOrder(const Menu<Pizza>& menu)
{
	CS_printDivider();
	std::cout << "\t\t\t Comanda :\n";
	CS_printDivider();
	
	//TODO implement
}

void showSales(Menu<Pizza> &menu)
{
	CS_printDivider();
	std::cout << "\t\t\t Vanzari \n";
	CS_printDivider();
	std::cout << "\n";
	menu.showSales();

}

void showIngredients(Menu<Pizza> &menu)
{
	CS_printDivider();
	std::cout << "\t\t\t Ingrediente :\n";
	CS_printDivider();
	std::cout << "\n";
	menu.showIngredients();

}

//displays splash screen, sets correct terminal width on windows
void CS_init()
{
	//Set correct terminal size on windows
	TERMSIZE;

	//show splash screen
	CS_showArt("welcome.in", COLS, "Bun venit la Domino the Hutt, pizzeria dvs. preferata!");

	CS_waitUserInput();
}


// OOP0-GrandmaBakes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Circle.h"
#include "RightTriangle.h"
#include "Rectangle.h"

#define MAX_SHAPES 5

void printMenu();
int ADD(Shape** shapes, int n);
int REMOVE(Shape** shapes, int n, int k);
void STOC(Shape** shapes, int n);
void TOTAL(Shape** shapes, int n);

int main()
{
	std::cout << "Grandma bakes\n";
	int option = -1, choice = 0, ok = 0, n = 0, k = 0;
	Shape** shapes = new Shape*[MAX_SHAPES];

	while (option != 0)
	{
		printMenu();
		std::cout << "Alegerea ta este: ";
		std::cin >> option;

		switch (option)
		{
		case 0:
			std::cout << "\nLa revedere.\n";
			break;
		case 1:
			ok = 0;
			///!! TODO adauga metoda de retur la meniu
			while (ok != 1)
			{
				if (ADD(shapes, n))
				{
					n++;
					ok = 1;
				}
			}
			break;

		case 2:
			ok = 0;
			while (ok != 1)
			{
				std::cout << "Dati numarul formei de sters sau 9 pt retur: ";
				std::cin >> k;
				k--;
				///se verifica existenta in functie
				if (!REMOVE(shapes, n, k))
				{
					ok = 1;
					n--;
				}
			}
			break;

		case 3:
			std::cout << "\n Detalii forme: \n";
			STOC(shapes, n);
			break;

		case 4:
			std::cout << "\n Total ingrediente necesare (g): \n";
			TOTAL(shapes, n);
			break;

		default:
			break;
		};
	}

	delete[] shapes;
	return 0;
}

void printMenu()
{
	std::cout << "\nMeniu\n";
	std::cout << "1. adauga forma (max. " << MAX_SHAPES << ")\n";
	std::cout << "2. sterge forma\n";
	std::cout << "3. afiseaza detalii pt. toate formele\n";
	std::cout << "4. afiseaza total necesar ingrediente\n";
	std::cout << "0. iesire\n";
}

int ADD(Shape** shapes, int n)
{
	int l1 = 0, l2 = 0, h = 0;
	char type[20];

	if (n > MAX_SHAPES)
	{
		std::cout << "Nu se poate adauga forma noua.\n";
		return -1;
	}

	std::cout << "Dati tipul formei: ";
	std::cin >> type;

	if (strcmp(type, "patrat") * strcmp(type, "dreptunghi") * strcmp(type, "cerc") * strcmp(type, "triunghi") != 0)
	{
		std::cout << "Nu se poate adauga forma noua. Tip forma incorect. \n";
		return -1;
	}

	std::cout << "Dati dimensiunile bazei si inaltimea: ";

	if (!strcmp(type, "patrat"))
	{
		std::cin >> l1 >> h;
		shapes[n] = new Rectangle(l1, h);
	}

	if (!strcmp(type, "dreptunghi"))
	{
		std::cin >> l1 >> l2 >> h;
		shapes[n] = new Rectangle(l1, l2, h);
	}

	if (!strcmp(type, "triunghi"))
	{
		std::cin >> l1 >> l2 >> h;
		shapes[n] = new RightTriangle(l1, l2, h);
	}

	if (!strcmp(type, "cerc"))
	{
		std::cin >> l1 >> h;
		shapes[n] = new Circle(l1, h);
	}

	if (!shapes[n]) { return -1; }

	return 0;

}

int REMOVE(Shape** shapes, int n, int k)
{
	if (!shapes[k]) { return -1; }
	if (n == 0 || k > n)
	{
		std::cout << "Nu se poate sterge forma " << k << "!\n";
		return -1;
	}

	for (int i = k; i<n - 1; i++)
	{
		shapes[i] = shapes[i + 1];
	}
	delete shapes[n - 1];
	shapes[n - 1] = NULL;

	return 0;
}

void STOC(Shape** shapes, int n)
{
	if (n<1 || n > MAX_SHAPES)
	{
		std::cout << "Nu exista forme\n";
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (shapes[i])
		{
			shapes[i]->showDetails();
		}
	}
}

void TOTAL(Shape** shapes, int n)
{
	if (n<1 || n > MAX_SHAPES)
	{
		std::cout << "Nu exista forme\n";
		return;
	}

	int butter = 0, jam = 0;

	for (int i = 0; i < n; i++)
	{
		if (shapes[i])
		{
			butter += shapes[i]->getOuterArea();
			jam += shapes[i]->getVolume() * 2;
		}
	}

	if (butter*jam > 0)
	{
		std::cout << "Total gem: " << jam << "g\n";
		std::cout << "Total unt: " << butter << "g\n";
	}

	else
	{
		std::cout << "Eroare: Nu s-a putut determina totalul \n";
	}

}
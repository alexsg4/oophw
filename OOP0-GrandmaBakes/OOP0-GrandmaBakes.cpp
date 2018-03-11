// OOP0-GrandmaBakes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Circle.h"
#include "RightTriangle.h"
#include "Rectangle.h"

void printMenu(int max);
int ADD(Shape **&shapes, int &n, int max);
int REMOVE(Shape **&shapes, int &n, int max, int k);
void STOC(Shape **&shapes, int n, int max);
void TOTAL(Shape **&shapes, int n, int max);

int main()
{
	const int maxShapes = 5;
	std::cout << "Grandma bakes\n";
	int option = -1, choice = 0, ok = 0, n = 0, k = 0;
	Shape** shapes = new Shape*[maxShapes];

	while (option != 0)
	{
		printMenu(maxShapes);
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
				if (!ADD(shapes, n, maxShapes))
				{
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
				if (k == 9) { break; }
				k--;
				///se verifica existenta in functie
				if (!REMOVE(shapes, n, maxShapes, k))
				{
					ok = 1;
				}
			}
			break;

		case 3:
			std::cout << "\n Detalii forme: \n\n";
			STOC(shapes, n, maxShapes);
			break;

		case 4:
			std::cout << "\n Total ingrediente necesare (g): \n";
			TOTAL(shapes, n, maxShapes);
			break;

		default:
			break;
		};
	}

	for (int i = 0; i < n; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;

	return 0;
}

void printMenu(int max)
{
	std::cout << "\nMeniu\n";
	std::cout << "1. adauga forma (max. " << max << ")\n";
	std::cout << "2. sterge forma\n";
	std::cout << "3. afiseaza detalii pt. toate formele\n";
	std::cout << "4. afiseaza total necesar ingrediente\n";
	std::cout << "0. iesire\n";
}

int ADD(Shape**& shapes, int &n, int max)
{
	int l1 = 0, l2 = 0, h = 0;
	char type[20];

	if (n > max)
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

	n++;
	return 0;

}

int REMOVE(Shape**& shapes, int &n, int max, int k)
{
	if (!shapes[k]) { return -1; }
	if (n == 0 || k >= n || k < 0)
	{
		std::cout << "Nu se poate sterge forma " << k << "!\n";
		return -1;
	}

	delete shapes[k];

	for (int i = k; i<n; i++)
	{
		shapes[i] = shapes[i + 1];
	}
	shapes[--n] = nullptr;

	return 0;
}

void STOC(Shape**& shapes, int n, int max)
{
	if (n<1 || n > max)
	{
		std::cout << "Nu exista forme\n";
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (shapes[i])
		{
			shapes[i]->showDetails();
			std::cout << "\n";
		}
	}
}

void TOTAL(Shape**& shapes, int n, int max)
{
	if (n<1 || n > max)
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
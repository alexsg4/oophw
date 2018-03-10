#include "stdafx.h"
#include "Circle.h"
#include <iostream>


Circle::Circle()
{
}

Circle::Circle(int radius, int height)
{
	setHeight(height);
	setLen1(radius);
}


Circle::~Circle()
{
}

int Circle::getOuterArea() const
{
	int len1 = getLen1();
	return PI*len1*len1;
}

int Circle::getVolume() const
{
	int len1 = getLen1();
	int height = getHeight();
	return PI*len1*len1*height;
}

void Circle::showDetails()
{
	std::cout << "Circle details:\n";
	std::cout << "Height: " << getHeight() << "\n";
	std::cout << "Radius: " << getLen1() << "\n";
}

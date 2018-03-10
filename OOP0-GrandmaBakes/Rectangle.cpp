#include "stdafx.h"
#include "Rectangle.h"
#include <iostream>


Rectangle::Rectangle()
{
}

Rectangle::Rectangle(int length1, int length2, int height)
{
	setLen1(length1);
	len2 = length2;
	setHeight(height);
}

Rectangle::Rectangle(int length, int height)
{
	setLen1(length);
	len2 = length;
	setHeight(height);
}


Rectangle::~Rectangle()
{
}

int Rectangle::getOuterArea() const
{
	int len1 = getLen1();
	return len1*len2;
}

int Rectangle::getVolume() const
{
	int len1 = getLen1();
	int height = getHeight();
	return len1 * len2*height;
}

void Rectangle::showDetails()
{
	int len1 = getLen1();
	int height = getHeight();
	std::cout << "Rectangle details:\n";
	std::cout << "Height: " << height << "\n";
	std::cout << "Length: " << len1 << "\n";
	std::cout << "Width: " << len2 << "\n";
}


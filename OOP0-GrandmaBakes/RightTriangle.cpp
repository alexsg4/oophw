#include "stdafx.h"
#include "RightTriangle.h"
#include <iostream>
#include <math.h>


RightTriangle::RightTriangle()
{
}

RightTriangle::RightTriangle(int length1, int length2, int height)
{
	setLen1(length1);
	len2 = length2;
	setHeight(height);
}


RightTriangle::~RightTriangle()
{
}

int RightTriangle::getOuterArea() const
{
	int height = getHeight();
	//lateral area (lateral faces * base edges * height + base area (1/4 * lateral faces * base edges^2 * cot(PI/lateral faces)
	return (4 * 3 * height) + (3 * 9 * 1 / sqrt(3)) / 4;
}

int RightTriangle::getVolume() const
{
	//base area(1 / 4 * lateral faces * base edges ^ 2 * cot(PI / lateral faces)
	return (3 * 9 * 1 / sqrt(3)) / 4;
}

void RightTriangle::showDetails()
{
	int len1 = getLen1();
	int height = getHeight();
	std::cout << "Right Triangle base details:\n";
	std::cout << "Height: " << height << "\n";
	std::cout << "Leg a: " << len1 << "\n";
	std::cout << "Leg b: " << len2 << "\n";
}

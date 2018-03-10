#include "stdafx.h"
#include "shape.h"
#include <iostream>


Shape::Shape()
{
}

Shape::Shape(int len1, int height)
{
	height = height;
	len1 = len1;
}


Shape::~Shape()
{
}

int Shape::getOuterArea() const
{
	return 0;
}

int Shape::getVolume() const
{
	return 0;
}

void Shape::showDetails()
{
	std::cout << "Shape details:\n";
	std::cout << "Height: " << height << "\n";
	std::cout << "Length: " << len1 << "\n";
}

const char * Shape::getType() const
{
	return &type[0];
}

int Shape::getHeight() const
{
	return height;
}

int Shape::getLen1() const
{
	return len1;
}

void Shape::setHeight(const int h)
{
	height=h;
}

void Shape::setLen1(const int l)
{
	len1 = l;
}

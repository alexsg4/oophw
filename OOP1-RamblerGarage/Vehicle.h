#pragma once
#include <string>
#include "Part.h"
class Vehicle
{
protected:
	unsigned totalParts;
	std::string make;
	std::string model;
	unsigned int year;
	double condition;
	Part** parts;


public:
	Vehicle();
	Vehicle(std::string make, std::string model, unsigned year = 1990);

	~Vehicle();

	const std::string getMake() const;
	const std::string getModel() const;
	const unsigned int getYear() const;
	const double getCondition() const;

	//TODO add Parts specific functions incl. constructor
};


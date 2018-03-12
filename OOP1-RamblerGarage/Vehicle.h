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
	Vehicle(std::string make, std::string model, unsigned year = 1950);

	~Vehicle();

	std::string getMake() const;
	std::string getModel() const;
	unsigned int getYear() const;
	double getCondition() const;

	//TODO add Parts specific functions incl. constructor
};


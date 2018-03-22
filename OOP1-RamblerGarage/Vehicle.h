#pragma once
#include <string>
#include <iostream>
#include "Part.h"
#include <limits>

class Vehicle
{
protected:
	unsigned totalParts = 10;
	unsigned numParts = 0;
	std::string make;
	std::string model;
	unsigned int year = 1950;
	double condition = 100.;
	Part** parts = nullptr;

	//Vehicle types come with a pre-defined number of parts;
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);

public:
	Vehicle();
	Vehicle(std::string make, std::string model, unsigned year, unsigned tParts);

	virtual ~Vehicle();

	std::string getMake() const;
	std::string getModel() const;
	unsigned int getYear() const;
	double getCondition() const;
	void applyRandomDamage(bool verbose = false);
	void showPartsList();
	void applySpecificDamage(bool verbose = false);
	void DBG_showLoadedDefects();
	void diagnose();

	//TODO further testing
	Part& operator[] (const unsigned x)
	{
		if (x < numParts && parts[x])
		{
			return *parts[x];
		}
	}
};

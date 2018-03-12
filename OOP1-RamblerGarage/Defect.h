#pragma once
#include <iostream>
#include <string>

class Defect
{
public: 
	//Implementation assumes a small number of Spare part types
	enum class Spare { SCREW, WIRE, OIL };

private:
	//types of spare parts 
	const unsigned spares = 3;
	std::string name;
	double damage = 1.;
	unsigned manHours = 1.;
	unsigned *cost = nullptr;

public:
	Defect();
	Defect(std::string n, double d, int h, int *&def);

	~Defect();

	unsigned getSpares() const;
	std::string getName() const;
	double getDamage() const;
	unsigned getManHours() const;
	void displaySpareCost();


};


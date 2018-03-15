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
	static const unsigned spares = 3;
	std::string name = "generic defect";
	double damage = 1.;
	double manHours = 1.;
	unsigned *cost = nullptr;

public:
	Defect();
	Defect(std::string n, double d, double h, int *def);

	~Defect();

	unsigned getSpares() const;
	std::string getName() const;
	double getDamage() const;
	unsigned getManHours() const;
	void displaySpareCost();


};


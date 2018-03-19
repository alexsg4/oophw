#pragma once
#include <iostream>
#include <string>

class Defect
{
public: 
	//Implementation assumes a small number of Spare part types
	enum class Spare { SCREW, WIRE, OIL, PAINT, REPLACE };

private:
	//types of spare parts 
	static constexpr unsigned spares = 5;
	std::string name = "generic defect";
	double damage = 1.;
	double manHours = 1.;
	unsigned *cost = nullptr;

public:
	Defect();
	Defect(std::string n, double d, double h, const int *def);

	Defect(std::string n, double d, double h);

	~Defect();

	static unsigned getSpareTypes();
	std::string getName() const;
	double getDamage() const;
	unsigned getManHours() const;
	void displaySpareCost();

	void loadCost(const unsigned* dCost);

	void displayName();


};


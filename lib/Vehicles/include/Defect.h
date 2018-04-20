#pragma once
#include <iostream>
#include <string>

class Defect
{
public: 
	//Implementation assumes a small number of Spare part types
	enum class Spare { SCREW, WIRE, OIL, PAINT, REPLACE, TYPES };

private:
	//types of spare parts 
	std::string name = "generic defect";
	double damage = 1.;
	double manHours = 1.;
	static const unsigned spares = static_cast<unsigned>(Spare::TYPES);
	unsigned cost[spares];

public:
	Defect();
	Defect(std::string n, double d, double h, const int *def);
	Defect(std::string n, double d, double h);

	Defect(const Defect& src);
	Defect& operator=(const Defect& src);
	bool operator==(const Defect& src) const;
	bool operator!=(const Defect& src) const;

	~Defect();

	static unsigned getSpareTypes();
	std::string getName() const;
	double getDamage() const;
	unsigned getManHours() const;
	void showSpareCost(std::ostream& out = std::cout);

	void loadCost(const unsigned* dCost);

	friend std::ostream& operator<<(std::ostream& out, Defect& src);
	friend std::istream& operator>>(std::istream& in, Defect& src);


};


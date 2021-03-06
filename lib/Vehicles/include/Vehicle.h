#pragma once
#include <string>
#include <iostream>
#include <limits>
#include "Part.h"

class Vehicle
{
public:
	//TODO usage
	enum class Stats 
	{ 
		SPD,	// Top speed in km/h
		PWR,	// Engine Power in kW
		TRQ,	// Maximum Torque corresponding in Nm
		RPM,	// Maximum RPM of the engine 
		WHT,	// Weight in kg
		FIN,	// Final drive ratio
		NUM = 4	// Total elements
	};

protected:
	unsigned totalParts = 10;
	unsigned numParts = 0;
	std::string make = "Generic Make";
	std::string model = "Generic Model";
	unsigned int year = 1950;
	double condition = 100.;
	Part** parts = nullptr;
	double* stats = nullptr;

	//Vehicle types come with a pre-defined number of parts;
	virtual void addPart(Part::Type t, Part::Position p = Part::Position::ANY);
	
	//TODO move them inside a separate class
	//Constants
	const double toBHP = 1.34102;	//used for kW to BHP conversion
	const double divPWR = 9549.;	//used for determining engine power
	const double GRAV = 9.8;		//gravitational constant at sea level
	const double dAIR = 1.225;		//air density 


public:
	Vehicle();
	Vehicle(std::string make, std::string model, unsigned year, unsigned tParts);
	Vehicle(const Vehicle& src);
	Vehicle& operator= (const Vehicle& src);
	
	Part& getPart(const unsigned part);
	friend std::istream& operator >>(std::istream& in, Vehicle& src);
	friend std::ostream& operator <<(std::ostream& out, const Vehicle& src);

	virtual ~Vehicle();

	std::string getMake() const;
	std::string getModel() const;
	unsigned int getYear() const;
	double getCondition() const;
	void applyRandomDamage(std::ostream& out = std::cout);
	void showPartsList(std::ostream& out = std::cout);
	void showLoadedDefects(std::ostream& out = std::cout);
	void diagnose(std::ostream& out = std::cout);
	void fix(std::ostream& out = std::cout);
	unsigned getNumParts() const;

	const std::string getNameType() const;

};

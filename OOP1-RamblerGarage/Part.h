#pragma once
#include <string>

class Defect; 

class Part
{
private:
	unsigned maxDefects;
	unsigned numDefects;
	std::string type;
	std::string vehicle;
	std::string mount; //i.e front/rear/left/right
	double condition;
	Defect** defects;


public:
	Part();
	~Part();

	const std::string getType() const;
	const std::string getVehicle() const;
	const std::string getMount() const;
	const double getCondition() const;


};


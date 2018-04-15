#pragma once
#include <iostream>
#include <string>

class Defect;

class Part
{
public:
	enum class Type
	{
		ANY, WHEEL, ENGINE, BRAKE, SUSPENSION, TRANSMISSION, INTERIOR, ECU, BODY, DOOR
	};

	enum class Mount { ANY, CAR, MOTO, BIKE };
	enum class Position { ANY, LEFT, RIGHT, FRONT, REAR, FRONTLT, FRONTRT, REARLT, REARRT };

private:
	//Parts always start in "pristine" condition
	double condition = 100.;
	unsigned numDefects = 0;
	Type type = Type::ANY;
	Mount mount = Mount::ANY;
	Position position = Position::ANY;

	static const unsigned maxDefects = 20;
	static const unsigned mountTypes = 3;
	static const unsigned partTypes = 8;
	const std::string DDIR = "../Assets/defects/";
	
	Defect* dTable[maxDefects];
	bool *defectMarker;

public:
	Part();
	Part(Mount v, Type t,  Position pos);
	Part(const Part& src);
	Part& operator=(const Part& src);
		
	~Part();

	Type getType() const;
	Mount getMount() const;
	Position getPosition() const;
	double getCondition() const;
	unsigned getMaxDefects() const;
	unsigned getNumDefects() const;
	static unsigned getMountTypes();

	//generate file name for defect file
	std::string getDefectsFile();
	
	//assumes file is present for defect loading
	void loadDefectsFromFile(std::string s, std::ostream& out = std::cout);

	std::string generateName() const;

	void diagnose(std::ostream& out = std::cout);

	void applyDamage(unsigned marker, bool verbose=false, std::ostream& out = std::cout);

	void showPossibleDefects(std::ostream& out = std::cout);


};


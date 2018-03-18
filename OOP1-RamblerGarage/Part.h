#pragma once
#include "Defect.h"
#include <string>

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
	static constexpr unsigned maxDefects = 20;
	unsigned numDefects = 0;
	Type type;
	Mount mount;
	Position position;

	static constexpr unsigned vehicleTypes = 3;
	static constexpr unsigned partTypes = 8;
	
	Defect** dTable;
	bool *defectMarker;

public:
	Part();
	Part(Mount v, Type t,  Position pos);
		
	~Part();

	Type getType() const;
	Mount getMount() const;
	Position getPosition() const;
	double getCondition() const;
	unsigned getMaxDefects() const;

	//generate file name for defect file
	std::string & getDefectsFile();
	
	//assumes file is present for defect loading
	void loadDefects(std::string s);

	void displayName();

	void diagnose();

	void applyDamage(unsigned marker);


};


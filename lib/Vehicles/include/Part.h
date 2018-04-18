#pragma once
#include <iostream>
#include <string>
#include "RArray.h"

#define _STR(s) #s
#define STR(s) _STR(s)

//verifies if defects have been loaded from files correctly
extern bool _isLoaded;

class Defect;

class Part
{
public:
	enum class Type
	{
		ANY, WHEEL, ENGINE, BRAKE, SUSPENSION, TRANSMISSION, INTERIOR, ECU, BODY, DOOR, 
		NUM	//Total number of elements. Add others above it. 
	};

	enum class Mount 
	{ 
	ANY, CAR, MOTO, BIKE, 
	NUM	//Total number of elements. Add others above it. 
	};
	
	enum class Position 
	{ 
		ANY, LEFT, RIGHT, FRONT, REAR, FRONTLT, FRONTRT, REARLT, REARRT, 
		NUM	//Total number of elements. Add others above it. 
	};

private:
	//Parts always start in "pristine" condition
	double condition = 100.;
	unsigned numDefects = 0;
	
	Type type;  
	Mount mount;
	Position position;
	
	unsigned tMount = 0;
	unsigned tType = 0;


	static const unsigned mountTypes = static_cast<unsigned>(Mount::NUM);
	static const unsigned posTypes = static_cast<unsigned>(Position::NUM);
	static const unsigned partTypes = static_cast<unsigned>(Type::NUM);
	
	//stores the list of possible defects for each type of part per vehicle type
	static RArray<RArray<Defect>> _dTable;
	
	//return address of _dTable
	inline static RArray<RArray<Defect>> * __dTable()
	{
		return &_dTable;
	}

	//accessor for _dTable
	RArray<RArray<Defect>> * dTable = __dTable();
	
	//marks current defects for this part
	RArray<bool> dMarker;

	//stores the starting index in dTable for each vehicle type
	static unsigned dSection[mountTypes-1];

public:
	Part();
	Part(Mount v, Type t,  Position p);
	Part(const Part& src);
	Part& operator=(const Part& src);
		
	~Part();

	Type getType() const;
	Mount getMount() const;
	Position getPosition() const;


	double getCondition() const;
	unsigned getNumDefects() const;
	static unsigned getPosTypes();

	//generate file name for defect file
	std::string getDefectsFile() const;
	
	//assumes file is present for defect loading
	bool loadDefectsFromFile(std::string s, std::ostream& out = std::cout);

	std::string generateName();

	void diagnose(std::ostream& out = std::cout);

	void applyDamage(unsigned marker, bool verbose=false, std::ostream& out = std::cout);

	void showPossibleDefects(std::ostream& out = std::cout);

	unsigned getPossibleDefectsNum() const;

};
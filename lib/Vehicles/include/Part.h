#pragma once
#include <iostream>
#include <string>
#include "RArray.h"

#define _STR(s) #s
#define STR(s) _STR(s)

class Defect;

class Part
{
public:
	enum class Type
	{
		ANY = -1,	//Used for general initialization
		WHEEL, ENGINE, BRAKE, SUSPENSION, TRANSMISSION, INTERIOR, ECU, BODY, DOOR, 
		NUM	//Total number of elements. Add others above it. 
	};

	enum class Mount 
	{ 
	ANY = -1,	//Used for general initialization
	CAR, MOTO, BIKE, 
	NUM	//Total number of elements. Add others above it. 
	};
	
	enum class Position 
	{ 
		ANY = -1, //Used for general initialization
		LEFT, RIGHT, FRONT, REAR, FRONTLT, FRONTRT, REARLT, REARRT, 
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
	unsigned tIndex = 0;

	static const unsigned mountTypes = static_cast<unsigned>(Mount::NUM);
	static const unsigned posTypes = static_cast<unsigned>(Position::NUM);
	static const unsigned partTypes = static_cast<unsigned>(Type::NUM);
	
	//stores the list of possible defects for each type of part per vehicle type
	static RArray<Defect> _dTable[partTypes*mountTypes];
	static bool _dLoaded[partTypes * mountTypes];
	
	//return address of _dTable
	static inline RArray<Defect>* __dTable()
	{
		return &_dTable[0];
	}

	//return index of current part inside a lookup table
	const inline unsigned _index() const
	{
		return dSection[tMount] + tType;
	}

	//accessor for _dTable
	RArray<Defect> * dTable = __dTable();
	
	//marks current defects for this part
	RArray<bool> dMarker;

	//stores the starting index in dTable for each vehicle type
	static unsigned dSection[mountTypes];

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
	static unsigned getMountTypes();

	//generate file name for defect file
	std::string getDefectsFile() const;
	
	//assumes file is present for defect loading
	bool loadDefectsFromFile(std::string s, std::ostream& out = std::cout);

	std::string generateName() const;

	void diagnose(std::ostream& out = std::cout);

	void applyDamage(unsigned marker, bool verbose=false, std::ostream& out = std::cout);

	void showPossibleDefects(std::ostream& out = std::cout);

	unsigned getPossibleDefectsNum();

};

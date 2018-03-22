#pragma once
#include <string>

#ifdef _WIN32
#define DDIR "defects\\" 
#endif // _WIN32

#ifdef __linux__
#define DDIR "defects/"
#endif // __linux__

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
	static constexpr unsigned maxDefects = 20;
	unsigned numDefects = 0;
	Type type = Type::ANY;
	Mount mount = Mount::ANY;
	Position position = Position::ANY;

	static constexpr unsigned mountTypes = 3;
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
	unsigned getNumDefects() const;
	static unsigned getMountTypes();

	//generate file name for defect file
	std::string getDefectsFile();
	
	//assumes file is present for defect loading
	void loadDefectsFromFile(std::string s);

	std::string generateName() const;

	void diagnose();

	void applyDamage(unsigned marker, bool verbose=false);

	void showPossibleDefects();


};


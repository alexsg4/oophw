#pragma once

class Part
{
public:
	//TODO remove string-referencing
	enum class Type
	{
		WHEEL, CHASSIS, ENGINE, BRAKE, SUSPENSION, TRANSMISSION, INTERIOR, ECU, ANY
	};

	enum class Mount { CAR, MOTO, BIKE, ANY };
	enum class Position { LEFT, RIGHT, FRONT, REAR, FRONTLT, FRONTRT, REARLT, REARRT, ANY };

private:
	//Parts always start in "pristine" condition
	double condition = 100.;
	static const unsigned maxDefects = 20;
	unsigned numDefects = 0;
	Type type;
	Mount mount;
	Position position;

	static const unsigned vehicleTypes = 3;
	static const unsigned partTypes = 8;
	
	static Defect* defects[vehicleTypes][partTypes][maxDefects];
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
	
	void loadDefects();
	void loadDefects(std::string s);


};


#pragma once

class Defect; 

class Part
{
public:
	//Might need renaming
	enum class Type
	{
		WHEEL, ENGINE, SUSPENSION, TRANSMISSION, CHASSIS, INTERIOR, BRAKE, ECU,
		SCREW, WIRE, OIL, PLATE
	
	};

	enum class Vehicle { ANY, CAR, BIKE, MOTO };
	enum class Position { ANY, LEFT, RIGHT, FRONT, REAR, FRONTLT, FRONTRT, REARLT, REARRT };


private:
	//Parts always start in "pristine" condition
	double condition = 100.;
	const unsigned maxDefects = 20;
	unsigned numDefects = 0;
	Type type;
	Vehicle vehicle;
	Position position;
	Defect** defects;

public:
	Part();
	Part(Type t, Vehicle v, Position pos);
		
	~Part();

	Type getType() const;
	Vehicle getVehicle() const;
	Position getMount() const;
	double getCondition() const;


};


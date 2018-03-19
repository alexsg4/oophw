// OOP1-RamblerGarage.cpp : Defines the entry point for the console application.


#ifdef _WIN32

#define CLEAR system("cls");
#define DV \

#endif // _WIN32

#ifdef linux

#define CLEAR system("clear");
#define DV /

#endif // linux

#include "stdafx.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"
#include "Defect.h"
#include <cstdlib>
#include <cstdalign>


int main()
{
	static constexpr unsigned fleetCapacity = 20;
	static constexpr unsigned fleetSize = 0;
	Vehicle** fleet = new Vehicle*[fleetCapacity];


	//testing
	Car* c1 = new Car("dacia", "logan", 2003);
	Bike* b1 = new Bike("Pegas", "p1", 1965);
	Motorbike* m1 = new Motorbike("Yamaha", "YZR-M1", 2017);


	delete c1;
	delete b1;
	delete m1;

	//TODO implement vehicle deletion/addition
	//TODO apply specific defects to a vehicle/fix a vehicle
	//TODO add menu 

    return 0;
}


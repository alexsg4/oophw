// OOP1-RamblerGarage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Car.h"
#include "Bike.h"
#include "Motorbike.h"
#include "Defect.h"


int main()
{
	
	//testing
	Car* c1 = new Car("dacia", "logan", 2003);
	Bike* b1 = new Bike("Pegas", "p1", 1965);
	Motorbike* m1 = new Motorbike("Yamaha", "YZR-M1", 2017);

	delete c1;
	delete b1;
	delete m1;

    return 0;
}


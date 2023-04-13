#include <iostream>
#include "Driver.h"

using namespace std;

Driver::Driver(Car& a,double initialBudget) :
cab(a), budget(initialBudget) {}

void Driver::drive(int drivenDistance)
{
	cab.driven(drivenDistance);
}

void Driver::repairCar(string accidentLevel)
{
	int reduction;
	double rate;

	if (accidentLevel == "SMALL")
	{
		reduction = 50;
		rate = 1.05;
	}
	else if (accidentLevel == "MEDIUM")
	{
		reduction = 150;
		rate = 1.1;
	}
	else if (accidentLevel == "LARGE")
	{
		reduction = 300;
		rate = 1.2;
	}

	budget -= reduction;
	cout << reduction <<  " is reduced from the driver's budget because of the " << accidentLevel << " accident" << endl;
	cab.repair(rate,accidentLevel);
	
}

void Driver::display()
{
	cout << "Driver budget: " << budget << endl;
}

void Driver::fullFuel()
{
	budget -= cab.fullFuel();
}

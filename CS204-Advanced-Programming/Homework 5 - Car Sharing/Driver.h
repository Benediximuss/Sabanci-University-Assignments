#ifndef _DRIVER_H
#define _DRIVER_H

#include <iostream>
#include <string>
#include "Car.h"
using namespace std;

class Driver
{
public:
	Driver(Car&,double);

	void drive(int);
	void repairCar(string);
	void display();
	void fullFuel();
private:
	Car& cab;
	double budget;
};

#endif
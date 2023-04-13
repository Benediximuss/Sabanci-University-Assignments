#include <iostream>
#include "Car.h"

using namespace std;

Car::Car(double intialFuel, double insuranceFee, int totalDistance)
{
	fuel = intialFuel;
	fuelMax = intialFuel;
	insurFee = insuranceFee;
	totDistance = totalDistance;
}

void Car::driven(int drivenDistance)
{
	totDistance += drivenDistance;
	fuel -= (0.25)*drivenDistance;
}

void Car::repair(double percentage, string level)
{
	insurFee *= percentage;
	cout << "Yearly insurance fee is increased to " << insurFee << " because of the " << level << " accident" << endl;
}

double Car::fullFuel() // RETURNS THE COST FOR FULLING THE FUEL
{
	double needed = (fuelMax - fuel);
	fuel = fuelMax;
	cout << "Fuel is full" << endl;
	return needed;
}

void Car::display()
{
	cout << "Fuel Level: " << fuel << endl;
	cout << "Insurance Fee: " << insurFee << endl;
	cout << "Total distance that the car has travelled: " << totDistance << endl;
}
#ifndef _CAR_H
#define _CAR_H

#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
	Car(double,double,int);

	void driven(int);
	void repair(double,string);
	double fullFuel();
	void display();
private:
	double fuel; // also max fuel
	double fuelMax;
	double insurFee;
	int totDistance;
};

#endif
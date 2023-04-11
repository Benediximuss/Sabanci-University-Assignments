#include <iostream>
#include <vector>
#include <string>
#include "date.h"

class Sailor
{
	public:
		Sailor()
		{
			id = 0;
			name = "Jane Doe";
			age = 0;
			rank = 0;
		}

	private:
		int id;
		string name;
		double age;
		double rank;
};

class Boat
{
	public:
		Boat()
		{
			id = 0;
			name = "Default";
			color = "Default";
		}

	private:
		int id;
		string name;  
		string color;
};

class Reservation
{
	public:
		Reservation()
		{
			Sailor s;
			sailor = s;
			Boat b;
			boat = b;
			Date d(1,1,1900);
			resDate = d;
		}

		// Add here the Print function

	private:
		Date resDate;
		Sailor sailor;
		Boat boat;
};

class Reservations
{
	public:
		// Fill this part with the member functions
		// 1. Add a Reservation

		// 2. Delete a Reservation

		// 3.1. Find a Reservation (sailor and boat ids are 0)
		// 3.2. Find a Reservation (only sailor id is 0)
		// 3.3. Find a Reservation (only boat id is 0)

	private:
		vector<Reservation> reservations;
	
};




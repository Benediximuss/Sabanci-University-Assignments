#include <iostream>
#include <vector>
#include <string>
#include "date.h"

class Sailor
{
	public:
		Sailor()
		{
			id = 999;
			name = "DEFAULT";
			age = 0;
			rank = 0;
		}

		Sailor(int a, string b, double c, double d)
		{
			id = a;
			name = b;
			age = c;
			rank = d;
		}

		int getSID()
		{
			return id;
		}

		string getSailorName()
		{
			return name;
		}

		double getAge()
		{
			return age;
		}

		double getRank()
		{
			return rank;
		}

		void updateSID(int a)
		{
			id = a;
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
			id = 999;
			name = "DEFAULT";
			color = "DEFAULT";
		}

		Boat(int a, string b, string c)
		{
			id = a;
			name = b;
			color = c;
		}

		int getBID()
		{
			return id;
		}

		string getBoatName()
		{
			return name;
		}

		string getColor()
		{
			return color;
		}

		void updateBID(int a)
		{
			id = a;
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

		Reservation(Date a, Sailor b, Boat c)
		{
			resDate = a;
			sailor = b;
			boat = c;
		}

		Date getDate()
		{
			return resDate;
		}

		Sailor getSailorInfo()
		{
			return sailor;
		}

		Boat getBoatInfo()
		{
			return boat;
		}

		void printReservation()
		{
			cout << resDate << " -> " << sailor.getSailorName() << "(" << sailor.getRank() << "," << sailor.getAge() << ") has reserved " << boat.getBoatName() << "(" << boat.getColor() << ")" << endl; 
		}

	private:
		Date resDate;
		Sailor sailor;
		Boat boat;
};

class Reservations
{
	public:

		void addRes(Reservation a)
		{
			reservations.push_back(a);
		}

		void delRes(Reservation a, string b)
		{
			if (a.getSailorInfo().getSID() == 0) {

				int len = reservations.size();
				int target;
				int delTimes = 0;

				for (int i = 0; i < len; i++) {
					if (reservations[i].getBoatInfo().getBID() == a.getBoatInfo().getBID()) {
						delTimes++;
					}
				}

				int k = 0;
				while (k != delTimes) {
					len = reservations.size();
					int last_idx = len - 1;
					for (int i = 0; i < len; i++){
						if (reservations[i].getBoatInfo().getBID() == a.getBoatInfo().getBID()) {
							target = i;
							reservations[target] = reservations[last_idx];
							reservations.pop_back();
							break;
						}
					}
					k++;
				}

				if (delTimes == 0) {
					cout << "Error: Could not delete reservation for boat id " << a.getBoatInfo().getBID() << endl << endl;
				}		
			
			}
			
			else if (a.getBoatInfo().getBID() == 0) {

				int len = reservations.size();
				int target;
				int delTimes = 0;

				for (int i = 0; i < len; i++) {
					if (reservations[i].getSailorInfo().getSID() == a.getSailorInfo().getSID()) {
						delTimes++;
					}
				}

				int k = 0;
				while (k != delTimes) {
					len = reservations.size();
					int last_idx = len - 1;
					for (int i = 0; i < len; i++){
						if (reservations[i].getSailorInfo().getSID() == a.getSailorInfo().getSID()) {
							target = i;
							reservations[target] = reservations[last_idx];
							reservations.pop_back();
							break;
						}
					}
					k++;
				}

				if (delTimes == 0) {
					cout << "Error: Could not delete reservation for sailor id " << a.getSailorInfo().getSID() << endl << endl;
				}						
		
			}

			else if (a.getSailorInfo().getSID() != 0 && a.getBoatInfo().getBID() != 0) {

				int len = reservations.size();
				int target;
				bool check = false;

				for (int i = 0; i < len; i++ ) {
					if (reservations[i].getSailorInfo().getSID() == a.getSailorInfo().getSID() && reservations[i].getBoatInfo().getBID() == a.getBoatInfo().getBID() && reservations[i].getDate() == a.getDate()) {
						target = i;
						check = true;
						break;
					}
				}

				if (check == true) {
					int last_idx = len - 1;
					reservations[target] = reservations[last_idx];
					reservations.pop_back();
				}

				else {
					cout << "Error: Could not delete reservation " << "\"" << a.getSailorInfo().getSID() << " " << a.getBoatInfo().getBID() << " " << b << "\"" << endl << endl;
				}

			}
			


		}

		void findRes_A(Reservation a, string b)
		{
			vector <Reservation> vectemp;
			int initsize = vectemp.size();
			cout << "Find Results:" << endl;

			if (a.getSailorInfo().getSID() == 0) {
				for (int i = 0; i < reservations.size(); i++){
					if (reservations[i].getBoatInfo().getBID() == a.getBoatInfo().getBID() && reservations[i].getDate() == a.getDate()) {
						vectemp.push_back(reservations[i]);
					}
				}

				if (vectemp.size() == initsize) { cout << "Error: No matching reservation found for boat id " << a.getBoatInfo().getBID() << " on " << b << endl << endl; }
				else {
					for (int i = 0; i < vectemp.size(); i++){
						vectemp[i].printReservation();
					}
					cout << endl;
				}

			}

			else if (a.getBoatInfo().getBID() == 0) {
				for (int i = 0; i < reservations.size(); i++){
					if (reservations[i].getSailorInfo().getSID() == a.getSailorInfo().getSID() && reservations[i].getDate() == a.getDate()) {
						vectemp.push_back(reservations[i]);
					}
				}

				if (vectemp.size() == initsize) { cout << "Error: No matching reservation found for sailor id " << a.getSailorInfo().getSID() << " on " << b << endl << endl; }
				else {
					for (int i = 0; i < vectemp.size(); i++){
						vectemp[i].printReservation();
					}
					cout << endl;
				}
			}

		}

		void findRes_B(Date a, Date b, string c, string d)
		{

			vector <Reservation> vectemp;
			int initsize = vectemp.size();
			cout << "Find Results:" << endl;

			for (int i = 0; i < reservations.size(); i++){
				if(reservations[i].getDate() >= a && reservations[i].getDate() <= b) {
					vectemp.push_back(reservations[i]);
				}
			}

			if (vectemp.size() == initsize) { cout << "Error: No matching reservation found between dates " << c << " & " << d << endl << endl; }
			else {
				for (int i = 0; i < vectemp.size(); i++){
					vectemp[i].printReservation();
				}
				cout << endl;
			}

		}

		void sortAll()
		{ 
			int min,lenres = reservations.size();
			Reservation temp;

			for (int i = 0; i < lenres-1; i++) {

			min = i;

			for (int k = i + 1; k < lenres; k++) {

				if (reservations[k].getDate() < reservations[min].getDate()) { min = k; }
				else if (reservations[k].getDate() == reservations[min].getDate()) {
					if (reservations[k].getSailorInfo().getSailorName() < reservations[min].getSailorInfo().getSailorName()) { min = k; }
				}
				
			}
						  
			temp = reservations[i];         
			reservations[i] = reservations[min];
			reservations[min] = temp;

			}
			
		}

	private:
		vector<Reservation> reservations;
	
};




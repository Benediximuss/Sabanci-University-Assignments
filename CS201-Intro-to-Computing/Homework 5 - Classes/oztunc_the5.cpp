#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Reservation.h"

using namespace std;

int main() {

	ifstream in_Res, in_Sailor, in_Boat;
	string fname_Res, fname_Sailor = "Sailors.txt", fname_Boat = "Boats.txt";

	vector<Sailor> sailorList;
	vector<Boat> boatList;
	vector<Reservation> resList;

	string line; int k = 0;

	cout << "Enter filename for reservation database: "; cin >> fname_Res;

	in_Sailor.open(fname_Sailor.c_str());
	if (in_Sailor.fail()) { cout << "Cannot open the files. Exiting..." << endl << endl; }
	else {
		while (getline(in_Sailor,line)) {
			if (k == 0) { k++; }
			else {
				int SID_temp; string SailorName_temp; double rating, age;
				istringstream ss(line);
				ss >> SID_temp >> SailorName_temp >> rating >> age;
				Sailor Sailor_temp(SID_temp, SailorName_temp, rating, age);
				sailorList.push_back(Sailor_temp);
			}
		}
		in_Sailor.close();

		in_Boat.open(fname_Boat.c_str());
		if (in_Boat.fail()) { cout << "Cannot open the files. Exiting..." << endl << endl; }
		else {
			k = 0;
			while (getline(in_Boat,line)) {
				if (k == 0) { k++; }
				else{
					int BID_temp; string BoatName_temp, color_temp;
					istringstream ss(line);
					ss >> BID_temp >> BoatName_temp >> color_temp;
					Boat Boat_temp(BID_temp,BoatName_temp,color_temp);
					boatList.push_back(Boat_temp);
				}
			}
			in_Boat.close();

			in_Res.open(fname_Res.c_str());
			if (in_Res.fail()) { cout << "Cannot open the files. Exiting..." << endl << endl; }
			else {
				Reservations All_Reservations;
				while(getline(in_Res,line)) {
					string function_temp; int SID_temp, BID_temp; string date_temp, date2_temp = "extra", date_as_string, date_as_string2;
					istringstream ss(line);
					ss >> function_temp >> SID_temp >> BID_temp >> date_temp >> date2_temp;
					date_as_string = date_temp;
					date_as_string2 = date2_temp;
					date_temp[4] = ' '; date_temp[7] = ' ';
					int year_temp, month_temp, day_temp;
					istringstream ss2(date_temp);
					ss2 >> year_temp >> month_temp >> day_temp;

					Date date_temp2(month_temp,day_temp,year_temp);

					Sailor sailor_temp; Boat boat_temp;

					for (int i = 0; i < sailorList.size(); i++) {
						if (sailorList[i].getSID() == SID_temp) { sailor_temp = sailorList[i]; break; }
					}

					for (int i = 0; i < boatList.size(); i++) {
						if (boatList[i].getBID() == BID_temp) { boat_temp = boatList[i]; break; }
					}

					if (sailor_temp.getSID() == 999)
					{
						sailor_temp.updateSID(SID_temp);
					}

					if (boat_temp.getBID() == 999)
					{
						boat_temp.updateBID(BID_temp);
					}


					Reservation Res_temp(date_temp2, sailor_temp, boat_temp);
					

					if (function_temp == "A") { All_Reservations.addRes(Res_temp); All_Reservations.sortAll(); }
					else if (function_temp == "D") { All_Reservations.delRes(Res_temp,date_as_string); All_Reservations.sortAll(); }
					else if (function_temp == "F") {
						if (date2_temp == "extra") { All_Reservations.findRes_A(Res_temp,date_as_string); }
						else {
							date2_temp[4] = ' '; date2_temp[7] = ' ';
							int year_temp, month_temp, day_temp;
							istringstream ss2(date2_temp);
							ss2 >> year_temp >> month_temp >> day_temp;
							Date date2_temp2(month_temp,day_temp,year_temp);

							All_Reservations.findRes_B(date_temp2,date2_temp2,date_as_string,date_as_string2);
						
						}
					}

					

				}
				in_Res.close();

			}
		}
	}

	return 0;
}
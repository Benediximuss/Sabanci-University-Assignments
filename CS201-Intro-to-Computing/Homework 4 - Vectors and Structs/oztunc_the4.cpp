#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct boat {
	int id;
	string name,color;
};

struct sailor {
	int id;
	double rate,age;
	string name;
};

struct reservation {
	int sid,bid;
	string date;
	int year,month,day;
};

void error_out() {
	cout << "Cannot open the files. Exiting..." << endl;
}

int compareDate(reservation x, reservation y) {

	if (x.year < y.year) { return 1; }
	else if (x.year > y.year) { return 2; }
	else if (x.year == y.year) {
		if (x.month < y.month) { return 1; }
		else if (x.month > y.month) { return 2; }
		else if (x.month == y.month) {
			if (x.day < y.day) { return 1; }
			else if (x.day > y.day) { return 2; }
			else if (x.day == y.day) { return 0; }
		}
	}

	return 0;

}

int main() {

	string res_file,sailor_file = "Sailors.txt",boat_file = "Boats.txt";
	ifstream res_input,sailor_input,boat_input;

	vector<reservation> resList;
	vector<boat> boatList;
	vector<sailor> sailorList;

	string line,word;
	int lineCount;

	reservation res_temp; string date_temp;
	boat boat_temp;
	sailor sailor_temp;

	cout << "Enter filename for reservation database: "; cin >> res_file;

	res_input.open(res_file.c_str());
	if (res_input.fail()) { error_out(); }
	else {

		lineCount = 1;
		while (getline(res_input,line)) {
			if (lineCount > 1) { 

			istringstream s1(line);
			s1 >> res_temp.sid >> res_temp.bid >> date_temp;

			res_temp.date = date_temp;

			date_temp[4] = ' ';
			date_temp[7] = ' ';

			istringstream s1b(date_temp);

			s1b >> res_temp.year >> res_temp.month >> res_temp.day;
			
			
			resList.push_back(res_temp);

			}
			lineCount ++;
		}

		res_input.close();

		boat_input.open(boat_file.c_str());
		if (boat_input.fail()) { error_out(); }
		else {

			lineCount = 1;
			while (getline(boat_input,line)) {
				if (lineCount > 1) {

					istringstream s2(line);
					s2 >> boat_temp.id >> boat_temp.name >> boat_temp.color;

					boatList.push_back(boat_temp);

				}
				lineCount ++;
			}

			boat_input.close();
			
			sailor_input.open(sailor_file.c_str());
			if (sailor_input.fail()) { error_out(); }
			else {

				lineCount = 1;
				while (getline(sailor_input,line)) {
					if (lineCount > 1) {

						istringstream s3(line);
						s3 >> sailor_temp.id >> sailor_temp.name >> sailor_temp.rate >> sailor_temp.age;

						sailorList.push_back(sailor_temp);

					}
					lineCount ++;
				}

				sailor_input.close();
				




				int min,sid1,sid2; string name1,name2;
		reservation temp;

		for (int i = 0; i < resList.size()-1; i++) {

		min = i;

		for (int k = i + 1; k < resList.size(); k++) {

			if (compareDate(resList[k],resList[min]) == 1) { min = k; }
			else if (compareDate(resList[k],resList[min]) == 0) {
		
				sid1 = resList[k].sid;
				sid2 = resList[min].sid;

				for (int l = 0; l < sailorList.size(); l++) {
					if (sailorList[l].id == sid1) { name1 = sailorList[l].name; }
					else if (sailorList[l].id == sid2) { name2 = sailorList[l].name; }
				}

				if (name1 < name2) { min = k;}
			
			} 
		}
						  
		temp = resList[i];         
		resList[i] = resList[min];
		resList[min] = temp;

	}
		reservation res;
		string temp_date, temp_boatname, temp_color, temp_sailorname; int temp_sid, temp_bid; double temp_rate, temp_age;

		for (int i = 0; i < resList.size(); i++) {
			
			res = resList[i];
			temp_date = res.date;
			temp_bid = res.bid;
			temp_sid = res.sid;

			for (int k = 0; k < sailorList.size(); k++) { if(sailorList[k].id == temp_sid) {
					temp_age = sailorList[k].age;
					temp_sailorname = sailorList[k].name;
					temp_rate =	sailorList[k].rate;
				} 
			}

			for (int k = 0; k < boatList.size(); k++) { if(boatList[k].id == temp_bid) {
				temp_color = boatList[k].color;
				temp_boatname = boatList[k].name;
				}
			}

			cout << temp_date << " -> " << temp_sailorname << "(" << temp_age << "," << temp_rate << ") has reserved " << temp_boatname << "(" << temp_color << ")" << endl;

			
		}

			}
		}
	}


	return 0;
}

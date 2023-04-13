#include<iostream>
#include<string>
#include"Car.h"
#include"Driver.h"
using namespace std;

int main()
{
	int km;
	string answer, accidentType;
	string loop = "YES";
	Car sharedCar(300, 1000, 5000); // sharedCar initially have fuel corresponds to 300$ which is the max fuel that the car can have, 
	//insurance fee is 1000$ for year 
	//and the total distance that the car has travelled is 5000km.

	Driver driver1(sharedCar, 1000);
	Driver driver2(sharedCar, 1000); // driver1 and driver2 shares the sharedCar and initial budget of each driver is 1000$

	while(loop == "YES")
	{
		cout << "How many km driver1 drives?"<<endl;
		cin >> km;
		cout << endl;
	
		driver1.drive(km);

		cout << "Did the driver1 have an accident YES / NO" <<endl;
		cin >> answer;
		cout << endl;

		if(answer == "YES")
		{
			cout << "What is the type of the accident SMALL / MEDIUM / LARGE" << endl;
			cin >> accidentType;
			cout << endl;
			driver1.repairCar(accidentType);
		}

		cout<<endl;
		sharedCar.display();

		driver1.fullFuel(); // Full fuel before giving the car to driver2

		driver1.display();
		
		cout<<endl<<endl;
		cout << "How many km driver2 drives?"<<endl;
		cin >> km;
		cout << endl;

		driver2.drive(km);

		cout << "Did the driver2 have an accident YES / NO" <<endl;
		cin >> answer;
		cout << endl;

		if(answer == "YES")
		{
			cout << "What is the type of the accident SMALL / MEDIUM / LARGE" << endl;
			cin >> accidentType;
			cout << endl;
			driver2.repairCar(accidentType);
		}

		cout<<endl;
		sharedCar.display();

		driver2.fullFuel(); // Full fuel before giving the car to driver1

		driver2.display();

		cout<<endl;
		cout <<"Do you want to continue: YES / NO"<<endl;
		cin >> loop;
		cout<<endl;
	}

	return 0;
}
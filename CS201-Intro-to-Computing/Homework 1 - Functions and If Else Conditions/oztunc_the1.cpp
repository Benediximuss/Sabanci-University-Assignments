#include <iostream>
#include <string>

using namespace std;


void getInput(string &prompt, double &mins, int &reps, double &weight) {
	if (weight == 12) { cout << prompt; cin >> mins >> reps; }
	else { cout << prompt; cin >> mins >> reps >> weight; }
}

bool inputCheck(double weight2, double lungesMins2, int lungesReps2, double pushupsMins2, int pushupsReps2, double pullupsMins2, int pullupsReps2, double liftMins2, int liftReps2, double liftWeight2)
{
	if (weight2 < 30) { cout << "Weight out of range!" << endl; return false; }
	 else { if (lungesReps2 < 0 || lungesReps2 > 50) { cout << "Reps out of range!" << endl; return false; }
			 else { if (lungesMins2 < 0 || lungesMins2 > 2000) { cout << "Minute out of range!" << endl; return false; }
					 else { if (pushupsReps2 < 0 || pushupsReps2 > 50) { cout << "Reps out of range!" << endl; return false; }
							 else { if (pushupsMins2 < 0 || pushupsMins2 > 2000) { cout << "Minute out of range!" << endl; return false; }
									 else { if (pullupsReps2 < 0 || pullupsReps2 > 50) { cout << "Reps out of range!" << endl; return false; }
											 else { if (pullupsMins2 < 0 || pullupsMins2 > 2000) { cout << "Minute out of range!" << endl; return false; }
											         else { if (liftWeight2 <= 0 || liftWeight2 > 35) { cout << "Lifted weight out of range!" << endl; return false; }
															 else { if (liftReps2 < 0 || liftReps2 > 50) { cout << "Reps out of range!" << endl; return false; }
																	 else { if (liftMins2 < 0 || liftMins2 > 2000) { cout << "Minute out of range!" << endl; return false; }
																	         else { return true; }	}}}}}}}}}			}

void calculateMET(int lungesReps2, double &lungesMET2, int pushupsReps2, double &pushupsMET2, int pullupsReps2, double &pullupsMET2) {
	if (lungesReps2 < 15) { lungesMET2 = 3; } else if (lungesReps2 >= 15 && lungesReps2 < 30) { lungesMET2 = 6.5; } else { lungesMET2 = 10.5; }
	if (pushupsReps2 < 15) { pushupsMET2 = 4; } else { pushupsMET2 = 7.5; }
	if (pullupsReps2 < 25) { pullupsMET2 = 5; } else { pullupsMET2 = 9; }
}

void calculateWeightLiftMET(int liftReps2, double liftWeight2, double &liftMET2) 
{
	if (liftWeight2 < 5 && liftReps2 < 20)														 { liftMET2 = 3; }
	else if (liftWeight2 < 5 && liftReps2 >= 20 && liftReps2 < 40)								 { liftMET2 = 5.5;}
	else if (liftWeight2 < 5 && liftReps2 >= 40)												 { liftMET2 = 10; }	
	else if (liftWeight2 >= 5 && liftWeight2 < 15 && liftReps2 < 20)							 { liftMET2 = 4; }	
	else if (liftWeight2 >= 5 && liftWeight2 < 15 && liftReps2 >= 20 && liftReps2 < 40)			 { liftMET2 = 7.5; }	
	else if (liftWeight2 >= 5 && liftWeight2 < 15 && liftReps2 >= 40)							 { liftMET2 = 12; }
	else if (liftWeight2 >= 15 && liftReps2 < 20)												 { liftMET2 = 5; }
	else if (liftWeight2 >= 15 && liftReps2 >= 20 && liftReps2 < 40)							 { liftMET2 = 9; }
	else if (liftWeight2 >= 15 && liftReps2 >= 40)												 { liftMET2 = 13.5; }
}

void displayResults(double lungesCals2, double lungesMins2, double lungesMET2, double pushupsCals2, double pushupsMins2, double pushupsMET2, double pullupsCals2, double pullupsMins2, double pullupsMET2, double liftCals2, double liftMins2, double liftMET2, double weight2, double calsGoal2, double calsBurnt2, double calsDiff2)
{
	cout << "From lunges, you burned " << lungesCals2 << " calories." << endl;
	cout << "From push ups, you burned " << pushupsCals2 << " calories." << endl;
	cout << "From pull ups, you burned " << pullupsCals2 << " calories." << endl;
	cout << "From weight lifting, you burned " << liftCals2 << " calories." << endl;
	cout << "You burned " << calsBurnt2 << " calories." << endl << endl;

	if (calsBurnt2 == calsGoal2) {cout << "Congratulations! You have reached your goal!" << endl;}
	else if (calsBurnt2 > calsGoal2) {cout << "You have surpassed your goal! You can eat something worth " << (-1)*calsDiff2 << " calories :)" << endl;}
	else if (calsBurnt2 < calsGoal2) {
		cout << "You did not reach your goal by " << calsDiff2 << " calories." << endl;
		cout << "You need to do lunges " << calsDiff2*(200)/(lungesMET2*3.5*weight2) << " minutes more to reach your goal or," << endl;
		cout << "You need to do push ups " << calsDiff2*(200)/(pushupsMET2*3.5*weight2)  << " minutes more to reach your goal or," << endl;
		cout << "You need to do pull ups " << calsDiff2*(200)/(pullupsMET2*3.5*weight2)  << " minutes more to reach your goal or," << endl;
		cout << "You need to do weight lifting " << calsDiff2*(200)/(liftMET2*3.5*weight2)  << " minutes more to reach your goal." << endl;
	}
}

void computeResults(double weight2, double calsGoal2, double lungesMins2, int lungesReps2, double pushupsMins2, int pushupsReps2, double pullupsMins2, int pullupsReps2, double liftMins2, int liftReps2, double liftWeight2)
{
	double lungesMETtemp, pushupsMETtemp, pullupsMETtemp, liftMETtemp;
	calculateMET(lungesReps2, lungesMETtemp, pushupsReps2, pushupsMETtemp, pullupsReps2, pullupsMETtemp);
	calculateWeightLiftMET(liftReps2, liftWeight2, liftMETtemp); 

	double lungesCalstemp = (lungesMins2*lungesMETtemp*weight2*3.5/200), pushupsCalstemp = (pushupsMins2*pushupsMETtemp*weight2*3.5/200), pullupsCalstemp = (pullupsMins2*pullupsMETtemp*weight2*3.5/200), liftCalstemp = (liftMins2*liftMETtemp*weight2*3.5/200);

	double calsBurnttemp = lungesCalstemp + pushupsCalstemp + pullupsCalstemp + liftCalstemp, calsDifftemp = calsGoal2 - calsBurnttemp;

	displayResults(lungesCalstemp, lungesMins2, lungesMETtemp, pushupsCalstemp, pushupsMins2, pushupsMETtemp, pullupsCalstemp, pullupsMins2, pullupsMETtemp, liftCalstemp, liftMins2, liftMETtemp, weight2, calsGoal2, calsBurnttemp, calsDifftemp);
}

int main() {

	cout << "Please enter your name: "; string name; cin >> name;
	cout << "Welcome " << name << ", please enter your weight(kg): "; double weight; cin >> weight;

	cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl; 

	string lungesPrompt = "Lunges: "; double lungesMins; int lungesReps;
	string pushupsPrompt = "Push Ups: "; double pushupsMins; int pushupsReps;
	string pullupsPrompt = "Pull Ups: "; double pullupsMins; int pullupsReps;
	string liftPrompt = "Weight Lifting: "; double liftMins; int liftReps; double liftWeight = 12;

	getInput(lungesPrompt, lungesMins, lungesReps, liftWeight);
	getInput(pushupsPrompt, pushupsMins, pushupsReps, liftWeight);
	getInput(pullupsPrompt, pullupsMins, pullupsReps, liftWeight);

	liftWeight = 1;

	cout << name << ", please enter minutes, repetitions and lifted weight in a week for the activities below." << endl;

	getInput(liftPrompt, liftMins, liftReps, liftWeight);

	cout << name << ", please enter your weekly calorie burn goal: "; double calsGoal; cin >> calsGoal;

	if (inputCheck(weight, lungesMins, lungesReps, pushupsMins, pushupsReps, pullupsMins, pullupsReps, liftMins, liftReps, liftWeight) == true) {
		computeResults(weight, calsGoal, lungesMins, lungesReps, pushupsMins, pushupsReps, pullupsMins, pullupsReps, liftMins, liftReps, liftWeight);
	}
	return 0;
}
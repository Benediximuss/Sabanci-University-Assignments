#include <iostream>
#include <string>

using namespace std;

int main() {
	
	string name;
	double midterm_grade, final_grade;
	
	cout << "The purpose of this program is to calculate your CS201 grade."<< endl;
	cout << "What is your name? ";
	cin >> name;

	cout << "Hello " << name << ", what are your midterm and final exam grades? ";
	cin >> midterm_grade >> final_grade;
	if (midterm_grade == -100 || final_grade == -100) {
		cout << name << ", one of your midterm or final exam grade is -100, you will fail the course!" << endl;
	}
	else {
		if (midterm_grade == -1) {
			cout << name << ", you did not enter the midterm exam, you will fail the course!" << endl;
		}
		else if (final_grade == -1) {
			cout << name << ", you did not enter the final exam, you will fail the course!" << endl;
		}
		else {
			double exam_avr;
			exam_avr = (0.30 * midterm_grade + 0.30 * final_grade) / 0.6;
				if (exam_avr < 30) {
					cout << name << ", your weighted exam average is less than 30, you will fail the course!" << endl;
				}
				else {
					double the1,the2,the3,the4,the5;
					int the_plag;
					the_plag = 0;

					cout << "What are the grades of your 5 take-home exams? ";
					cin >> the1 >> the2 >> the3 >> the4 >> the5;

					if (the1 == -100) {
						the_plag += 1;
					}
					if (the2 == -100) {
						the_plag += 1;
					}
					if (the3 == -100) {
						the_plag += 1;
					}
					if (the4 == -100) {
						the_plag += 1;
					}
					if (the5 == -100) {
						the_plag += 1;
					}
					
					if (the_plag >= 2) {
						cout << name << ", at least two of your THE grades are -100, you will fail the course!" << endl;
					}
					else {
						double the_avr, the_grade;
						the_avr = (the1*0.03+the2*0.04+the3*0.04+the4*0.04+the5*0.05) / 0.20;

						if (the_avr < 0) {
							the_grade = the_avr;
						}
						else {
							double the_ratio;
							the_ratio = the_avr/exam_avr;
							if (the_ratio <= 2) {
								the_grade = the_avr;
							}
							else if (2 < the_ratio && the_ratio < 3) {
								the_grade = the_avr * (3-the_ratio);
							}
							else if (the_ratio >= 3) {
								the_grade = 0;
							}
						}

						double quiz1,quiz2,quiz3,quiz4;
						int quiz_plag;
						quiz_plag = 0;

						cout << "What are the grades of your 4 quizzes? ";
						cin >> quiz1 >> quiz2 >> quiz3 >> quiz4;

						if (quiz1 == -100) {
							quiz_plag += 1;
						}
						if (quiz2 == -100) {
							quiz_plag += 1;
						}
						if (quiz3 == -100) {
							quiz_plag += 1;
						}
						if (quiz4 == -100) {
							quiz_plag += 1;
						}

						if (quiz_plag >= 2) {
							cout << name << ", at least two of your quiz grades are -100, you will fail the course!" << endl;
						}
						else if ( (quiz_plag + the_plag) == 2) {
							cout << name << ", one of your THE and one of your quiz grades is -100, you will fail the course!" << endl;
						}
						else {

						double quiz_avr, quiz_grade;
						quiz_avr = (quiz1+quiz2+quiz3+quiz4) / 4;

						if (quiz_avr < 0) {
							quiz_grade = quiz_avr;
						}
						else {
							double quiz_ratio;
							quiz_ratio = quiz_avr/exam_avr;

							if (quiz_ratio <= 2) {
								quiz_grade = quiz_avr;
							}
							else if (2 < quiz_ratio && quiz_ratio < 3) {
								quiz_grade = quiz_avr * (3-quiz_ratio);
							}
							else if (quiz_ratio >= 3) {
								quiz_grade = 0;
							}
						}

						cout << name << ", your weighted exam average is: " << exam_avr << endl;
						cout << name << ", your THE average is: " << the_avr << " and you will get " << the_grade << " of it." << endl;
						cout << name << ", your quiz average is: " << quiz_avr << " and you will get " << quiz_grade << " of it." << endl;

						double overall;
						overall = quiz_grade * 0.2 + the_grade * 0.2 + midterm_grade * 0.3 + final_grade * 0.3 ;

						cout << name << ", your grade for CS201 is: " << overall << endl;

					}
				}
			}
		}
	}

  return 0;
}
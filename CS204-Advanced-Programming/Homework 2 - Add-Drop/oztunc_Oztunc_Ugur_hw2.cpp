#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// UGUR OZTUNC 28176 CS204 HW2 ADD-DROP

struct courseNode {
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode* next;
	//courseNode();
	courseNode(string a, string b, int c) {
		courseCode = a;
		courseName = b;
		studentsAttendingIDs.push_back(c);
		next = NULL;
	}
	courseNode(string a, string b) {
		courseCode = a;
		courseName = b;
		next = NULL;
	}
};

void addIntSortedVector(vector<int> &a, int x) // adds integer x to the vector a considering the ascending order of the vector
{
	if (a.size() == 0)
	{
		a.push_back(x);
	}
	else
	{
		if (x > a[a.size()-1])
		{
			a.push_back(x);
		}
		else if (x < a[0])
		{
			int temp;
			int insert = x;
			a.push_back(a[a.size()-1]);
			int k = 0;
			while(k < a.size()-1)
			{
				temp = a[k];
				a[k] = insert;
				insert = temp;
				k++;
			}
		}
		else
		{
			for (int i = 1; i < a.size(); i++)
			{
				if (a[i-1] < x && x < a[i])
				{
					int temp;
					int insert = x;
					a.push_back(a[a.size()-1]);
					int k = i;
					while(k < a.size()-1)
					{
						temp = a[k];
						a[k] = insert;
						insert = temp;
						k++;
					}
					break;
				}
			}
		}
	}
}

void delIntSortedVector(vector<int> &a, int x) // deletes integer x from the vector a considering the ascending order of the vector
{
	if (a.size() == 0)
	{
		cout << "empty vector" << endl;
	}
	else
	{
		if (a[a.size()-1] == x)
		{
			a.pop_back();
		}
		else
		{
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] == x)
				{
					int k = i;
					while(k < a.size()-1)
					{
						a[k] = a[k+1];
						k++;
					}
					a.pop_back();
					break;
				}
			}
		}
	}
}

courseNode* addNodeSorted(courseNode* headNode, courseNode* newNode) //adds new nodes with respect to ascending order
{
	courseNode* tempPtr = headNode;

	if (headNode == NULL || newNode->courseName < headNode->courseName)
	{
		newNode->next = headNode;
		return newNode;
	}

	while (tempPtr->next != NULL && tempPtr->next->courseName < newNode->courseName)
	{
		tempPtr = tempPtr->next;
	}

	newNode->next = tempPtr->next;
	tempPtr->next = newNode;
	
	return headNode;
}

void AddStudent(courseNode* targetNode, int newID) // sends proper data to the 'addIntSortedVector' function
{
	addIntSortedVector(targetNode->studentsAttendingIDs, newID);
}

courseNode* isExist(courseNode* headNode, string targetCourseName) // if target course name exists in linked list returns its node's pointer, if not exist returns NULL
{
	courseNode* tempPtr = headNode;
	while(tempPtr != NULL)
	{
		if (tempPtr->courseName == targetCourseName)
		{
			return tempPtr;
		}
		else
		{
			tempPtr = tempPtr->next;
		}
	}
	return NULL;
}

bool isEnrolled(courseNode* targetNode, int targetID) // if target studentd ID exists in targetNode's IDs vector returns true, if not returns false
{
	vector<int> targetDomain = targetNode->studentsAttendingIDs;
	int k = targetDomain.size();
	for (int i = 0; i < k; i++)
	{
		if (targetDomain[i] == targetID)
		{
			return true;
		}
	}
	return false;
}

void displayList(courseNode* headNode) // displays all courses and student IDs
{
	courseNode* tempPtr = headNode;
	while(tempPtr != NULL)
	{
		cout << tempPtr->courseCode << " " << tempPtr->courseName << ":";
		for (int i = 0; i < tempPtr->studentsAttendingIDs.size(); i++)
		{
			cout << " " << tempPtr->studentsAttendingIDs[i];
		}
		cout << endl;
		tempPtr = tempPtr->next;
	}
}

void displayFinalList(courseNode* headNode) // displays the final list when choice is 4
{
	cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;

	courseNode* tempPtr = headNode;
	while (tempPtr != NULL)
	{
		if (tempPtr->studentsAttendingIDs.size() < 3)
		{
			cout << tempPtr->courseCode << " " << tempPtr->courseName <<  " -> This course will be closed" << endl;
		}
		else
		{
			cout << tempPtr->courseCode << " " << tempPtr->courseName << ":";
			for (int i = 0; i < tempPtr->studentsAttendingIDs.size(); i++)
			{
				cout << " " << tempPtr->studentsAttendingIDs[i];
			}
			cout << endl;
		}
		tempPtr = tempPtr ->next;
	}

}


int main() {
	
	string fileName;
	cout << "Please enter file name: "; cin >> fileName;
	ifstream inFile;
	inFile.open(fileName.c_str());

	courseNode* head = NULL;

	string line;
	while(getline(inFile,line)) { //initialization of the nodes list based on the txt file
		istringstream ss(line);
		string courseCode_inTemp, courseName_inTemp;
		int studentsAttendingID_inTemp;
		ss >> courseCode_inTemp >> courseName_inTemp >> studentsAttendingID_inTemp;
		courseNode* NodePtr_inTemp = new courseNode(courseCode_inTemp,courseName_inTemp,studentsAttendingID_inTemp);

		if (isExist(head,courseName_inTemp) == NULL) // checking whether this course is created before
		{
			head = addNodeSorted(head,NodePtr_inTemp);
		}
		else
		{
			AddStudent(isExist(head,courseName_inTemp),studentsAttendingID_inTemp);
		}
	}
	inFile.close();

	cout << "Successfully opened file CoursesAndStudents.txt" << endl << "The linked list is created." << endl << "The initial list is:" << endl;
	displayList(head);

	int choice = 0;
	while(choice != 4)
	{
		cout << endl << "Please select one of the choices:" << endl;
		cout << "1. Add to List" << endl << "2. Drop from List" << endl << "3. Display List" << endl << "4. Finish Add/Drop and Exit" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
			string inStr,inCourseCode,inCourseName;
			int inID;
			cin.clear();
			cin.ignore();
			getline(cin,inStr);
			istringstream ss(inStr);

			while(ss >> inCourseCode >> inCourseName) // reading user given input's course name and code
			{
				courseNode* nodeToEnroll = isExist(head,inCourseName);
				if (nodeToEnroll == NULL)
				{
					nodeToEnroll = new courseNode(inCourseCode,inCourseName);
					head = addNodeSorted(head,nodeToEnroll);
					cout << inCourseCode << " does not exist in the list of Courses. It is added up." << endl;
				}

				while(ss >> inID)
				{
					if (isEnrolled(nodeToEnroll,inID) == true) // reading user given input's student IDs
					{
						cout << "Student with id " << inID << " already is enrolled to " << inCourseCode << ". No action taken." << endl;
					}
					else
					{
						AddStudent(nodeToEnroll,inID);
						cout << "Student with id " << inID << " is enrolled to " << inCourseCode << "." << endl;
					}
				}
				ss.clear();
			}
		}

		else if (choice == 2)
		{
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
			string inStr,inCourseCode,inCourseName;
			int inID;
			cin.clear();
			cin.ignore();
			getline(cin,inStr);
			istringstream ss(inStr);

			while(ss >> inCourseCode >> inCourseName) // reading user given input's course name and code
			{
				while(ss >> inID) // reading user given input's student IDs
				{
					if (isExist(head,inCourseName) == NULL)
					{
						cout << "The " << inCourseCode << " course is not in the list, thus student with id " << inID << " can’t be dropped." << endl;
					}
					else
					{
						if (isEnrolled(isExist(head,inCourseName),inID) == false)
						{
							cout << "Student with id " << inID << " is not enrolled to " << inCourseCode << ", thus he can't drop that course." << endl;
						}
						else
						{
							delIntSortedVector(isExist(head,inCourseName)->studentsAttendingIDs,inID);
							cout << "Student with id " << inID << " has dropped " << inCourseCode << "." << endl;
						}
					}
				}
				ss.clear();
			}
		}

		else if (choice == 3)
		{
			cout << "The current list of course and the students attending them:" << endl;
			displayList(head);
		}
	}

	displayFinalList(head);

	return 0;
}
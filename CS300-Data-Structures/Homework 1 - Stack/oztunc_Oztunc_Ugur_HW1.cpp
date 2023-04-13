#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include <fstream>
#include "randgen.h"

using namespace std;

struct cellNode {
	int x, y;
	cellNode* next;
	bool ways[4]; // { LEFT, UP, DOWN, RIGHT } (0, 1, 2, 3)
	bool isVisited;
	bool isOpen[4]; // wall status (true = no wall on that way)

	cellNode() {}

	cellNode(int a, int b) {
		x = a;
		y = b;
		next = NULL;
		ways[0] = true;
		ways[1] = true;
		ways[2] = true;
		ways[3] = true;
		isVisited = false;
		isOpen[0] = false;
		isOpen[1] = false;
		isOpen[2] = false;
		isOpen[3] = false;
	}
};

void fillMatrix(vector<vector<cellNode>> &matrix) { // adjusting a mazes initial ways i.e: 0,0 cell always has two walls (left and down) initially
	int a = matrix.size(), b = matrix[0].size();
	for (int i = 0; i < a; i++)
	{
		for (int k = 0; k < b; k++)
		{
			matrix[i][k] = cellNode(i,k);
			if (i == 0) { matrix[i][k].ways[0] = false; }
			if (k == 0) { matrix[i][k].ways[2] = false; }
			if (k == b-1) { matrix[i][k].ways[1] = false; }
			if (i == a-1) { matrix[i][k].ways[3] = false; }
		}
	}
}

void resetWays(vector<vector<cellNode>> &matrix) { // after generating a maze, adjusts ways based on isOpen status in order to find path later
	int a = matrix.size(), b = matrix[0].size();
	for (int i = 0; i < a; i++)
	{
		for (int k = 0; k < b; k++)
		{
			matrix[i][k].ways[0] = true;
			matrix[i][k].ways[1] = true;
			matrix[i][k].ways[2] = true;
			matrix[i][k].ways[3] = true;

			if (i == 0) { matrix[i][k].ways[0] = false; }
			if (k == 0) { matrix[i][k].ways[2] = false; }
			if (k == b-1) { matrix[i][k].ways[1] = false; }
			if (i == a-1) { matrix[i][k].ways[3] = false; }

			for (int j = 0; j < 4; j++)
			{
				if (matrix[i][k].isOpen[j]) {
					matrix[i][k].ways[j] = true;
				}
				else {
					matrix[i][k].ways[j] = false;
				}
			}

			matrix[i][k].isVisited = false;
		}
	}
}

int main() {
	int totalMaze, col, row;

	cout << "Enter the number of mazes: ";
	cin >> totalMaze;
	cout << "Enter the number of rows and columns (M and N): ";
	cin >> col >> row;

	vector<vector<vector<cellNode>>> mazes; // vector that will store all generated mazes' matrices

	Stack<cellNode> mazeStack; // a stack that will be used in whole program (after all parts stack will be empty and can be used again and again, thus there is no need to create more than one stack)

	int currentMazeNO = 0;
	while(currentMazeNO != totalMaze) { // creating 'K' mazes

		vector<vector<cellNode>> mazeMatrix(col, vector<cellNode>(row)); // creating a single mazeMatrix that will store information about cells
		
		fillMatrix(mazeMatrix); // explained in decleration

		cellNode* orgNode = new cellNode;
		*orgNode = mazeMatrix[0][0];
		mazeStack.push(orgNode); // pushing 0,0 cell

		while(!mazeStack.isEmpty()) { // generating maze
			cellNode* ptr = mazeStack.getTop();
			mazeMatrix[ptr->x][ptr->y].isVisited = true; // current cell is visited

			if (ptr->x == col-1 && ptr->y == row-1) { // if current cell is right up corner of maze, return, since it is the ending point of the maze
				mazeStack.popCommand();
			}
			else {
				vector<int> choices; // possible choices of current cell will be stored in this vector
				for (int i = 0; i < 4; i++) {
					if (ptr->ways[i]) { // checking current cell's ways array's i. element is true or false (means that it is possible to go that way)
						int pot_next_x = ptr->x, pot_next_y = ptr->y; // potential x and y values

						if (i == 0) { pot_next_x--; } // go left
						else if (i == 1) { pot_next_y++; } // go up
						else if (i == 2) { pot_next_y--; } // go down
						else if (i == 3) { pot_next_x++; } // go right

						if (mazeMatrix[pot_next_x][pot_next_y].isVisited) { // checking potential next cell's isVisited status true or false
							mazeMatrix[ptr->x][ptr->y].ways[i] = false; // changing current cell's 'i' way false in order to not consider it a potential way again later

							// changing the way of potential next cell's (which can not be traveled because of it is visited) to the current cell
							if (i == 0) { mazeMatrix[pot_next_x][pot_next_y].ways[3] = false; }
							else if (i == 1) { mazeMatrix[pot_next_x][pot_next_y].ways[2] = false; }
							else if (i == 2) { mazeMatrix[pot_next_x][pot_next_y].ways[1] = false; }
							else if (i == 3) { mazeMatrix[pot_next_x][pot_next_y].ways[0] = false; }
						}
						else { // all checks were passed, so this way can be traveled, it is added to the choices vector in order to be potentially chosen randomly later
							choices.push_back(i);
						}
					}
				}

				if (choices.size() != 0) { // if there are possible ways to travel
					RandGen random;
					int randidx = random.RandInt(choices.size());
					int choice = choices[randidx]; // choose a random way in choices vector
					int next_x = ptr->x, next_y = ptr->y; // next cell's x y values

					// changing next cell's way to go back to false (to the current cell)
					if (choice == 0) { next_x--; mazeMatrix[ptr->x-1][ptr->y].ways[3] = false; mazeMatrix[ptr->x-1][ptr->y].isOpen[3] = true; }
					else if (choice == 1) { next_y++; mazeMatrix[ptr->x][ptr->y+1].ways[2] = false; mazeMatrix[ptr->x][ptr->y+1].isOpen[2] = true; }
					else if (choice == 2) { next_y--; mazeMatrix[ptr->x][ptr->y-1].ways[1] = false; mazeMatrix[ptr->x][ptr->y-1].isOpen[1] = true;}
					else if (choice == 3) { next_x++; mazeMatrix[ptr->x+1][ptr->y].ways[0] = false; mazeMatrix[ptr->x+1][ptr->y].isOpen[0] = true;}

					mazeMatrix[ptr->x][ptr->y].isOpen[choice] = true; // removing the wall on this way


					cellNode* nextCell = new cellNode;
					*nextCell = mazeMatrix[next_x][next_y];
					mazeStack.push(nextCell); // pushing next cell

				}
				else { // if there are no possible ways to travel, return to previous cell (pop)
					mazeStack.popCommand();
				}
			}

		}

		string fname = "maze_";
		fname += to_string(currentMazeNO+1) + ".txt"; // setting maze file name
		ofstream foutput;
		foutput.open(fname, ios::out);

		foutput << row << " " << col << endl;

		for (int y = 0; y < row; y++) { // printing values to maze file
			for (int x = 0; x < col; x++) {
				foutput << "x=" <<  mazeMatrix[x][y].x << " y=" << mazeMatrix[x][y].y << " ";
				if (mazeMatrix[x][y].isOpen[0]) { foutput << "l=0 "; } else { foutput << "l=1 "; }
				if (mazeMatrix[x][y].isOpen[3]) { foutput << "r=0 "; } else { foutput << "r=1 "; }
				if (mazeMatrix[x][y].isOpen[1]) { foutput << "u=0 "; } else { foutput << "u=1 "; }
				if (mazeMatrix[x][y].isOpen[2]) { foutput << "d=0"; } else { foutput << "d=1"; }
				foutput << endl;
			}
		}

		foutput.close();

		resetWays(mazeMatrix); // explained in decleration
		mazes.push_back(mazeMatrix); // adding current maze to the mazes vector

		currentMazeNO++;
	}

	cout << "All mazes are generated." << endl;

	int targetMaze, entry_x, entry_y, exit_x, exit_y;

	cout << "Enter a maze ID between 1 to " << totalMaze << " inclusive to find a path: ";
	cin >> targetMaze;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> entry_x >> entry_y;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> exit_x >> exit_y;

	cellNode* entryNode = new cellNode;
	vector<vector<cellNode>>& mazeMatrix = mazes[targetMaze-1];
	*entryNode = mazeMatrix[entry_x][entry_y];
	mazeStack.push(entryNode); // pushing entry cell

	while (mazeStack.getTop()->x != exit_x || mazeStack.getTop()->y != exit_y) { // continue looking ways until top cell in stack is exit cell
		cellNode* ptr = mazeStack.getTop();

		int choice = 0;
		while(ptr->ways[choice] == false) { // instead of random choosing a non-walled way, always choose the first non-walled way in ways array (i.e: ptr->ways: { false,false,true,false } means 2nd index will be choosen which is going down)
			choice++;
		}
		
		if (ptr->ways[choice] == true) { // a check for the case of all ways in ways array is false
			int next_x = ptr->x, next_y = ptr->y;
			mazeMatrix[next_x][next_y].ways[choice] = false; // eliminating current way in order to not take it again in case of returning to current cell later
			ptr->ways[choice] = false; // doing same to the cellNode in stack again, since stack stores an updated copy of mazeMatrix's cells, not itself

			// changing next cell's ways to return current cell again to false
			if (choice == 0) { next_x--; mazeMatrix[ptr->x-1][ptr->y].ways[3] = false; } 
			else if (choice == 1) { next_y++; mazeMatrix[ptr->x][ptr->y+1].ways[2] = false; }
			else if (choice == 2) { next_y--; mazeMatrix[ptr->x][ptr->y-1].ways[1] = false; }
			else if (choice == 3) { next_x++; mazeMatrix[ptr->x+1][ptr->y].ways[0] = false; }

			cellNode* nextCell = new cellNode;
			*nextCell = mazeMatrix[next_x][next_y];
			mazeStack.push(nextCell); // going to next cell
		}
		else { // if all ways are false in ways array
			mazeStack.popCommand(); // return to previous cell
		}

	}

	vector<string> path; // a vector to store path coordinates REVERSED

	while(!mazeStack.isEmpty()) { // emptying path coordinates to the path vector REVERSED
		string temp = to_string(mazeStack.getTop()->x);
		temp += " ";
		temp += to_string(mazeStack.getTop()->y);

		path.push_back(temp);

		mazeStack.popCommand();
	}

	string fnamepath = "maze_";
	fnamepath += to_string(targetMaze) + "_path_";
	fnamepath += to_string(entry_x) + "_" + to_string(entry_y) + "_" + to_string(exit_x) + "_" + to_string(exit_y) + ".txt"; // setting output path file name
	ofstream foutput;
	foutput.open(fnamepath, ios::out);

	for (int i = path.size() - 1; i > -1 ; i--) { // printing the reversed coordinates in the path vector to output file REVERSED AGAIN in order to be proper
		foutput << path[i];
		if (i != 0) {
			foutput << endl;
		}
	}

	foutput.close();
	
	return 0;
}

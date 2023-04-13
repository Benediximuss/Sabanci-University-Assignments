#ifndef _BUSNETWORK_H
#define _BUSNETWORK_H

#include <iostream>
#include <string>
using namespace std;

struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;

	busStop(string a) {
		busStopName = a;
		left = NULL;
		right = NULL;
	}
};

struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine(string a) {
		busLineName = a;
		next = NULL;
		busStops = NULL;
	}
	busLine(string a, busStop* b) {
		busLineName = a;
		next = NULL;
		busStops = b;
	}
};

class BusNetwork
{
	public:
		BusNetwork(); //	default constructor with NULL head
		BusNetwork(busLine* initPtr); //	with initial head pointer
		
		void printNetwork(); //		print whole bus lines and stops
		bool consistencyCheck(); //		check whether all stops and lines are linked correctly or not

		void addBusLine(); // 3	add a new bus line with new stops
		void addBusStop(); // 4 add a new stop to an existing line

		void deleteBusLine(); // 5 delete a line completely
		void deleteBusStop(); // 6 delete a stop from a line

		void pathFinder(); // find path between two stops if its possible

	private:
		busLine* head;

		bool isLineExist(string a);
		bool isStopExist(string a,string b);
		bool isStopExist(busStop* a,string b);
		bool isStopExist_inNetwork(string a);
		bool isBothStopsExist_inLine(busLine* a,string b,string c);
		busLine* findLine(string a);
		busStop* findStop(busLine* a, string b);
};



#endif
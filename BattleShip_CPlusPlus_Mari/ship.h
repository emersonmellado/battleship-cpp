// Ship
#include <string>

using std::string;

#ifndef SHIP_H
#define SHIP_H

struct Point {
	int d;
	int x;
	int y;
};

class Ship {
private:
	int size;
	int horizontalVertical;//1: H/ 2: V
	string name;

public:
	Point point[5];
	bool hitFlag[5];
	Ship();
	~Ship();
	/*
	1.	A String that can be used as the ship’s name
	2.	An int smaller than 4 and bigger than 0 that identifies the size (length) of a ship.
	3.	An int that is either 1 or 2 that shows whether the ship is placed horizontally or vertically.
	4.	A function called Place() that should place a ship randomly (correctly) on a grid. If a ship location is not available or the ship can’t be placed, the function should try again until it places the ship.
	5.	A function called InformationLog() that appends to an information log( information log is a simple sequential file)
	6.	A function called ErrorLog() that appends to an error log when a ship is not placed due to logical errors. (Example: you cannot place a 3 cell long ship vertically in row 16 col 1)
	*/
	void SetName(string);
	string GetName();
	void SetSize(int);
	int GetSize();
	void SetPosition(int);
	int GetPosition();

	void Place(int, int);
	void SaveInformationLog(string);
	void SaveErrorLog(string);
};

#endif


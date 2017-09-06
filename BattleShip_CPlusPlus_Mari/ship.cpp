#include <iostream>
#include <sstream>

#include "ship.h"

using std::endl;

#include "log.h"
#include "informationLog.h"
#include "errorLog.h"

Ship::Ship() {}

void Ship::SetName(string shipName) {
	name = shipName;
}
string Ship::GetName() {
	return name.c_str();
}
int Ship::GetSize() {
	return size;
}
int Ship::GetPosition() {
	return horizontalVertical;
}

void Ship::SetSize(int shipSize) {
	if (shipSize < 0 || shipSize > 4) {
		std::stringstream msg;
		msg << "Invalid ship size for ship: " << name << ". Value passed was: " << shipSize << ". It must be between 1 and 4";
		SaveErrorLog(msg.str());
		return;
	}
	size = shipSize;
}

void Ship::SetPosition(int positionHorizontalVertical) {
	if (positionHorizontalVertical < 1 || positionHorizontalVertical >2) {
		std::stringstream msg;
		msg << "Invalid ship position for ship: " << name << ". Value passed was: " << positionHorizontalVertical << ". It must be 1 for Horizontal or 2 for Vertical";
		SaveErrorLog(msg.str());
		return;
	}
	horizontalVertical = positionHorizontalVertical;
}

Ship::~Ship() { }

void Ship::Place(int BOARD_WIDTH, int BOARD_HEIGHT)
{
	/*
	In the game play you also need to append to the information log. Each step that you successfully finish must append a success message in the file.
	For example when a player shoots row 1 col1, the log could be “attempting to shoot Row1, Col1”.
	You need to keep track of number of shoots and save it in a sequential file called War Hero if it is smaller than the previous version.
	If and when this happens, you need to ask for the player name and save the name and the number if shoots in the file. (Example: Destroyer, 6 hits!)
	You should also be visually helpful, meaning that after each shooting you should redraw the grid and show the new status in it. (Example: H for Hit, M for Miss)
	(10 marks) for the driver
	*/

	//PLACESHIPS UserInputShipPlacement()
	//{
	int d, x, y;
	//hipLocation temp;
	//Using this as a bad return
	//this->point[0].X = -1;
	//Get 3 integers from user
	d = rand() % 2 + 1;
	do {
		x = rand() % BOARD_WIDTH;
	} while (x < 0 || x >= BOARD_WIDTH);

	do {
		y = rand() % BOARD_HEIGHT;
	} while (y < 0 || y >= BOARD_HEIGHT);

	//Good data
	this->horizontalVertical = d;
	this->point[0].X = x;
	this->point[0].Y = y;
	//return temp;
	//}
}

void Ship::SaveInformationLog(string textToSave)
{
	InformationLog infoLog;
	infoLog.WriteInFile(textToSave);
}

void Ship::SaveErrorLog(string textToSave)
{
	ErrorLog errorLog;
	errorLog.WriteInFile(textToSave);
}
#include <iostream>
#include <string>
#include <vector>

#include "ship.h"

using namespace std;

const int BOARD_WIDTH = 16;
const int BOARD_HEIGHT = 16;
const int SHIP_TYPES = 5;

const char isWATER = 247; //ASCII Character Code
const char isHIT = 'H';
const char isSHIP = 'S';
const char isMISS = 'M';

vector<Ship> ship(SHIP_TYPES);

struct PLAYER {
	char grid[BOARD_WIDTH][BOARD_HEIGHT];
}player[3]; //Ignore player 0, just using player's 1 & 2

enum Position { HORIZONTAL = 1, VERTICAL = 2 };

struct ShipLocation {
	Position direction;
	Ship ship;
};

bool gameRunning = false;

//Functions
void LoadShips();
void ResetBoard();
void DrawBoard(int);
ShipLocation UserInputShipPlacement();
bool UserInputAttack(int&, int&, int);
bool GameOverCheck(int);

int main()
{
	LoadShips();
	ResetBoard();

	//"PLACE SHIPS" phase of game
	//Loop through each player... 
	for (int aplyr = 1; aplyr<3; ++aplyr)
	{
		//Loop through each ship type to place
		for (int thisShip = 0; thisShip<SHIP_TYPES; ++thisShip)
		{
			//Display gameboard for player
			system("cls");
			DrawBoard(aplyr);
			//Give instructions
			/*cout << "\n";
			cout << "INSTRUCTIONS (Player " << aplyr << ")\n\n";
			cout << "You are about to place your ships.  Format should be:\n";
			cout << "Facing (1:Horizontal,2:Vertical), X (top-row) coords, Y (left-side) coords\n";
			cout << "Example: 1 7 2    This would place a ship beginning at X:7 Y:2 going horizontal\n\n";
			cout << "Ship to place: " << ship[thisShip].GetName() << " which has a length of " << ship[thisShip].GetSize() << "\n";
			cout << "Where do you want it placed? ";*/

			//Get input from user and loop until good data is returned
			ShipLocation aShip;
			//aShip.ship.point[0].X = -1;
			//while (aShip.ship.point[0].X == -1)
			//{
				aShip.ship.Place(BOARD_WIDTH, BOARD_HEIGHT);
				//aShip = UserInputShipPlacement();
			//}

			//Combine user data with "this ship" data
			aShip.ship.SetSize(ship[thisShip].GetSize());
			aShip.ship.SetName(ship[thisShip].GetName());

			//Add the FIRST grid point to the current player's game board
			player[aplyr].grid[aShip.ship.point[0].X][aShip.ship.point[0].Y] = isSHIP;

			//Determine ALL grid points based on length and direction
			for (int i = 1; i<aShip.ship.GetSize(); ++i)
			{
				//horizontalVertical
				if (aShip.ship.GetPosition() == HORIZONTAL) {
					aShip.ship.point[i].X = aShip.ship.point[i - 1].X + 1;
					aShip.ship.point[i].Y = aShip.ship.point[i - 1].Y;
				}
				if (aShip.ship.GetPosition() == VERTICAL) {
					aShip.ship.point[i].Y = aShip.ship.point[i - 1].Y + 1;
					aShip.ship.point[i].X = aShip.ship.point[i - 1].X;
				}

				//Add the REMAINING grid points to our current players game board
				player[aplyr].grid[aShip.ship.point[i].X][aShip.ship.point[i].Y] = isSHIP;
			}
			//Loop back through each ship type
		}
		//Loop back through each player
	}

	//********* FINISHED WITH "PLACE SHIPS" PHASE *********************************
	//*****************************************************************************

	//Ready to play the game
	gameRunning = true;
	int thisPlayer = 1;
	do {
		//Because we are ATTACKING now, the 
		//opposite players board is the display board
		int enemyPlayer;
		if (thisPlayer == 1) enemyPlayer = 2;
		if (thisPlayer == 2) enemyPlayer = 1;
		system("cls");
		DrawBoard(enemyPlayer);

		//Get attack coords from this player
		bool goodInput = false;
		int x, y;
		while (goodInput == false) {
			goodInput = UserInputAttack(x, y, thisPlayer);
		}

		//Check board; if a ship is there, set as HIT.. otherwise MISS
		if (player[enemyPlayer].grid[x][y] == isSHIP) {
			player[enemyPlayer].grid[x][y] = isHIT;
		}

		if (player[enemyPlayer].grid[x][y] == isWATER) {
			player[enemyPlayer].grid[x][y] = isMISS;
		}

		//Check to see if the game is over
		//If 0 is returned, nobody has won yet
		int aWin = GameOverCheck(enemyPlayer);
		if (aWin != 0) {
			gameRunning = false;
			break;
		}
		//Alternate between each player as we loop back around
		thisPlayer = (thisPlayer == 1) ? 2 : 1;
	} while (gameRunning);

	system("cls");
	cout << "\n\nCONGRATULATIONS!!!  PLAYER " << thisPlayer << " HAS WON THE GAME!\n\n\n\n";

	system("pause");
	return 0;
}


bool GameOverCheck(int enemyPLAYER)
{
	bool winner = true;
	//Loop through enemy board
	for (int w = 0; w<BOARD_WIDTH; ++w) {
		for (int h = 0; h<BOARD_HEIGHT; ++h) {
			//If any ships remain, game is NOT over
			if (player[enemyPLAYER].grid[w][h] = isSHIP)
			{
				winner = false;
				return winner;
			}
		}
	}
	//If we get here, somebody won, game over!
	return winner;
}


bool UserInputAttack(int& x, int& y, int theplayer)
{
	cout << "\nPLAYER " << theplayer << ", ENTER COORDINATES TO ATTACK: ";
	bool goodInput = false;
	cin >> x >> y;
	if (x<0 || x >= BOARD_WIDTH) return goodInput;
	if (y<0 || y >= BOARD_HEIGHT) return goodInput;
	goodInput = true;
	return goodInput;
}

ShipLocation UserInputShipPlacement()
{
	int d, x, y;
	ShipLocation tmp;
	//Using this as a bad return
	tmp.ship.point[0].X = -1;
	//Get 3 integers from user
	cin >> d >> x >> y;
	if (d != 0 && d != 1) return tmp;
	if (x<0 || x >= BOARD_WIDTH) return tmp;
	if (y<0 || y >= BOARD_HEIGHT) return tmp;
	//Good data
	tmp.direction = (Position)d;
	tmp.ship.point[0].X = x;
	tmp.ship.point[0].Y = y;
	return tmp;
}

void LoadShips()
{
	ship[0].SetName("Cruiser");		ship[0].SetSize(2);		ship[0].SetPosition(1);
	ship[1].SetName("Frigate");		ship[1].SetSize(3);		ship[1].SetPosition(1);
	ship[2].SetName("Submarine");	ship[2].SetSize(3);		ship[2].SetPosition(2);
	ship[3].SetName("Escort");		ship[3].SetSize(4);		ship[3].SetPosition(1);
	ship[4].SetName("Battleship");	ship[4].SetSize(5);		ship[4].SetPosition(2);
}
void ResetBoard()
{
	//Loop through each player
	for (int plyr = 1; plyr<3; ++plyr)
	{
		//For each grid point, set contents to 'water'
		for (int w = 0; w<BOARD_WIDTH; ++w) {
			for (int h = 0; h<BOARD_HEIGHT; ++h) {
				player[plyr].grid[w][h] = isWATER;
			}
		}
		//Loop back to next player
	}
}

void DrawBoard(int thisPlayer)
{
	//Draws the board for a player (thisPlayer)
	cout << "PLAYER " << thisPlayer << "'s GAME BOARD\n";
	cout << "----------------------\n";

	//Loop through top row (board_width) and number columns
	cout << "   ";
	for (int w = 0; w<BOARD_WIDTH; ++w) {
		if (w < 10)
			//Numbers only 1 character long, add two spaces after
			cout << w << "  ";
		else if (w >= 10)
			//Numbers 2 characters long, add only 1 space after
			cout << w << " ";
	}
	cout << "\n";

	//Loop through each grid point and display to console
	for (int h = 0; h<BOARD_HEIGHT; ++h) {
		for (int w = 0; w<BOARD_WIDTH; ++w) {

			//If this is the FIRST (left) grid point, number the grid first
			if (w == 0) cout << h << " ";
			//If h was 1 character long, add an extra space to keep numbers lined up
			if (w<10 && w == 0) cout << " ";
			//Display contents of this grid (if game isn't running yet, we are placing ships
			//so display the ships
			if (gameRunning == false) cout << player[thisPlayer].grid[w][h] << "  ";
			//Don't show ships, BUT show damage if it's hit
			if (gameRunning == true && player[thisPlayer].grid[w][h] != isSHIP)
			{
				cout << player[thisPlayer].grid[w][h] << "  ";
			}
			else if (gameRunning == true && player[thisPlayer].grid[w][h] == isSHIP)
			{
				cout << isWATER << "  ";
			}
			//If we have reached the border.. line feed
			if (w == BOARD_WIDTH - 1) cout << "\n";
		}
	}
}
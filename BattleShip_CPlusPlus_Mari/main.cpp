#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "ship.h"

using namespace std;

const int BOARD_WIDTH = 16;
const int BOARD_HEIGHT = 16;
const int SHIP_TYPES = 5;

const char isWATER = 247; //ASCII Character Code
const char isHIT = 'H';
const char isSHIP = 'S';
const char isMISS = 'M';

vector<Ship> userShips(SHIP_TYPES + 1);
vector<Ship> enemyShips(SHIP_TYPES + 1);

struct PLAYER {
	char grid[BOARD_WIDTH][BOARD_HEIGHT];
	//int shipId[BOARD_WIDTH][BOARD_HEIGHT];
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
bool GameOverCheck(int);

int random(int, int);

int random(int low, int high) {
	if (low > high) return high;
	return low + (std::rand() % (high - low + 1));
}

int main()
{
	LoadShips();
	ResetBoard();

	//Loop through each player... 
	for (int aplyr = 1; aplyr < 3; ++aplyr)
	{
		//Loop through each ship type to place
		for (int thisShip = 0; thisShip <= SHIP_TYPES; ++thisShip)
		{
			system("cls");
			DrawBoard(aplyr);

			Ship currentShip;
			if (aplyr == 1) {
				currentShip = userShips[thisShip];
			}
			else {
				currentShip = enemyShips[thisShip];
			}

			currentShip.Place(BOARD_WIDTH, BOARD_HEIGHT);

			//Add the FIRST grid point to the current player's game board
			player[aplyr].grid[currentShip.point[0].x][currentShip.point[0].y] = isSHIP;
			//player[aplyr].shipId[currentShip.point[0].x][currentShip.point[0].y] = thisShip;

			//Determine ALL grid points based on length and direction
			for (int i = 1; i < currentShip.GetSize(); ++i)
			{
				//horizontalVertical
				if (currentShip.GetPosition() == HORIZONTAL) {
					currentShip.point[i].x = currentShip.point[i - 1].x + 1;
					currentShip.point[i].y = currentShip.point[i - 1].y;
				}
				if (currentShip.GetPosition() == VERTICAL) {
					currentShip.point[i].y = currentShip.point[i - 1].y + 1;
					currentShip.point[i].x = currentShip.point[i - 1].x;
				}

				//Add the REMAINING grid points to our current players game board
				player[aplyr].grid[currentShip.point[i].x][currentShip.point[i].y] = isSHIP;
				//player[aplyr].shipId[currentShip.point[i].x][currentShip.point[i].y] = thisShip;
			}

			if (aplyr == 1) {
				userShips[thisShip] = currentShip;
			}
			else {
				enemyShips[thisShip] = currentShip;
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
		if (thisPlayer == 2) {
			//If the player == 2 it means the computer
			//So we are going to fake a random shot
			srand(time(NULL));
			do {
				x = random(0, BOARD_WIDTH);
				y = random(0, BOARD_HEIGHT);
			} while (player[enemyPlayer].grid[x][y] == isMISS || player[enemyPlayer].grid[x][y] == isHIT);

			goodInput = true;
		}
		while (goodInput == false) {
			goodInput = UserInputAttack(x, y, thisPlayer);
		}

		Ship shipHit;

		for (int i = 0; i < SHIP_TYPES + 1; ++i)
		{
			for (int j = 0; j < SHIP_TYPES - 1; ++j)
			{
				if (enemyPlayer == 1) {
					if (userShips[i].point[j].x == x && userShips[i].point[j].y == y) {
						userShips[i].hitFlag[j] = true;
						shipHit = userShips[i];
						break;
					}
				}
				else {
					if (enemyShips[i].point[j].x == x && enemyShips[i].point[j].y == y) {
						enemyShips[i].hitFlag[j] = true;
						shipHit = enemyShips[i];
						break;
					}
				}
			}
		}

		int hitNumber = 0;
		for (int i = 0; i < SHIP_TYPES - 1; ++i)
		{
			if (shipHit.hitFlag[i] == true) {
				hitNumber++;
			}
		}

		string currentPlayer = (thisPlayer == 1) ? "USER" : "COMPUTER";

		//Check board; if a ship is there, set as HIT.. otherwise MISS
		if (player[enemyPlayer].grid[x][y] == isSHIP) {
			player[enemyPlayer].grid[x][y] = isHIT;

			shipHit.SaveInformationLog(currentPlayer + ": " + shipHit.GetName() + ", was HIT " + to_string(hitNumber) + " times");
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

		//system("pause");
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
	for (int w = 0; w < BOARD_WIDTH; ++w) {
		for (int h = 0; h < BOARD_HEIGHT; ++h) {
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
	string currentPlayer = (theplayer == 1) ? "USER" : "COMPUTER";
	cout << "\n " << currentPlayer << ", ENTER COORDINATES TO ATTACK: EX: 8:4";
	bool goodInput = false;
	char dummy;
	cin >> x >> dummy >> y;
	if (x < 0 || x >= BOARD_WIDTH) return goodInput;
	if (y < 0 || y >= BOARD_HEIGHT) return goodInput;
	goodInput = true;
	return goodInput;
}

void LoadShips()
{
	userShips[0].SetName("Cruiser");		userShips[0].SetSize(2);		userShips[0].SetPosition(1);
	userShips[1].SetName("Frigate");		userShips[1].SetSize(5);		userShips[1].SetPosition(1);
	userShips[2].SetName("Submarine");		userShips[2].SetSize(3);		userShips[2].SetPosition(2);
	userShips[3].SetName("Escort");			userShips[3].SetSize(4);		userShips[3].SetPosition(1);
	userShips[4].SetName("Battleship");		userShips[4].SetSize(2);		userShips[4].SetPosition(2);
	userShips[5].SetName("Destroyer");		userShips[5].SetSize(4);		userShips[5].SetPosition(2);

	enemyShips[0].SetName("Cruiser");		enemyShips[0].SetSize(2);		enemyShips[0].SetPosition(1);
	enemyShips[1].SetName("Frigate");		enemyShips[1].SetSize(3);		enemyShips[1].SetPosition(1);
	enemyShips[2].SetName("Submarine");		enemyShips[2].SetSize(3);		enemyShips[2].SetPosition(2);
	enemyShips[3].SetName("Escort");		enemyShips[3].SetSize(4);		enemyShips[3].SetPosition(1);
	enemyShips[4].SetName("Battleship");	enemyShips[4].SetSize(2);		enemyShips[4].SetPosition(2);
	enemyShips[5].SetName("Destroyer");		enemyShips[5].SetSize(4);		enemyShips[5].SetPosition(2);
}
void ResetBoard()
{
	//Loop through each player
	for (int plyr = 1; plyr < 3; ++plyr)
	{
		//For each grid point, set contents to 'water'
		for (int w = 0; w < BOARD_WIDTH; ++w) {
			for (int h = 0; h < BOARD_HEIGHT; ++h) {
				player[plyr].grid[w][h] = isWATER;
			}
		}
		//Loop back to next player
	}
}

void DrawBoard(int thisPlayer)
{
	//Draws the board for a player (thisPlayer)
	string currentPlayer = (thisPlayer == 1) ? "USER" : "COMPUTER";
	cout << currentPlayer << " - GAME BOARD\n";
	cout << "----------------------\n";

	//Loop through top row (board_width) and number columns
	cout << "   ";
	for (int w = 0; w < BOARD_WIDTH; ++w) {
		if (w < 10)
			//Numbers only 1 character long, add two spaces after
			cout << w << "  ";
		else if (w >= 10)
			//Numbers 2 characters long, add only 1 space after
			cout << w << " ";
	}
	cout << "\n";

	//Loop through each grid point and display to console
	for (int h = 0; h < BOARD_HEIGHT; ++h) {
		for (int w = 0; w < BOARD_WIDTH; ++w) {

			//If this is the FIRST (left) grid point, number the grid first
			if (w == 0) cout << h << " ";
			//If h was 1 character long, add an extra space to keep numbers lined up
			if (w < 10 && w == 0) cout << " ";
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
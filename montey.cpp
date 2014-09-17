/********************************************
* A little simulator to test the Monty Hall
* door problem.
*
* Author: Weston Dranfield
*********************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include <stdlib.h>

using namespace std;

struct Door
{
	bool isOpen;
	bool isWinner;
};

class GameShow 
{
public:
	void resetGame(int numDoors = 3); //get a new game ready to play
	void play();         //play the game
	void showStats(bool didWin);    //show the game stats

	GameShow();
	~GameShow();
private:
	void deleteDoors();   //delete all doors created
	int getUserInput(string message);   //return the user's input
	void executeRound();  //do a round;

	vector<Door *> doors; //collection of doors
	double numWins;       //number of wins
	double numLoses;      //number of loses
	int winningDoor;      //index of the winning door
};

GameShow::GameShow()
{
	resetGame();
	numWins = 0;
	numLoses = 0;
}

GameShow::~GameShow()
{
	deleteDoors();
}

void GameShow::deleteDoors()
{
	//delete all doors
	for (int i = 0; i < doors.size(); i++)
	{
		delete doors[i];
	}

	doors.clear();
}

void GameShow::resetGame(int numDoors)
{
	//delete any previous doors
	deleteDoors();

	//pick a random door to win
	winningDoor = rand() % 4;

	//create a vector of numDoors doors
	for (int i = 0; i < numDoors; i++)
	{ 
		//create our new door
		Door *  newDoor = new Door();

		//set the door to closed
		newDoor->isOpen = false;

		//set one door to the be the winner
		newDoor->isWinner = (i == winningDoor - 1) ? true : false;

		//add the door to the vector
		doors.push_back(newDoor);
	}
}

int GameShow::getUserInput(string message)
{
	

	//display options
	cout << "\nPlease enter " + message + ": ";

	//get the input
	int numRounds;
	cin >> numRounds;

	return numRounds;
}

void GameShow::executeRound()
{
	//choose a door
	bool notValid = true;
	int choice = -1;

	while (notValid)
	{
		choice = getUserInput("the door you choose (between 1 and 3)");
		if (choice > 0 && choice <= doors.size())
			notValid = false;
	}

	//check if we have a win
	if (doors[choice - 1]->isWinner)
	{
		cout << "The show host just opened a loosing door, ";
		int doSwitch = getUserInput("if you would like to switch doors (1. yes  2. no)");

		if (doSwitch == 2)
		{
			//increment wins
			numWins++;

			//show stats
			showStats(true);
		}
		else
		{
			//increment wins
			numLoses++;

			//show stats
			showStats(false);
		}
	}
	else
	{
		cout << "The show host just opened a loosing door, ";
		int doSwitch = getUserInput("if you would like to switch doors (1. yes  2. no)");

		if (doSwitch == 1)
		{
			//increment wins
			numWins++;

			//show stats
			showStats(true);
		}
		else
		{
			//increment wins
			numLoses++;

			//show stats
			showStats(false);
		}
	}
}

void GameShow::showStats(bool didWin)
{
	cout << ((didWin) ? "You Won!" : "You Lost :(") << endl;
	cout << "\nWINS:  " << numWins;
	cout << "\nLoses: " << numLoses;
	cout << "\nFrequency of wins: " << ((numWins / (numWins + numLoses)) * 100) << " perecent\n\n\n\n";
}

void GameShow::play()
{
	executeRound();
}

int main(int argc, char* argv[]) 
{
	int numGames = 100;
	if (argc > 1)
		numGames = atoi(argv[1]);

	cout << "    ___                    \n"
	     << "   /   \\___   ___  _ __    \n"
	     << "  / /\\ / _ \\ / _ \\| '__|    \n"
	     << " / /_// (_) | (_) | |       \n"
	     << "/___,' \\___/ \\___/|_|       \n"
	     << "                           \n"
	     << "   ___               _      \n"
	     << "  / _ \\_   _ _______| | ___ \n"
	     << " / /_)/ | | |_  /_  / |/ _ \n"
		 << "/ ___/| |_| |/ / / /| |  __/\n"
		 << "\\/     \\__,_/___/___|_|\\___|\n\n\n";
	GameShow myGame;
	for (int i = 0; i < numGames; i++)
	{
		myGame.play();
		myGame.resetGame();
	}
	return 0;
}
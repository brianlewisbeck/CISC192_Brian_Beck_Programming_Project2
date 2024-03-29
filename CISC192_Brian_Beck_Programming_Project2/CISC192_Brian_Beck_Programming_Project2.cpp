// CISC192_Brian_Beck_Programming_Project2.cpp : Defines the entry point for the console application.
// CISC 192
// Programming Project 2
// Brian Beck
// Started 08072018

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
// #include <ncurses.h> Probably best to use this instead of system clear.

using namespace std;


// function prototypes
void displayRace(int, int, int);  // displays the current status of race, starting with clear screen.
void doRound(int &, int &, int &); // performs random number calculation and adds to distance traveled.
void determineLeader(string &, int, int, int); // determins the current leader and modifies the string
void raceSummary(string, int, int, int, int); // provide winner information.

int main()
{
	const int TRACK_LENGTH = 50; 

	// TO DO: should I correct the misuse of "tie"

	string currentLeader = "tie"; // "tie" is correct at the start but not technically accurate after another round without a leader.  It is still a tie in that there is no winner.  
	
	
	bool
		// tie_break = false, I have commented out some possible alternative ways of dealing with ties, etc., that I decided not to use.
		cross_line = false,
		race_over = false,
		A_cross = false, 
		B_cross = false,
		C_cross = false;
	int round = 1, //counter indicating we are at the start of round 1.
		// numberAcross = 0,
		ADist = 0,
		BDist = 0,
		CDist = 0;

	do // do a first round and repeat until race is over.
	{ 
		displayRace(ADist, BDist, CDist);
		doRound(ADist, BDist, CDist);
		round++;
		determineLeader(currentLeader, ADist, BDist, CDist);

		if (ADist > TRACK_LENGTH && !A_cross) // once one racer has crossed the finish line we test for winners.
			// TO DO: we test for winners when only one crosses, which is redundant; 
		{
			A_cross = true;
			// numberAcross++;
			cross_line = true;
		}
		if (BDist > TRACK_LENGTH && !B_cross)
		{
			B_cross = true;
			// numberAcross++;
			cross_line = true;
		}
		if (CDist > TRACK_LENGTH && !C_cross)
		{
			C_cross = true;
			// numberAcross++;
			cross_line = true;
		}

		if (cross_line && currentLeader != "tie")
			race_over = true; // race is over when at least one driver has crossed 50, and when there is not a tie. Note that there is a remote possibility of a 3rd driver having passed less than 50, but catching up to the other 2 if they repeatedly tie.

	} while (!race_over);

	raceSummary(currentLeader, ADist, BDist, CDist, round);
	cin.get();
	return 0;
}


void doRound( int &ADist, int &BDist, int &CDist)
{
	const int MAX_VALUE = 10;
	const int MIN_VALUE = 1;

	// Get the system time.

	unsigned seed = time(0);

	// Seed the random number generator
	srand(seed);
	
	ADist += (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
	BDist += (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
	CDist += (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
	
}

void displayRace(int ADist, int BDist, int CDist)
{
	system("CLS"); // this clears the screen but is windows dependent.  it would be better to use ncurses and reset the position to 0,0 after each run.
	cout << "                            ALPHABET SPEEDWAYS" << endl;

	//using loops to set out "racetrack"

	for (int i = 0; i < 75; i++)
	{
		cout << "=";

	}
	cout << endl << "=" << endl << "=" << endl << "=" << endl;
	
	for (int a = 0; a < ADist; a++)
	{
		cout << " ";
	}
	cout << "<A>";
	cout << endl << "=" << endl << "=" << endl << "=" << endl;

	for (int b = 0; b < BDist; b++)
	{
		cout << " ";
	}
	cout << "<B>";
	cout << endl << "=" << endl << "=" << endl << "=" << endl;

	for (int c = 0; c < CDist; c++)
	{
		cout << " ";
	}
	cout << "<C>";
	cout << endl << "=" << endl << "=" << endl << "=" << endl;

	for (int j = 0; j < 75; j++)
	{
		cout << "=";

	}
	this_thread::sleep_for(chrono::milliseconds(1500));
}

void determineLeader(string &currentLeader, int ADist, int BDist, int CDist)
{
	if (ADist > BDist && ADist > CDist)
		currentLeader = "A";
	else if (BDist > ADist && BDist > CDist)
		currentLeader = "B";
	else if (CDist > ADist && CDist > BDist)
		currentLeader = "C";
	else
		currentLeader = "tie";
}

void raceSummary(string currentLeader, int ADist, int BDist, int CDist, int round)
{
	cout << endl << "The winner is " << currentLeader << "." << endl;
	cout << currentLeader << " won in " << round << " rounds." << endl;

	if (currentLeader == "A")
		cout << currentLeader << " traveled a total of " << ADist << " spaces.  Vroom Vroom!!";
	if (currentLeader == "B")
		cout << currentLeader << " traveled a total of " << BDist << " spaces.  Vroom Vroom!!";
	if (currentLeader == "C")
		cout << currentLeader << " traveled a total of " << CDist << " spaces.  Vroom Vroom!!";
}
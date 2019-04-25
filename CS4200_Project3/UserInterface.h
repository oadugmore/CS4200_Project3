#pragma once

#include "Node.h"
#include <vector>
#include <string>
#include <array>
#include <iostream>

using namespace std;

class UserInterface
{
public:
	// Asks the user to enter an integer, and returns a validated int from the user's input.
	int GetTimeLimit();

	// Asks the user to enter a decimal number, and returns a validated double from the user's input.
	//virtual double GetDouble() = 0;

	// Asks the user which player should start, and returns true if the computer should start.
	bool ComputerStarts();

	// Asks the user to enter a string, and returns the inputted string.
	//virtual std::string GetString() = 0;

	// Asks the user to enter a move, and returns a pair of coordinates for the desired move.
	array<int, 2> GetMove();

	void DisplayBoard(Node board);

private:
    bool ValidMove(string move);
	int CharToInt(char c);
	char IntToChar(int i);
	string vsMessage;
	vector<string> moves;
};

#pragma once

#include <string>
#include <array>
#include <iostream>

using namespace std;

class UserInterface
{
public:
	// Asks the user to enter an integer, and returns a validated int from the user's input.
	virtual int GetTimeLimit();

	// Asks the user to enter a decimal number, and returns a validated double from the user's input.
	//virtual double GetDouble() = 0;

	// Asks the user which player should start, and returns true if the computer should start.
	virtual bool ComputerStarts();

	// Asks the user to enter a string, and returns the inputted string.
	//virtual std::string GetString() = 0;

	// Asks the user to enter a move, and returns a pair of coordinates for the desired move.
	virtual string GetMove();

	virtual void DisplayBoard();

private:
    bool ValidMove(string move);
};

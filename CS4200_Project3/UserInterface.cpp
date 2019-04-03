#include "UserInterface.h"

int UserInterface::GetTimeLimit()
{
    cout << "Enter the time limit, in seconds: ";
    int input;
    for (;;)
    {
        if (cin >> input && input > 0)
            return input;
        else
        {
            cout << "Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool UserInterface::ComputerStarts()
{
    cout << "Who goes first, C for computer, O for opponent: ";
    char input;
    for (;;)
    {
        if (cin >> input && (input == 'C' || input == 'c' || input == 'O' || input == 'o'))
            return (input == 'C' || input == 'c');
        else
        {
            cout << "Please enter either C or O." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string UserInterface::GetMove()
{
    cout << "Enter a move: ";
    string input;
    for (;;)
    {
        if (cin >> input && ValidMove(input))
            return input;
        else
        {
            cout << "Please enter a move in the form A1, E6, etc." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool UserInterface::ValidMove(string move)
{
    if (move.size() != 2) return false;
    char letter = __ascii_tolower(move[0]);
    int number = move[1];
    if (letter < 'a' || letter > 'h') return false;
    if (number < 1 || number > 8) return false;
    return true;
}


void UserInterface::DisplayBoard()
{
}

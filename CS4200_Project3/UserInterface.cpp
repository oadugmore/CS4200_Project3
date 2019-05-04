#include "UserInterface.h"
#include <iostream>
#include <limits>
#include <cctype>


const int ROW_COUNT = 8;
using std::numeric_limits;
using std::streamsize;
using std::tolower;
using std::toupper;
using std::cin;
using std::cout;
using std::endl;

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
        {
            bool computerStarts = (input == 'C' || input == 'c');
            vsMessage = computerStarts ? "Computer vs. Opponent" : "Opponent vs. Computer";
            return computerStarts;
        }
        else
        {
            cout << "Please enter either C or O." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

array<int, 2> UserInterface::GetMove()
{
    cout << endl;
    cout << "Enter opponent's move: ";
    string input;
    for (;;)
    {
        if (cin >> input && ValidMove(input))
        {
            moves.push_back("" + toupper(static_cast<unsigned char>(input[0])) + input[1]);
            return { CharToInt(input[0]), input[1] - '1' };
        }
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
    char letter = tolower(static_cast<unsigned char>(move[0]));
    int number = move[1] - '0';
    if (letter < 'a' || letter > 'h') return false;
    if (number < 1 || number > 8) return false;
    return true;
}

int UserInterface::CharToInt(unsigned char c)
{
    auto letter = tolower(c);
    return (letter - 'a');
}

char UserInterface::IntToChar(int i)
{
    return ('A' + i);
}

void UserInterface::DisplayBoard(Node board)
{
    cout << endl;
    cout << "  1 2 3 4 5 6 7 8\t" << vsMessage << endl;
    auto state = board.GetState();

    auto computerMove = board.LastMove();
    // for the first move there is no "last move."
    if (computerMove[0] != -1)
    {
        moves.push_back("" + IntToChar(computerMove[0]) + (computerMove[1] + 1));
    }

    int lines = 0;
    while (lines < ROW_COUNT || lines * 2 < moves.size())
    {
        // print this row of the board
        if (lines < ROW_COUNT)
        {
            cout << IntToChar(lines);
            for (int i = 0; i < ROW_COUNT; i++)
            {
                cout << " " << state[lines][i];
            }
        }

        // print move history
        if (lines * 2 < moves.size())
        {
            cout << "\t" << moves[lines * 2];
        }
        if (lines * 2 + 1 < moves.size())
        {
            cout << "\t" << moves[lines * 2 + 1];
        }

        cout << endl;
        lines++;
    }

    if (computerMove[0] != -1)
    {
        cout << endl;
        cout << "Computer's move is: " << moves[moves.size() - 1] << endl;
    }

}

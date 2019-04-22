#pragma once

#include <array>

using namespace std;

class Node
{
public:
    Node(array<array<char, 8>, 8> state, bool playerTurn, array<int, 2> lastMove);
    ~Node();
    int GetValue();
    array<array<char, 8>, 8> GetState();
    bool IsTerminal();
	bool IsPlayerTurn();
	array<int, 2> LastMove();

private:
    array<array<char, 8>, 8> state;
	bool isPlayerTurn;
	array<int, 2> lastMove;
    //int value;
    //bool isTerminal;

};


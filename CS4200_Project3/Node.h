#pragma once

#include <array>

using namespace std;

class Node
{
public:
    Node(array<array<char, 8>, 8> state, bool playerTurn);
    ~Node();
    int GetValue();
    array<array<char, 8>, 8> GetState();
    bool IsTerminal();
	bool IsPlayerTurn();

private:
    array<array<char, 8>, 8> state;
	bool isPlayerTurn;
    //int value;
    //bool isTerminal;

};


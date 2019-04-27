#pragma once

#include <array>
#include <vector>
#include "GameEngine.h"

using namespace std;

class Node
{
public:
    Node(array<array<char, 8>, 8> state, bool playerTurn, array<int, 2> lastMove);
	Node();
    int GetValue();
    array<array<char, 8>, 8> GetState();
    bool IsTerminal();
	bool IsPlayerTurn();
	array<int, 2> LastMove();
	vector<Node> GetSuccessors(GameEngine* gameEngine);

private:
    array<array<char, 8>, 8> state;
	bool isPlayerTurn;
	array<int, 2> lastMove;
	vector<Node> successors;
	bool hasCalculatedSuccessors;
    //int value;
    //bool isTerminal;

};


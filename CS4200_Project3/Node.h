#pragma once

#include <array>
#include <vector>
#include <memory>

using std::vector;
using std::array;
using std::shared_ptr;

class Node
{
public:
    Node(array<array<char, 8>, 8> state, bool playerTurn, array<int, 2> lastMove);
	Node();
    //Node(const Node& node);
    //int GetValue();
    array<array<char, 8>, 8> GetState();
    //bool IsTerminal();
	bool IsPlayerTurn();
	array<int, 2> LastMove();
	//vector<Node> GetSuccessors(GameEngine* gameEngine);
    bool HasCalculatedSuccessors();
    //Node PreviousState();

private:
    array<array<char, 8>, 8> state;
	bool isPlayerTurn;
	array<int, 2> lastMove;
	vector<Node> successors;
	bool hasCalculatedSuccessors;
    shared_ptr<Node> previousMove;
    //int value;
    //bool isTerminal;

};


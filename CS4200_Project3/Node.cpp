#include "Node.h"

using std::exception;

Node::Node(array<array<char, 8>, 8> state, bool computerTurn, array<int, 2> lastMove)
{
	this->state = state;
	this->isComputerTurn = computerTurn;
	this->lastMove = lastMove;
}

// Default constructor, only use as placeholder
Node::Node()
{
	state = {};
	isComputerTurn = false;
	lastMove = {};
}

array<array<char, 8>, 8> Node::GetState()
{
	return state;
}

bool Node::ComputerTurnNext()
{
	return isComputerTurn;
}

array<int, 2> Node::LastMove()
{
	return lastMove;
}

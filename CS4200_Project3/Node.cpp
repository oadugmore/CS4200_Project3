#include "Node.h"

Node::Node(array<array<char, 8>, 8> state, bool playerTurn, array<int, 2> lastMove)
{
    this->state = state;
	this->isPlayerTurn = playerTurn;
	this->lastMove = lastMove;
    //this->value = value;
    //this->isTerminal = isTerminal;
}

// Default constructor, only use as placeholder
Node::Node()
{
}

Node::~Node()
{
}

int Node::GetValue()
{
    //return value;
    throw exception("Use IsolationEngine methods for this.");
}

array<array<char, 8>, 8> Node::GetState()
{
    return state;
}

bool Node::IsTerminal()
{
    //return isTerminal;
    throw exception("Use IsolationEngine methods for this.");
}

bool Node::IsPlayerTurn()
{
	return isPlayerTurn;
}

array<int, 2> Node::LastMove()
{
	return lastMove;
}

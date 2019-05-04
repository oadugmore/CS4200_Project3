#include "Node.h"

using std::exception;

Node::Node(array<array<char, 8>, 8> state, bool computerTurn, array<int, 2> lastMove)
{
	this->state = state;
	this->isComputerTurn = computerTurn;
	this->lastMove = lastMove;
	this->hasCalculatedSuccessors = false;
	//this->value = value;
	//this->isTerminal = isTerminal;
}

// Default constructor, only use as placeholder
Node::Node()
{
	state = {};
	isComputerTurn = false;
	lastMove = {};
	hasCalculatedSuccessors = false;
}

//Node::Node(const Node& node)
//{
//}

//int Node::GetValue()
//{
//	//return value;
//	throw exception("Use IsolationEngine methods for this.");
//}

array<array<char, 8>, 8> Node::GetState()
{
	return state;
}

//bool Node::IsTerminal()
//{
//	//return isTerminal;
//	throw exception("Use IsolationEngine methods for this.");
//}

bool Node::IsComputerTurn()
{
	return isComputerTurn;
}

array<int, 2> Node::LastMove()
{
	return lastMove;
}

// Uses the GameEngine method to get this node's successors,
// and caches them for later
//vector<Node> Node::GetSuccessors(GameEngine* gameEngine)
//{
//	// if successors aren't already cached, generate them
//	if (!hasCalculatedSuccessors)
//	{
//		hasCalculatedSuccessors = true;
//	}
//	return successors;
//}

bool Node::HasCalculatedSuccessors()
{
    return hasCalculatedSuccessors;
}

//Node Node::PreviousState()
//{
//    return *previousMove;
//}

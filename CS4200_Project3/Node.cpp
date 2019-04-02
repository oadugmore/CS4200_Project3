#include "Node.h"


Node::Node(array<array<char, 8>, 8> state)
{
    this->state = state;
    //this->value = value;
    //this->isTerminal = isTerminal;
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
    return isTerminal;
    throw exception("Use IsolationEngine methods for this.");
}

#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

int Node::GetValue()
{
    return value;
}

array<array<char, 8>, 8> Node::GetState()
{
    return state;
}

bool Node::IsTerminal()
{
    return isTerminal;
}

#pragma once

#include "Node.h"

class Player
{
public:
	virtual shared_ptr<Node> GetMove(shared_ptr<Node> currentState) = 0;
};

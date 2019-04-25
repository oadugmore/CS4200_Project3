#pragma once

#include "Node.h"

class Player
{
public:
	virtual Node GetMove(Node currentState) = 0;
};

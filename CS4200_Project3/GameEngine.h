#pragma once

#include <vector>
#include "Node.h"

using std::vector;

class GameEngine
{
public:
    virtual vector<shared_ptr<Node>> GetSuccessors(shared_ptr<Node> n) = 0;
    virtual int Utility(shared_ptr<Node> n) = 0;
    virtual void FindActivePlayer(shared_ptr<Node> n, int& x, int& y) = 0;
    virtual shared_ptr<Node> Move(shared_ptr<Node> current, int currentX, int currentY, int newX, int newY) = 0;
};

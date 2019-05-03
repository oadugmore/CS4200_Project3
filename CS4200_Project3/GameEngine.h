#pragma once

#include <vector>
#include "Node.h"

using std::vector;

class GameEngine
{
public:
    virtual vector<Node> GetSuccessors(Node n) = 0;
    virtual int Utility(Node n) = 0;
    //virtual bool TerminalTest(Node n) = 0;
    virtual void FindActivePlayer(Node n, int& x, int& y) = 0;
    virtual Node Move(Node current, int currentX, int currentY, int newX, int newY) = 0;
};

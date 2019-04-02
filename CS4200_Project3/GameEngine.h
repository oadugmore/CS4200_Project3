#pragma once

#include <vector>
#include "Node.h"

class GameEngine
{
public:
    virtual vector<Node> GetSuccessors(Node n) = 0;
    virtual int Utility(Node n) = 0;
    virtual bool TerminalTest(Node n) = 0;
};

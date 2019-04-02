#pragma once

#include "Node.h"
#include "GameEngine.h"
#include <unordered_map>

using namespace std;

class MiniMax
{
public:
    MiniMax(GameEngine* gameEngine);
    ~MiniMax();
    Node AlphaBetaSearch(Node currentState);
    int MaxValue(Node currentState, int alpha, int beta, bool cacheMinResults);
    int MinValue(Node currentState, int alpha, int beta);
    int Max(int a, int b);
    int Min(int a, int b);

private:
    unordered_map<int, Node> hashTable;
    GameEngine* gameEngine;
};


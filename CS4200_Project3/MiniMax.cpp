#include "MiniMax.h"



MiniMax::MiniMax(GameEngine* gameEngine)
{
    this->gameEngine = gameEngine;
}


MiniMax::~MiniMax()
{
}

Node MiniMax::AlphaBetaSearch(Node currentState)
{
    // initialize hash table
    int v = MaxValue(currentState, INT_MIN, INT_MAX, true);
    return hashTable[v];
}

int MiniMax::MaxValue(Node currentState, int alpha, int beta, bool cacheMinResults)
{
    if (gameEngine->TerminalTest(currentState)) 
        return gameEngine->Utility(currentState);

    int v = INT_MIN;
    vector<Node> successors = gameEngine->GetSuccessors(currentState);
    for (int i = 0; i < successors.size(); i++)
    {
        v = Max(v, MinValue(successors[i], alpha, beta));
        if (v >= beta) return v;
        alpha = Max(alpha, v);
    }
    return v;
}

int MiniMax::MinValue(Node currentState, int alpha, int beta)
{
    return 0;
}

int MiniMax::Max(int a, int b)
{
    return a >= b ? a : b;
}

int MiniMax::Min(int a, int b)
{
    return a <= b ? a : b;
}

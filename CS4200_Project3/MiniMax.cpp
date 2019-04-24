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
    //int v = MaxValue(currentState, INT_MIN, INT_MAX, true);
		
	vector<Node> successors = gameEngine->GetSuccessors(currentState);
	// terminal test
	if (successors.empty())
	{
		// this is a terminal state?
		//return gameEngine->Utility(currentState);
	}

	int v = INT_MIN;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	for (int i = 0; i < successors.size(); i++)
	{
		int min = MinValue(successors[i], alpha, beta);

		v = Max(v, min);
		if (v >= beta) break;
		alpha = Max(alpha, v);
	}
	//return v;

	hashTable[min] = successors[i];
    return hashTable[v];
}

int MiniMax::MaxValue(Node currentState, int alpha, int beta)
{
	vector<Node> successors = gameEngine->GetSuccessors(currentState);
	// terminal test
    if (successors.empty())
        return gameEngine->Utility(currentState);

    int v = INT_MIN;
    for (int i = 0; i < successors.size(); i++)
    {
        int min = MinValue(successors[i], alpha, beta);
        
        v = Max(v, min);
        if (v >= beta)
			break;
        alpha = Max(alpha, v);
    }
    return v;
}

int MiniMax::MinValue(Node currentState, int alpha, int beta)
{
	vector<Node> successors = gameEngine->GetSuccessors(currentState);
	// terminal test
	if (successors.empty())
        return gameEngine->Utility(currentState);

    int v = INT_MIN;
    for (int i = 0; i < successors.size(); i++)
    {
        v = Min(v, MaxValue(successors[i], alpha, beta, false));
        if (v <= alpha)
			break;
        beta = Min(beta, v);
    }
    return v;
}

int MiniMax::Max(int a, int b)
{
    return a >= b ? a : b;
}

int MiniMax::Min(int a, int b)
{
    return a <= b ? a : b;
}
